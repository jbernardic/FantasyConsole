#pragma once
#include "Shape.h"

class Collisions {
public:
	static bool CheckCollision(Bounds bounds1, Bounds bounds2);
private:
	Collisions() {}
};