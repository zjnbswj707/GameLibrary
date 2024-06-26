#pragma once


#include "Object.h"
#include "RGB.h"
#include "Picture.h"
#include <vector>
using namespace std;

typedef NoReturn (*DrawFunction) (Object);

class Drawer{
	    vector<vector<RGBColor>> scene;
	    vector<Object> objects;
	public:
		Drawer(){}
		
		NoReturn draw(Object target){
			objects.push_back(target);
			return;
		}
		
		vector<vector<RGBColor>> GetScene(NoArgument){
			for(int i=0;i<int(objects.size());i++){
				Picture pic = objects[i].picture;
				
			}
			objects.clear();
			return scene;
		}
};

Drawer local_drawer;

NoReturn draw(Object object){
	local_drawer.draw(object);
	return;
}

NoReturn Draw(NoArgument);

NoReturn API_Draw(NoArgument){
	while(true)
		Draw();
	return;
}
