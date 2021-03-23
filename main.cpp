#include "csim.h"

#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include <map>
#include <math.h>
#include <list>
#include <sstream>
#include <vector>
#include <algorithm> 
#include <iterator>
#include <stdint.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::stringstream;
using std::istringstream;
using std::istream_iterator;
using std::back_inserter;
using std::map;
using std::list;
using std::vector;
using std::hex;

/*
int get_index(uint32_t address, int tag_bits, int offset_bits) {
  uint32_t index = address;
  index = index << tag_bits;
  index = index >> (offset_bits + tag_bits);
  return (int) index;
  }*/

int get_bits(uint32_t address, int num_bits, int position) {
  return ((1 << num_bits) - 1) & (address >> (position - 1));
}

bool is_power_of_two(int num) {
  return (ceil(log2(num)) == floor(log2(num)));
}

void print(list<uint32_t> const &list) {
  cout << "list content:" << endl;
  for (auto const & i: list) {
    cout << i << endl;
  }
  cout << endl;
}

int calc_total_cycles(int store_hits, int store_misses,
		      int load_hits, int load_misses,
		      int evictions, string store_type, int n_bytes) {
  int total_cycles = 0;
  int memory_cycles = 1 + (100 * n_bytes / 4);
  
  // calculate using write-through
  if (store_type == "write-through") {
    total_cycles += load_misses * memory_cycles;
    total_cycles += load_hits;
    total_cycles += store_misses * memory_cycles;
    total_cycles += store_hits;
  }
  // calculuate using write-back
  else {
    total_cycles += store_hits; // write to cache
    total_cycles += evictions * memory_cycles; // write to memory
    total_cycles += store_misses; // write to cache
    total_cycles += load_misses * memory_cycles; // load from memory
    total_cycles += load_hits; // load from cache
  }
  return total_cycles;
}

void print_output(int total_stores, int total_loads, int load_hits, int load_misses,
		  int store_hits, int store_misses, int total_cycles) {
  cout << "Total loads: " << total_loads << endl;
  cout << "Total stores: " << total_stores << endl;
  cout << "Load hits: " << load_hits << endl;
  cout << "Load misses: " << load_misses << endl;
  cout << "Store hits: " << store_hits << endl;
  cout << "Store misses: " << store_misses << endl; 
  cout << "Total cycles: " << total_cycles << endl;
}

int main(int argc, char** argv){
  
  // check the correct number of args were provided
  if (argc != 7) {
    cout << "Not enough arguments." << endl;
    return 1;
  }
  
  int n_sets = atoi(argv[1]);
  int n_blocks = atoi(argv[2]);  // number of slots in each set
  int n_bytes = atoi(argv[3]);
  string allocation = argv[4];
  string store_type = argv[5];
  string cache_type = argv[6];

  if (allocation == "no-write-allocate" && store_type == "write-back") {
    cout << "No-write allocation and write back are invalid." << endl;

    return 2;
  }

  if (!is_power_of_two(n_sets)) {
    cout << "Number of sets must be a power of 2." << endl;
    return 3;
  } else if (!is_power_of_two(n_blocks)) {
    cout << "Number of blocks per set must be a power of 2." << endl;
    return 4;
  } else if (!is_power_of_two(n_bytes)) {
    cout << "Number of bytes per block must be a power of 2." << endl;
    return 5;
  } else if (n_bytes < 4) {
    cout << "Number of bytes per block must be at least 4." << endl;
    return 6;
  }
  
  map<int, list<uint32_t>> cache;
  
  // statistics
  int load_hits = 0;
  int load_misses = 0;
  int store_hits = 0;
  int store_misses = 0;
  int evictions = 0;
  
  int index_bits = log2(n_sets);
  int offset_bits = log2(n_bytes);
  int tag_bits = 32 - index_bits - offset_bits;
  
  // read in input
  for (string line; getline(cin, line);) {
    istringstream iss(line);
    vector<string> tokens;
    uint32_t address;
    copy(istream_iterator<string>(iss),
	 istream_iterator<string>(),
	 back_inserter(tokens));		
    stringstream ss;
    ss << hex << tokens[1];
    ss >> address;
    
    // tokens[2] is the ignored field
    
    //int index = get_index(address, tag_bits, offset_bits);
    int index = get_bits(address, index_bits, offset_bits + 1);

    // DEBUGGING ONLY
    //cout << "index of address " << address << " is: " << index << endl;
    
    address = get_bits(address, tag_bits + index_bits, offset_bits + 1); // new address w/o offset bits
    //cout << "address after offset bit truncation: " << address << endl << endl;
    
    // if storing
    if (tokens[0] == "s") {
      if (cache_type == "lru") {
        store_lru(cache, address, n_blocks, &store_hits, &store_misses, &evictions, index, allocation);    
      }
      else {
        store_fifo(cache, address, n_blocks, &store_hits, &store_misses, &evictions, index, allocation);
      }
    }
    // if loading
    else {
      if (cache_type == "lru") {
        load_lru(cache, address, n_blocks, &load_hits, &load_misses, &evictions, index);	    
      } else {
        load_fifo(cache, address, n_blocks, &load_hits, &load_misses, &evictions, index);
      }
    }
    //print(cache[0]);
  } 

  int total_stores = store_hits + store_misses;
  int total_loads = load_hits + load_misses;
  int total_cycles = calc_total_cycles(store_hits, store_misses, load_hits, load_misses,
				       evictions, store_type, n_bytes);

  print_output(total_stores, total_loads, load_hits, load_misses,
	       store_hits, store_misses, total_cycles);
  
  return 0;
}
