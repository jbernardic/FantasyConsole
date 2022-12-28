#pragma once
#include "SpriteBatch.h"
class Text
{
public:
	static void DrawInput(glm::vec2 position);
	static void Init(const char* texture, glm::vec2 cellSize);
	static std::unique_ptr<SpriteBatch> SB;
	static const char* TextureName;
	static glm::vec2 CellSize;
};

