#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include <map>
#include <list>
#include "csim.h"
#include <sstream>
#include <vector>
#include <algorithm> 
#include <iterator>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::list;
using std::vector;

int main(int argc, char** argv){

	/*
	// check the correct number of args were provided
	if (argc != 7) {
		cout << "Not enough arguments\n";
		return 1;
	}

	int n_sets = atoi(argv[0]);
	int n_blocks = atoi(argv[1]);  // number of slots in each set
	int n_bytes = atoi(argv[2]);
	string allocation = argv[3];
	string store_type = argv[4];

	map<string, list<string>> cache;  // pointer ????

	// statistics
	int total_loads = 0;
	int total_stores = 0;
	int load_hits = 0;
	int load_misses = 0;
	int store_hits = 0;
	int store_misses = 0;
	int total_cycles = 0;
	*/

	// read in input
	for (std::string line; std::getline(cin, line);) {
		std::istringstream iss(line);
		vector<string> tokens;
		unsigned int x;
		copy(std::istream_iterator<string>(iss),
     			std::istream_iterator<string>(),
     			std::back_inserter(tokens));		
		std::stringstream ss;
		ss << std::hex << tokens[1];
		ss >> x;
		cout << tokens[0] << endl;
        	cout << x << endl;
	} 

	return 0;
}
