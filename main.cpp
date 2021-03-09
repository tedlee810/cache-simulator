#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char** argv){

	// check the correct number of args were provided
	if (argc != 7) {
		cout << "Not enough arguments\n";
		return 1;
	}

	int n_sets = atoi(argv[0]);
	int n_blocks = atoi(argv[1]);
	int n_bytes = atoi(argv[2]);
	string allocation = argv[3];
	string store_type = argv[4];
	
	return 0;
}
