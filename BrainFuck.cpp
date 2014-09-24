#pragma once
#include "BrainFuck.h"
#include <stack>
#include <iostream>

BrainFuck& BrainFuck::makeJumps() {
	std::stack< instruction > loops;
	instruction tmp;

	jumps = (instruction*)malloc(size * sizeof(instruction));

	for(instruction i=0; i<size; i++)
		switch(program[ i ]) {
		case '[':
		case '(':
			loops.push( i ); // add loop start to stack
			break;

		case ']':
		case ')':
			tmp = loops.top();
			loops.pop();

			// add unconditional jump to start of loop
			//jumps[ i ].check	= false;
			jumps[ i ]		= tmp;

			// add conditional jump to end of loop
			//jumps[ tmp ].check	= true;
			jumps[ tmp ]		= i;

			break;
		}

	return *this;
}

BrainFuck& BrainFuck::compress() {
	char* tmp = (char*)malloc(1024);
	size = 0;

	do {
		switch(*program) {
		case '+':
		case '-':
		case '>':
		case '<':
		case '[':
		case ']':
		case '.':
		case ',':

		case '(':
		case ')':
			tmp[ size++ ] = *program;
		}
	} while(*(program++));

	// end string
	tmp[ size ] = '\0';

	program = tmp;

	return *this;
}

BrainFuck& BrainFuck::compile() {
	compress();
	makeJumps();
	return *this;
}

instruction BrainFuck::execute(instruction on) {
	switch(program[ on ]) {
	case '+': // increment
		tape.inc();
		break;

	case '-': // decrement
		tape.dec();
		break;

	case '>': // shift right
		tape.right();
		break;

	case '<': // shift left
		tape.left();
		break;

	case '[': // if false jump after ]
		if(!tape.get()) // false; skip the loop
			on = jumps[ on ];
		break;

	case ']': // jump to [ "unconditional"
		// on = jumps[ on ]
		if(tape.get())
			on = jumps[ on ];
		break;

	case ',': // input byte
		tape.set( getchar() );
		break;
		
	case '.': // output byte
		// output[ outlen++ ] = tape.get();
		putchar( tape.get() );
		break;

	//////////////////////
	// Custom BrainFuck //
	//////////////////////

	case '(': // continue if byte is true
		if(!tape.get()) // false; skip to )
			on = jumps[ on ];
		break;

	case ')': // ignore
		break;
	}
	
	// goto next instruction
	return on + 1;
}

BrainFuck& BrainFuck::run() {
	system("cls");

	for(
		PC = 0;				// start at beginning
		PC < size;			// dont past the end
		PC = execute(PC)	// do stuff and get the next
	);

	return *this;
}

BrainFuck& BrainFuck::debug() {
	instruction prePC;
	std::string output;
	bool wait = true;

	// start at beginning
	PC = 0;

	while(PC < size) {
		// run it!
		prePC = PC;
		PC = execute( PC );

		system("cls");

		// output
		if(program[ prePC ] == '.')
			output.push_back( (char)tape.get() );

		// give stats
		printf("Command: %c\t\tPC: %d -> %d\n", program[ prePC ], prePC+1, PC+1);

		// show data
		this->tape.show();

		// output if any
		if(!output.empty())
			std::cout << output; // << std::endl << std::endl;

		if(wait)
			if(getchar() != '\n')
				wait = false;
	}

	return *this;
}