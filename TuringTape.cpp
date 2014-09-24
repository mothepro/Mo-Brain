#include "TuringTape.h"
#include <cstdio>
#include <cstdlib>

template <class T>
TuringTape<T>::TuringTape(size_t len) {
	this->size = len;
	this->start = (T*)calloc(this->size, sizeof(T)); // new T[ this->size ];
	this->ptr = this->start;
}

template <class T>
void TuringTape<T>::show() {
	size_t i, len;

	// top of box
	for(i=0; i<this->size; i++)
		printf("+------");
	printf("+\n");
	
	// box info
	for(i=0; i<this->size; i++)
		printf("| %4d ", *(this->start + i*sizeof(T)));
	printf("|\n");

	// bottom of box
	for(i=0; i<this->size; i++)
		printf("+------");
	printf("+\n");

	// location
	for(i=0, len = (this->ptr - this->start) / sizeof(T); i<len; i++)
		printf("       ");
	printf("   /\\\n\n");

	//return *this;
}

template <class T>
bool TuringTape<T>::left() {
	if(this->ptr > this->start)
		this->ptr--;
#ifdef WRAP
	else
		this->ptr = this->start + this->size * sizeof(T);
#else
	else
		return false;
#endif
	return true;
}

template <class T>
bool TuringTape<T>::right() {
	if(this->ptr < this->start + this->size)
		this->ptr++;
#ifdef WRAP
	else
		this->ptr = this->start;
#else
	else
		return false;
#endif
	return true;
}

template <class T>
void TuringTape<T>::inc() {
	(*this->ptr)++;
	//return *this;
}

template <class T>
void TuringTape<T>::dec() {
	(*this->ptr)--;
	//return *this;
}