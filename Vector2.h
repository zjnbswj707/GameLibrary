#pragma once

class Vector2 {
	public:
		int x, y;
		Vector2() {}
		Vector2(int a, int b) {
			this->x = a;
			this->y = b;
		}
		Vector2 operator+(Vector2 target) const {
			Vector2 newVector;
			newVector.x = this->x + target.x;
			newVector.y = this->y + target.y;
			return newVector;
		}
		Vector2 operator-(Vector2 target) const {
			Vector2 newVector;
			newVector.x = this->x - target.x;
			newVector.y = this->y - target.y;
			return newVector;
		}
		Vector2 operator*(int target) const {
			Vector2 newVector;
			newVector.x = this->x * target;
			return newVector;
		}
		Vector2 operator/(int target) const {
			Vector2 newVector;
			newVector.x = this->x / target;
			return newVector;
		}
		void operator+=(Vector2 target) {
			this->x += target.x;
			this->y += target.y;
			return;
		}
		void operator-=(Vector2 target) {
			this->x -= target.x;
			this->y -= target.y;
			return;
		}
		void operator*=(int target) {
			this->x *= target;
			return;
		}
		void operator/=(int target) {
			this->x /= target;
			return;
		}
};
