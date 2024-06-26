#pragma once

#include "Vector2.h"
#include "Picture.h"

class Object {
	public:
		Vector2 position;
		Picture picture;

		Object() {}
		Object(int a, int b) {
			this->position.x = a;
			this->position.y = b;
		}
		Object(Vector2 pos) {
			this->position.x = pos.x;
			this->position.y = pos.y;
		}
		Object(int a, int b, Picture pic) {
			this->position.x = a;
			this->position.y = b;
			this->picture = pic;
		}
		Object(Vector2 pos, Picture pic) {
			this->position.x = pos.x;
			this->position.y = pos.y;
			this->picture = pic;
		}
		
		
		
};
