/*
 * Header file for cahce simulator
 */

#include <string>

#ifndef CSIM_H
#define CSIM_H

void store();
int get_index(int address, int len, int tag_bits, int offset_bits);
//void write_allocate();
//void no_write_allocate();
//void write_back();
//void write_through();

#endif /* CSIM_H */
