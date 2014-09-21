#include "TuringTape.h"
#include <cstdio>
#include <cstdlib>

TuringTape::TuringTape(size_t l) {
	this->size = l;
	this->start = (byte*)calloc(this->size, sizeof(byte)); // new byte[ this->size ];
	this->ptr = this->start;
}

TuringTape& TuringTape::show() {
	size_t i, len;

	// top of box
	for(i=0; i<this->size; i++)
		printf("+------");
	printf("+\n");
	
	// box info
	for(i=0; i<this->size; i++)
		printf("| %4d ", *(this->start + i*sizeof(byte)));
	printf("|\n");

	// bottom of box
	for(i=0; i<this->size; i++)
		printf("+------");
	printf("+\n");

	// location
	for(i=0, len = (this->ptr - this->start) / sizeof(byte); i<len; i++)
		printf("       ");
	printf("   /\\\n\n");

	return *this;
}

TuringTape& TuringTape::left() {
	if(this->ptr > this->start)
		this->ptr--;

#ifdef WRAP
	else
		this->ptr = this->start + this->size * sizeof(byte);
#endif
	return *this;
}

TuringTape& TuringTape::right() {
	if(this->ptr < this->start + this->size)
		this->ptr++;

#ifdef WRAP
	else
		this->ptr = this->start;
#endif
	return *this;
}

TuringTape& TuringTape::inc() {
	(*this->ptr)++;
	return *this;
}

TuringTape& TuringTape::dec() {
	(*this->ptr)--;
	return *this;
}

byte TuringTape::get() {
	return *this->ptr;
}

void TuringTape::set(byte b) {
	*this->ptr = b;
}