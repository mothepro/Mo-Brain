#pragma once
#include "BrainFuck.h"
#include <stack>

BrainFuck& BrainFuck::makeJumps() {
	std::stack< instruction > loops;
	instruction tmp;

	this->jumps = (instruction*)malloc(this->size * sizeof(instruction));

	for(instruction i=0; i<this->size; i++)
		switch(this->program[ i ]) {
		case '[':
		case '(':
			loops.push( i ); // add loop start to stack
			break;

		case ']':
		case ')':
			tmp = loops.top();
			loops.pop();

			// add unconditional jump to start of loop
			//this->jumps[ i ].check	= false;
			this->jumps[ i ]		= tmp;

			// add conditional jump to end of loop
			//this->jumps[ tmp ].check	= true;
			this->jumps[ tmp ]		= i;

			break;
		}

	return *this;
}

BrainFuck& BrainFuck::compress() {
	char* tmp = (char*)malloc(1024);
	this->size = 0;

	do {
		switch(*this->program) {
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
			tmp[ this->size++ ] = *this->program;
		}
	} while(*(this->program++));

	// end string
	tmp[ this->size ] = '\0';

	this->program = tmp;

	return *this;
}

BrainFuck& BrainFuck::compile() {
	this->compress();
	this->makeJumps();
	return *this;
}

BrainFuck& BrainFuck::run() {
	system("cls");

	// start at beginning
	this->PC = 0;

	#ifdef DEBUG
		instruction prePC;
		char output[100] = "";
		int outlen = 0;
	#endif

	while(this->PC < this->size) {
		#ifdef DEBUG
			prePC = this->PC;
		#endif

		switch(this->program[ this->PC ]) {
		case '+': // increment
			this->tape.inc();
			this->PC++;
			break;

		case '-': // decrement
			this->tape.dec();
			this->PC++;
			break;

		case '>': // shift right
			this->tape.right();
			this->PC++;
			break;

		case '<': // shift left
			this->tape.left();
			this->PC++;
			break;

		case '[': // if false jump after ]
			if(!this->tape.get()) // false; skip the loop
				this->PC = this->jumps[ this->PC ] +1;
			else
				this->PC++;
			break;

		case ']': // jump to [ "unconditional"
			// this->PC = this->jumps[ this->PC ]
			if(this->tape.get())
				this->PC = this->jumps[ this->PC ] +1;
			else
				this->PC++;
			break;

		case ',': // input byte
			// byte t;
			// printf("Input: ");
			// scanf_s(" %c", &t);
			this->tape.set( getchar() );

			this->PC++;
			break;
		
		case '.': // output byte
			#ifdef DEBUG
				output[ outlen++ ] = this->tape.get();
			#else
				putchar( this->tape.get() );
			#endif

			this->PC++;
			break;

		//////////////////////
		// Custom BrainFuck //
		//////////////////////

		case '(': // continue if byte is true
			if(!this->tape.get()) // false; skip to )
				this->PC = this->jumps[ this->PC ];
			else
				this->PC++;
			break;

		case ')': // ignore
			this->PC++;
			break;
		}

		#ifdef DEBUG
			system("cls");

			//printf("%s\n", this->program);
			//printf("%.*s%c\n", (this->PC < 1) ? 0 : this->PC-1, "                                                                                 ", '_');
			
			printf("Command: %c\t\tPC: %d -> %d\n", this->program[ prePC ], prePC+1, this->PC+1);
			this->tape.show();

			if(outlen)
				printf("%s", output);

			getchar();
		#endif
	}

	return *this;
}