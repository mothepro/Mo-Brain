#pragma once
#include <string>
#include "TuringTape.h"
#define DEBUG

typedef unsigned short instruction;

class BrainFuck {
public:
	BrainFuck(char* p, size_t t = 10) : program(p), tape(t) {};
	BrainFuck(std::string p, size_t t = 10) : tape(t) {
		this->program = new char[p.size() + 1];
		std::copy(p.begin(), p.end(), this->program);
		this->program[ p.size() ] = '\0'; // don't forget the terminating 0
	};

	bool validate();
	BrainFuck& compile();
	BrainFuck& run();

private:
	// program tokens
	char* program;

	// size of program
	instruction size;

	// sets the size of the program and jump table
	BrainFuck& compress();

	// creates the jump table
	BrainFuck& makeJumps();

	// optimize BF
	BrainFuck& opitmize();

	// data storage
	TuringTape tape;

	// points to operating TOKEN in program
	instruction PC;

	// list of jumps to use
	instruction* jumps;
};