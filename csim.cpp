#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include "csim.h"
#include <list>
#include <map>
#include <math.h>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::list;
using std::find;

void store(map<int, list<int>>* cache, int address, int n_blocks,
	   int* store_hits, int* store_misses,
	   int tag_bits, int offset_bits) {
	
  // get the index bits from the address
  int index = get_index(address, tag_bits, offset_bits);
  
  // check to see if address is in cache in that index bit
  bool found = (find(cache[index].begin(), cache[index].end(), address) != cache[index].end());

  // if found, it's a hit;
  // otherwise, it's a miss
  if (found) {
    (*store_hits)++; // increment store hit count
    cache[index].splice(cache[index].begin(); cache[index]; cache[index].begin()); // move that element to front
  } else {
    (*store_misses)++; // increment store miss count
    cache[index].push_front(address); // insert this new address into cache
  }
  
  // potentially do eviction
  if (cache[index].size() > n_blocks)
    cache[index].pop_back();
}

int get_index(int address, int tag_bits, int offset_bits) {
  int index = address;
  for(int i = 0; i < tag_bits; i++) {
    // each address is always 32 bits long
    index = index - pow(2, 32 - 1 - i); // take off the tag bits
  }
  for(int i = 0; i < offset_bits; i++) {
    index = index >> 1; // take off the offset bits
  }
  return index;
}
