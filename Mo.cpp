#include "BrainFuck.h"
#include <string>
#include <iostream>

int main() {
	size_t s;
	std::string prog, // "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++."; // Hello World
		line;

	printf("Tape Length: ");
	scanf_s(" %d", &s);
	getchar();

	printf("Your Program:\n");
	do {
		std::getline(std::cin, line);
		prog += line;
	} while(!line.empty());

	BrainFuck b(prog, s);
	b.compile().run();

	getchar();
	return 0;
}