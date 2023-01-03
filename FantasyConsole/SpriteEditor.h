#pragma once
#include <glm/glm.hpp>
#include <VertexArray.h>
#include <IndexBuffer.h>
#include <iostream>
#include <array>
#include "Sprite.h"
#include "SpriteBatch.h"
class SpriteEditor
{
public:
	SpriteEditor(glm::vec2 position, glm::vec2 size, unsigned int gridWidth, unsigned int gridHeight);
	void Draw(SpriteBatch& sb);
	~SpriteEditor();
	glm::vec2 Position;
	bool Active = true;

private:
	glm::vec2 Size;
	glm::uvec2 m_GridSize;
	Sprite* m_Grid;
	bool m_Drawing = false;
};

