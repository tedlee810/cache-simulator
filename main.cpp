/**
 * Ted Lee         tlee144
 * Thomas Mazumder tmazumd1
 *
 * Cache simulator using either LRU or FIFO.
 *
 * CSF Assignment 3
 */

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
using std::cerr;
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

/**
 * Extracts bits from a given integer.
 *
 * @param address  is a 32-bit address to extract bits from.
 * @param num_bits is the number of bits to extract
 * @param position is the position where to begin the extraction.
 *
 * @return an integer representation of the extracted bits.
 */
int get_bits(uint32_t address, int num_bits, int position) {
  return ((1 << num_bits) - 1) & (address >> (position - 1));
}

/**
 * Checks if a given integer is a power of 2.
 *
 * @param num is the integer to be checked.
 *
 * @return true  if num is a power of 2;
 *         false otherwise.
 */
bool is_power_of_two(int num) {
  return (ceil(log2(num)) == floor(log2(num)));
}

/**
 * For testing purposes only. Prints the contents of a list.
 *
 * @param list is a const reference to a list of uint32_t elements.
 */
void print(list<uint32_t> const &list) {
  cout << "list content:" << endl;
  for (auto const & i: list) {
    cout << i << endl;
  }
  cout << endl;
}

/**
 * Calculate the total cycles depending on write policies.
 *
 * @param store_hits   is the number of store hits that occurred in the cache.
 * @param store_misses is the number of store misses that occurred in the cache.
 * @param load_hits    is the number of load hits that occurrred in the cache.
 * @param load_misses  is the number of load misses that occurred in the cache.
 * @param n_bytes      is the number of bytes allocated per block.
 * @param store_type   is the string representation of the store type of the cache.
 * @param allocation   is the string representation of the  allocation type of the cache.
 *
 * @return the total cycles required.
 */
int calc_total_cycles(int store_hits, int store_misses,
		      int load_hits, int load_misses,
		      string store_type, int n_bytes,
		      string allocation) {

  // coefficient for when writing to memory
  int memory_cycles = 1 + (100 * n_bytes / 4);

  // total cycles (every combination calculates load hits and misses the same)
  int total_cycles = load_misses * memory_cycles + load_hits;
  
  // calculate using write-through and write-allocate
  if (store_type == "write-through" && allocation == "write-allocate") {
    total_cycles += store_misses * (memory_cycles + 100);
    total_cycles += store_hits * 101;
  }
  // calculuate using write-back and no-write-allocate
  else if (store_type == "write-through" && allocation == "no-write-allocate") {
    total_cycles += store_hits * 101;
    total_cycles += store_misses * 100;
  }
  // calculate using write-back and write-allocate
  else {
    total_cycles += store_hits;
    total_cycles += store_misses * memory_cycles;
  }
  return total_cycles;
}

/**
 * Prints the data points after running the cache.
 *
 * @param total_stores is the total stores performed.
 * @param total_loads  is the total loads performed.
 * @param load_hits    is the load hits performed.
 * @param load_missees is the load misses performed.
 * @param store_hits   is the store hits performed.
 * @param store_misses is the store misses performed.
 * @param total_cycles is the total processor cycles performed.
 */
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
/**
 * Checks for bad expressions in the command-line arguments.
 *
 * @param n_sets     is the number of sets in the cache.
 * @param n_blocks   is the number of blocks per set.
 * @param n_bytes    is the number of bytes per block.
 * @param allocation is the string representation of the allocation type.
 * @param store_type is the string representation of the store type.
 *
 * @return 2 if no-write-allocate and write-back are entered simultaneously.
 * @return 3 if n_sets is not a power of 2.
 * @return 4 if n_blocks is not a power of 2.
 * @return 5 if n_bytes is not a power of 2.
 * @return 6 if there are less than 4 bytes per block.
 * @return 0 otherwise.
 */
