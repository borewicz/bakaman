#pragma once

#include <map>
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H  

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shaderprogram.h"

struct Character {
	GLuint TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	GLuint Advance;
};

class TextRenderer
{
private:
	GLuint VAO, VBO, screenWidth, screenHeight;
	ShaderProgram *shaderProgram;

	std::map<GLchar, Character> Characters;

	void configShader();
	void configText();

public:
	void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	static TextRenderer& getTextRender();
	static void destroyTextRender();
public:
	TextRenderer(GLuint screenWidth, GLuint screenHeight);
	TextRenderer();
	~TextRenderer();
	void resizeWindow(GLuint screenWidth, GLuint screenHeight);
};

