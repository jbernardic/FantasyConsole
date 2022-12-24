#include "Collisions.h"
#include<iostream>
bool Collisions::CheckCollision(Bounds bounds1, Bounds bounds2) {
	if (bounds1.type == BoundsType::RECTANGLE && bounds2.type == BoundsType::RECTANGLE) {
		glm::vec2 pos1 = bounds1.pos;
		glm::vec2 size1 = bounds1.size;
		glm::vec2 pos2 = bounds2.pos;
		glm::vec2 size2 = bounds2.size;
		bool rightside = pos1.x + size1.x / 2 >= pos2.x - size2.x / 2;
		bool leftside = pos1.x - size1.x / 2 <= pos2.x + size2.x / 2;
		bool bottomside = pos1.y + size1.y / 2 >= pos2.y - size2.y / 2;
		bool topside = pos1.y - size1.y / 2 <= pos2.y + size2.y / 2;
		bool result = rightside && leftside && bottomside && topside;
		return result;
	}
	else if (bounds1.type == BoundsType::CIRCLE && bounds2.type == BoundsType::CIRCLE) {
		glm::vec2 pos1 = bounds1.pos;
		glm::vec2 pos2 = bounds2.pos;
		bool result = glm::distance(pos1, pos2) <= bounds1.size.x + bounds2.size.x;
		return result;
	}
	return false;
}