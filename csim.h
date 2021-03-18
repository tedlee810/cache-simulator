/*
 * Header file for cahce simulator
 */

#ifndef CSIM_H
#define CSIM_H

#include <string>
#include <map>
#include <list>
#include <stdint.h>

void store(std::map<int, std::list<uint32_t>> &cache, uint32_t address, int n_blocks,
	   int* store_hits, int* store_misses, int* evictions,
	   int tag_bits, int offset_bits,
	   std::string allocation);

void load(std::map<int, std::list<uint32_t>> &cache, uint32_t address, int n_blocks,
           int* load_hits, int* load_misses, int* evictions,
           int tag_bits, int offset_bits);

int get_index(uint32_t address, int tag_bits, int offset_bits);

//void write_allocate();
//void no_write_allocate();
//void write_back();
//void write_through();

#endif /* CSIM_H */
