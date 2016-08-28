#include <vector>

#include "GL/glew.h"
#include "shaderprogram.h"
#include "tga.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "obj_loader.h"

class Object
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.

	GLuint vertexBuffer, uvBuffer;
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
	glm::mat4 *_extraMatrix;
public:
	Object(const char *file, const char *texture, ShaderProgram *sp);
	void draw();
	float x() { return _x; }
	float y() { return _y; }
	float z() { return _z; }
	void setX(float x) { this->_x = x; }
	void setY(float y) { this->_y = y; }
	void setZ(float z) { this->_z = z; }
	void setExtraMatrix(glm::mat4 *mat) { this->_extraMatrix = mat; }
	glm::mat4 *extraMatrix() { return _extraMatrix;  }
	~Object();
};