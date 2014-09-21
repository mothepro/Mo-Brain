#pragma once
//#define WRAP

typedef char byte;

class TuringTape {
public:
	//TuringTape() { TuringTape(10); };
	TuringTape(size_t);

	TuringTape& show();

	TuringTape& left();
	TuringTape& right();

	TuringTape& inc();
	TuringTape& dec();

	byte get();
	void set(byte);
private:
	size_t size;
	byte* start;
	byte* ptr;
};