int check_errors(int n_sets, int n_blocks, int n_bytes, string allocation, string store_type) {
  // error code to return
  int has_error = 0;
  
  if (allocation == "no-write-allocate" && store_type == "write-back") {
    cerr << "No-write allocation and write back are invalid." << endl;
    has_error = 2;
  }
  if (!is_power_of_two(n_sets)) {
    cerr << "Number of sets must be a power of 2." << endl;
    has_error = 3;
  }
  if (!is_power_of_two(n_blocks)) {
    cerr << "Number of blocks per set must be a power of 2." << endl;
    has_error = 4;
  }
  if (!is_power_of_two(n_bytes)) {
    cerr << "Number of bytes per block must be a power of 2." << endl;
    has_error = 5;
  }
  if (n_bytes < 4) {
    cerr << "Number of bytes per block must be at least 4." << endl;
    has_error = 6;
  }
  return has_error;
}

/**
 * Controls the operations of the cache simulator.
 *
 * @return 0 if no errors.
 * @return 1 if incorrect number of arguments. 
 * @return 2 if no-write-allocate and write-back are entered simultaneously.
 * @return 3 if n_sets is not a power of 2.
 * @return 4 if n_blocks is not a power of 2.
 * @return 5 if n_bytes is not a power of 2.
 * @return 6 if there are less than 4 bytes per block.
 */
int main(int argc, char** argv){
  // check the correct number of args were provided
  if (argc != 7) {
    cerr << "Incorrect number of arguments; must be exactly 7." << endl;
    return 1;
  }

  int n_sets = atoi(argv[1]);   // number of sets in cache
  int n_blocks = atoi(argv[2]); // number of slots in each set
  int n_bytes = atoi(argv[3]);  // number of bytes per block
  string allocation = argv[4];  // allocation type (write- or no-write allocate)
  string store_type = argv[5];  // store type (write-through or write-back)
  string cache_type = argv[6];  // cache type (LRU or FIFO)

  // check for bad expressions in command-line args
  int error_code = check_errors(n_sets, n_blocks, n_bytes, allocation, store_type);
  if (error_code != 0)
    return error_code;

  // declare cache with indices as keys and a list of addresses as keys
  map<int, list<uint32_t>> cache;
  
  // instantiate statistics
  int load_hits = 0;
  int load_misses = 0;
  int store_hits = 0;
  int store_misses = 0;
  int evictions = 0;

  // calcuate index, offset, and tag bits
  int index_bits = log2(n_sets);
  int offset_bits = log2(n_bytes);
  int tag_bits = 32 - index_bits - offset_bits;
  
  // read in input
  for (string line; getline(cin, line); ) {
    istringstream iss(line);
    vector<string> tokens;
    uint32_t address;
    copy(istream_iterator<string>(iss),
	 istream_iterator<string>(),
	 back_inserter(tokens));		
    stringstream ss;
    ss << hex << tokens[1];
    ss >> address;
    
    /* tokens[2] is the ignored field */

    // extract index bits
    int index = get_bits(address, index_bits, offset_bits + 1);
    // create new address without offset bits (to be stored in cache)
    address = get_bits(address, tag_bits + index_bits, offset_bits + 1);
    
    /* STORING INTO CACHE */
    if (tokens[0] == "s") {
      store(cache, address, n_blocks, &store_hits, &store_misses, &evictions,
	    index, allocation, cache_type);
    }    
    /* LOADING FROM CACHE */
    else {
      load(cache, address, n_blocks, &load_hits, &load_misses, &evictions,
	   index, cache_type);
    }
  }

  // calculate data to print
  int total_stores = store_hits + store_misses;
  int total_loads = load_hits + load_misses;
  int total_cycles = calc_total_cycles(store_hits, store_misses, load_hits, load_misses,
				       store_type, n_bytes, allocation);

  // print data
  print_output(total_stores, total_loads, load_hits, load_misses,
	       store_hits, store_misses, total_cycles);
  
  return 0;
}
