#pragma once

#include "RGB.h"
#include "types.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Picture {
		string path;
		fstream stream;
		int floor;
		vector<vector<RGBColor>> value;
	public:
		Picture() {}
		Picture(const Picture& target){
			this->value = target.value;
		}
		Picture(vector<vector<RGBColor>> picval, int picfloor = 1){
			this->value = picval;
			this->floor = picfloor;
		}
		Picture(string filepath, int picfloor = 1) {
			this->stream.open(filepath, ios_base::in | ios_base::binary);
			this->floor = picfloor;
		}
		
		NoReturn NextFloor(NoArgument){
			this->floor++;
			return;
		}
		
		NoReturn PrevFloor(NoArgument){
			this->floor--;
			return;
		}
		
		vector<vector<RGBColor>> GetValue(NoArgument){
			return this->value;
		}
		
		NoReturn operator=(Picture pic){
			if(this != &pic) this->value = pic.GetValue();
			return;
		}


};
