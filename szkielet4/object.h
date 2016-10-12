#pragma once

#include <vector>

#include "GL/glew.h"
#include "shaderprogram.h"
#include "tga.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "obj_loader.h"
#include "other.h"

class Object
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; 

	GLuint vertexBuffer, uvBuffer, normalsBuffer;
	GLuint _vao, _vbo;
	int vertexCount, vertexSize;
	void setupVAO();
	void loadIntoVBO();
	GLuint makeBuffer(void *data);
	GLuint readTexture(const char* filename);
	ShaderProgram *shaderProgram;
	void assignVBOtoAttribute(char* attributeName, GLuint bufVBO, int variableSize);
	int textureID;
	void updateModelMatrix();
	float _x = 0.0f, _y = 0.0f, _z = 0.0f;
public:
	Object(const char *file, const char *texture, ShaderProgram *sp);
	void draw();
	float x() { return _x; }
	float y() { return _y; }
	float z() { return _z; }
	int X() {
		return (int)_x / 2;
	}
	int Y() {
		return (int)_y / 2;
	}
	void setX(float x) { this->_x = x; }
	void setY(float y) { this->_y = y; }
	void setZ(float z) { this->_z = z; }
	~Object();
};
