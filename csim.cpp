#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include "csim.h"
#include <list>
#include <map>
#include <math.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::list;

void store(map<string, list<string>>* cache, int address, int len,
	   int* store_hits, 
	   int* store_misses) {
	
	// get the index bits from the address

	// put the address into the list at the correct slot
	
	// potentially do eviction 

}

int get_index(int address, int len, int tag_bits, int offset_bits) {
	int index = address;
        for(int i = 0; i < tag_bits; i++) {
                index = index - pow(2, len - 1 - i);
        }
        for(int i = 0; i < offset_bits; i++) {
                index = index >> 1;
        }
	return index;
}
