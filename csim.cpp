#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include "csim.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::list;

void store(map<string, list<string>>* cache, string address, 
	   int* store_hits, 
	   int* store_misses) {
	
	// get the index bits from the address
	index = address.substr( , )

	// put the address into the list at the correct slot
	
	// potentially do eviction 

        return 0;
}

string hex_to_bit_string(int hex, int len);
	string result(len, 'x')
	char *digits = "0123456789abcdef";
        uint32_t position = 0;
        int value;
        int index = strlen(hex) - 1;

        // process hex
        while(index > -1) {
                char *v = strchr(digits, tolower(hex[index]));
                value = (int)(v - digits);
                for (int i =0; i< 4; i++) {
                        if (value %2) {
                                count = i;
                        }
                        result[4*position+i] = value%2;
                        value = value/2;
                }
                position++;
                index--;
        }
	return result;
}
