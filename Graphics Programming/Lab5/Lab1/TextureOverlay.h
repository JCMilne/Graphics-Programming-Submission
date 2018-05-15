#pragma once
#include <string>
#include "Texture.h"
#include "SceneDisplay.h"
#include "Mesh.h"
#include <gl\glew.h>
#include <glm\glm.hpp>
#include <vector>


class TextureOverlay
{
public:
	TextureOverlay();
	~TextureOverlay();
	void drawOL(GLuint program);
	void init(const std::string& fileName);

private:
	Texture texture;
};

