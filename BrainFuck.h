#pragma once
#include <string>
#include "TuringTape.cpp"

typedef unsigned short instruction;
typedef unsigned char byte;

class BrainFuck {
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

	/**
	 * Runs an operation
	 * @return the next instruction to execute
	 */
	instruction execute(instruction);

	// data storage
	TuringTape<byte> tape;

	// points to operating TOKEN in program
	instruction PC;

	// list of jumps to use
	instruction* jumps;

public:
	BrainFuck(char* p, size_t t = 10) : program(p), tape(t) {};
	BrainFuck(std::string p, size_t t = 10) : tape(t) {
		this->program = new char[p.size() + 1];
		std::copy(p.begin(), p.end(), this->program);
		this->program[ p.size() ] = '\0'; // don't forget the terminating 0
	};

	/**
	 * Verifies the program
	 */
	bool validate();

	/**
	 * Compresses and makes the jump table
	 */
	BrainFuck& compile();

	/**
	 * Runs the program
	 */
	BrainFuck& run();

	/**
	 * Shows Tape as it executes program
	 */
	BrainFuck& debug();
};