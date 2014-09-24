#pragma once
//#define WRAP

/**
 * A special type of linked list or array which make only
 * allows the operations of a Turing Tape
 */
template <class T>
class TuringTape {
	size_t size;
	T* start;
	T* ptr;

public:
	TuringTape(size_t = 10);
	~TuringTape() { free(start); delete ptr, size; }

	void show();

	// basic movements
	inline bool left();
	inline bool right();
	inline void inc();
	inline void dec();

	inline T get()									{ return *ptr; }
	//inline bool operator== (const T t)				{ return t == get(); }
	//inline bool operator> (const T t)				{ return t >  get(); }
	//inline bool operator< (const T t)				{ return t <  get(); }

	inline void set(T t)							{ *ptr = t; }
	//inline TuringTape<T>& operator= (const T t)		{ set(t); }


	// highrt
	//inline TuringTape& operator>> (const size_t) { (*ptr)++; return *this; }


	inline bool move();
	inline bool aimSto();

	//inline TuringTape<T>& operator++ ()				{ (*ptr)++; return *this; }
	//inline TuringTape<T>& operator+= (const T t)	{ (*ptr) += t; return *this; }

	//inline TuringTape<T>& operator-- ()				{ (*ptr)--; return *this; }
	//inline TuringTape<T>& operator-= (const T t)	{ (*ptr) -= t; return *this; }

};