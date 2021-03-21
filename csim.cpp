#include "csim.h"

#include <cstdlib>
#include <stdint.h>
#include <cstdio>
#include <string>
#include <iostream>
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

void store(map<int, list<uint32_t>> &cache, uint32_t address, int n_blocks,
	   int* store_hits, int* store_misses, int* evictions, int index,
	   string allocation) {
	
  // check to see if address is in cache in that index bit
  bool found = (find(cache[index].begin(), cache[index].end(), address) != cache[index].end());

  // if found, it's a hit;
  // otherwise, it's a miss
  if (found) {
    (*store_hits)++; // increment store hit count
    cache[index].splice(cache[index].begin(), cache[index], cache[index].begin()); // move that element to front
  } else {
    (*store_misses)++; // increment store miss count
    if (allocation == "write-allocate") {
      cache[index].push_front(address); // insert this new address into cache
    }
  }
  
  // potentially do eviction
  if ((int) cache[index].size() > n_blocks) {
    (*evictions)++;
    cache[index].pop_back();
  }
}

void load(map<int, list<uint32_t>> &cache, uint32_t address, int n_blocks,
	  int* load_hits, int* load_misses, int* evictions, int index) {
  // check to see if address is in cache in that index bit
  bool found = (find(cache[index].begin(), cache[index].end(), address) != cache[index].end());	

  // if found, it's a hit;
  // otherwise, it's a miss
  if (found) {
    (*load_hits)++; // increment load hit count
    cache[index].splice(cache[index].begin(), cache[index], cache[index].begin()); // move that element to front
  } else {
    (*load_misses)++; // increment load miss count
    cache[index].push_front(address); // insert this new address into cache
  }

  // potentially do eviction
  if ((int) cache[index].size() > n_blocks) {
    (*evictions)++;
    cache[index].pop_back();
  }

}

/*
  SCRATCH PAPER lmao

  ... 00[00 1111 11]11
  [0011 1111] 1100 ...
  ... 0000 [0011 1111]
 */
