#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include <map>
#include <list>
#include "csim.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::list;

int main(int argc, char** argv){

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

	map<string, list<string>>* cache;  // pointer ????

	// statistics
	int total_loads = 0;
	int total_stores = 0;
	int load_hits = 0;
	int load_misses = 0;
	int store_hits = 0;
	int store_misses = 0;
	int total_cycles = 0;


	// read the input file


	


	return 0;
}
