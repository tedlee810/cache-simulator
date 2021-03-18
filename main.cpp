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

void print(list<uint32_t> const &list) {
  for (auto const & i: list) {
    cout << "list content: " << i << endl;
  }
}

int main(int argc, char** argv){
  
	// check the correct number of args were provided
	if (argc != 7) {
		cout << "Not enough arguments\n";
		return 1;
	}

	int n_sets = atoi(argv[1]);
	int n_blocks = atoi(argv[2]);  // number of slots in each set
	int n_bytes = atoi(argv[3]);
	string allocation = argv[4];
	string store_type = argv[5];

	cout << "n_blocks: " << n_blocks << endl;
	
	map<int, list<uint32_t>> cache;

	// statistics
	int total_loads = 0;
	int total_stores = 0;
	int load_hits = 0;
	int load_misses = 0;
	int store_hits = 0;
	int store_misses = 0;
	int total_cycles = 0;

	int tag_bits = 32 - log2(n_sets) - log2(n_bytes);
	int offset_bits = log2(n_bytes);
	cout << "tag_bits: " << tag_bits << endl;
	cout << "offset_bits: " << offset_bits << endl << endl;
	
	// read in input
	for (string line; getline(cin, line);) {
	  istringstream iss(line);
	  vector<string> tokens;
	  uint32_t address;
	  copy(istream_iterator<string>(iss),
	       istream_iterator<string>(),
	       back_inserter(tokens));		
	  stringstream ss;
	  ss << hex << tokens[1];
	  ss >> address;
	  cout << tokens[0] << endl;
	  cout << address << endl;

	  // tokens[2] is the ignored field
	  
	  if (tokens[0] == "s") {
	    store(cache, address, n_blocks,
		  &store_hits, &store_misses,
		  tag_bits, offset_bits);
	    print(cache[0]);
	  } else if (tokens[0] == "cache, address") {
	    //load();
	  }
	  cout << endl;
	} 

	return 0;
}
