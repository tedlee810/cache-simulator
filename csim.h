/**
 * Ted Lee         tlee144
 * Thomas Mazumder tmazumd1
 *
 * Header file for csim.cpp.
 */

#ifndef CSIM_H
#define CSIM_H

#include <string>
#include <map>
#include <list>
#include <stdint.h>

/**
 * Stores a given address into a cache.
 *
 * @param cache        is a reference to a map<int, list<uint32_t>> that represents the cache.
 * @param address      is the address to store in the cache.
 * @param n_blocks     is the number of blocks per set.
 * @param store_hits   is an integer pointer containing the number of store hits in a cache.
 * @param store_misses is an integer pointer containing the number of store misses in a cache.
 * @param evictions    is an integer pointer containing the number of evictions in a cache.
 * @param index        is an integer representation of the index bits in the address.
 * @param allocation   is the string representation of the allocation type for the cache.
 * @param cache_type   is the string representation of the cache type.
 */
void store(std::map<int, std::list<uint32_t>> &cache, uint32_t address, int n_blocks,
	   int* store_hits, int* store_misses, int* evictions, int index,
	   std::string allocation, std::string cache_type);

/**
 * Loads a given address from a cache.
 *
 * @param cache        is a reference to a map<int, list<uint32_t>> that represents the cache.
 * @param address      is the address to store in the cache.
 * @param n_blocks     is the number of blocks per set.
 * @param store_hits   is an integer pointer containing the number of store hits in a cache.
 * @param store_misses is an integer pointer containing the number of store misses in a cache.
 * @param evictions    is an integer pointer containing the number of evictions in a cache.
 * @param index        is an integer representation of the index bits in the address.
 * @param cache_type   is the string representation of the cache type.
 */
void load(std::map<int, std::list<uint32_t>> &cache, uint32_t address, int n_blocks,
	  int* load_hits, int* load_misses, int* evictions, int index, std::string cache_type);

/**
 * Loads a given address from a cache.
 *
 * @param cache        is a reference to a map<int, list<uint32_t>> that represents the cache.
 * @param address      is the address to store in the cache.
 * @param n_blocks     is the number of blocks per set.
 * @param store_hits   is an integer pointer containing the number of store hits in a cache.
 * @param store_misses is an integer pointer containing the number of store misses in a cache.
 * @param evictions    is an integer pointer containing the number of evictions in a cache.
 * @param index        is an integer representation of the index bits in the address.
 */
void load_fifo(std::map<int, std::list<uint32_t>> &cache, uint32_t address, int n_blocks,
	       int* load_hits, int* load_misses, int* evictions, int index);

#endif /* CSIM_H */
