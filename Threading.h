#pragma once

#include "types.h"
#include "GameFrame.h"
#include <future>
#include <mutex>
#include <thread>

typedef NoReturn (*Function) (NoArgument);

int maxinum_threading_count = 50;
int surplus_threading_count = maxinum_threading_count;
int next_id = 1;
typedef bool Threading_StartReturnValue;
typedef bool Threading_RunReturnValue;

class Threading{
	private:
		Function function;
	public:
		int id;
		
		Threading(){
			id = next_id++;
		}
		Threading(Function init_function){
			function = init_function;
			id = next_id++;
		}
		
		Threading_StartReturnValue Start(NoArgument){
			if(surplus_threading_count == 0){
				return false;
			}
			thread instantiation(function);
			surplus_threading_count--;
			instantiation.detach();
			delete &instantiation;
			surplus_threading_count++;
			return true;
		}
		
		Threading_RunReturnValue Run(NoArgument){
			if(surplus_threading_count == 0){
				return false;
			}
			thread instantiation(function);
			surplus_threading_count--;
			instantiation.join();
			delete &instantiation;
			surplus_threading_count++;
			return true;
		}
};
