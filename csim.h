/*
 * Header file for cahce simulator
 */

#include <string>
#include <map>
#include <list>

#ifndef CSIM_H
#define CSIM_H

void store(std::map<int, std::list<int>>* cache, int address, int n_blocks,
	   int* store_hits, int* store_misses,
	   int tag_bits, int offset_bits);

int get_index(int address, int tag_bits, int offset_bits);

//void write_allocate();
//void no_write_allocate();
//void write_back();
//void write_through();

#endif /* CSIM_H */
