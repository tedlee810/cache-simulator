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

void print(list<uint32_t> const &list) {
  for (auto const & i: list) {
    cout << "list content: " << i << endl;
  }
}

int calc_total_cycles(int store_hits, int store_misses,
		      int load_hits, int load_misses,
		      int evictions, string store_type) {
  int total_cycles = 0;
  if (store_type == "write-through") {
    total_cycles += store_hits * 100; // write to memory
    total_cycles += store_hits; // write to cache
    total_cycles += store_misses * 100; // write to memory
    total_cycles += store_misses; // write to cache
    total_cycles += load_misses * 100; // load from memory
    total_cycles += load_misses; // write to cache
    total_cycles += load_hits; // load from cache
  } else if (store_type == "write-back") {
    total_cycles += store_hits; // write to cache
    total_cycles += evictions * 100; // write to memory
    total_cycles += store_misses; // write to cache
    total_cycles += load_misses * 100; // load from memory
    total_cycles += load_misses; // write to cache
    total_cycles += load_hits; // load from cache
  }
  return total_cycles;
}

int main(int argc, char** argv){
  
  // check the correct number of args were provided
  if (argc != 7) {
    cout << "Not enough arguments\n";
    return 1;
  }
  
  int n_sets = atoi(argv[1]);
  int n_blocks = atoi(argv[2]);  // number of slots in each set
  int n_bytes = atoi(argv[3]);
  string allocation = argv[4];
  string store_type = argv[5];
  
  cout << "n_blocks: " << n_blocks << endl;
  
  map<int, list<uint32_t>> cache;
  
  // statistics
  int load_hits = 0;
  int load_misses = 0;
  int store_hits = 0;
  int store_misses = 0;
  int evictions = 0;
  
  int tag_bits = 32 - log2(n_sets) - log2(n_bytes);
  int offset_bits = log2(n_bytes);
  cout << "tag_bits: " << tag_bits << endl;
  cout << "offset_bits: " << offset_bits << endl << endl;
  
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
    
    
    if (tokens[0] == "s") {
      store(cache, address, n_blocks,
	    &store_hits, &store_misses, &evictions,
	    tag_bits, offset_bits,
	    allocation);
    } else if (tokens[0] == "l") {
      load(cache, address, n_blocks,
	   &load_hits, &load_misses, &evictions,
	   tag_bits, offset_bits);	    
    }
    //print(cache[0]);
  } 
  
  
  int total_stores;
  if (store_type == "write-through") {
    total_stores = (store_hits + store_misses) * n_bytes / 4;	
  } else if (store_type == "write-back") {
    total_stores = evictions * n_bytes / 4;
  }
  
  int total_loads = load_misses * n_bytes / 4;
  int total_cycles = calc_total_cycles(store_hits, store_misses,
				       load_hits, load_misses,
				       evictions, store_type);
  
  cout << "Total stores: " << total_stores << endl;
  cout << "Total loads: " << total_loads << endl;
  cout << "Load hits: " << load_hits << endl;
  cout << "Load misses: " << load_misses << endl;
  cout << "Store hits: " << store_hits << endl;
  cout << "Store misses: " << store_misses << endl; 
  cout << "Total cycles: " << total_cycles << endl;
  
  return 0;
}
