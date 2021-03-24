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
	       string allocation, string cache_type) {
	
  // check to see if address is in cache in that index bit
  bool found = (find(cache[index].begin(), cache[index].end(), address) != cache[index].end());

  // if found, it's a hit; otherwise, it's a miss
  if (found) {
    // increment store hits
    (*store_hits)++;

    // if LRU, move the address from the cache and put it to the front
    if (cache_type == "lru") {
      cache[index].remove(address);
      cache[index].push_front(address);
    }
  } else {
    // increment store misses
    (*store_misses)++;

    // if write-allocate, insert the address into cache
    if (allocation == "write-allocate") {
      cache[index].push_front(address);
    }
  }
  
  // evict if size of list goes over number of blocks allowed per set
  if ((int) cache[index].size() > n_blocks) {
    (*evictions)++;
    cache[index].pop_back();
  }
}

void load(map<int, list<uint32_t>> &cache, uint32_t address, int n_blocks,
	  int* load_hits, int* load_misses, int* evictions, int index, string cache_type) {

  // check to see if address is in cache in that index bit
  bool found = (find(cache[index].begin(), cache[index].end(), address) != cache[index].end());	

  // if found, it's a hit; otherwise, it's a miss
  if (found) {
    // increment load hits
    (*load_hits)++; // increment load hit count

    if (cache_type == "lru") {
      cache[index].remove(address);
      cache[index].push_front(address);
    }
  } else {
    // increment load misses
    (*load_misses)++;

    // insert the address into cache
    cache[index].push_front(address);
  }

  // evict if size of list goes over number of blocks allowed per set
  if ((int) cache[index].size() > n_blocks) {
    (*evictions)++;
    cache[index].pop_back();
  }
}
