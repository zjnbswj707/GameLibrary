#pragma once

#include "types.h"
#include <random>
using namespace std;

typedef int RandintReturnValue;
RandintReturnValue Randint(NoArgument){
	random_device rd;
	int mode = rd(), result;
	if(mode == 1){
		ranlux24 engine(rd());
		result = engine();
	}
	if(mode == 2){
		ranlux48 engine(rd());
		result = engine();
	}
	if(mode == 3){
		minstd_rand engine(rd());
		result = engine();
	}
	if(mode == 4){
		minstd_rand0 engine(rd());
		result = engine();
	}
	else{
		mt19937_64 engine(rd());
		result = engine();
	}
	return result;
}

typedef double RandomReturnValue;
RandomReturnValue Random(NoArgument){
	random_device rd;
	int mode = rd();
	double result;
	uniform_real_distribution<> limiter(0.0, 1.0);
	if(mode == 1){
		ranlux24 engine(rd());
		result = limiter(engine);
	}
	if(mode == 2){
		ranlux48 engine(rd());
		result = limiter(engine);
	}
	if(mode == 3){
		minstd_rand engine(rd());
		result = limiter(engine);
	}
	if(mode == 4){
		minstd_rand0 engine(rd());
		result = limiter(engine);
	}
	else{
		mt19937_64 engine(rd());
		result = limiter(engine);
	}
	return result;
}

typedef int RandBetweenReturnValue;
RandBetweenReturnValue RandBetween(int Start, int End){
	if(Start == End) return Start;
	int value = Randint();
	return value % (End - Start + 1) + Start;
}
