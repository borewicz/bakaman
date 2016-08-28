#include "object.h"

GLuint Object::readTexture(const char* filename) {
	GLuint tex;
	TGAImg img;
	glActiveTexture(GL_TEXTURE0);
	if (img.Load(filename) == IMG_OK) {
		glGenTextures(1, &tex); //Zainicjuj uchwyt tex
		glBindTexture(GL_TEXTURE_2D, tex); //Przetwarzaj uchwyt tex
		if (img.GetBPP() == 24) //Obrazek 24bit
			glTexImage2D(GL_TEXTURE_2D, 0, 3, img.GetWidth(), img.GetHeight(), 0,
			GL_RGB, GL_UNSIGNED_BYTE, img.GetImg());
		else if (img.GetBPP() == 32) //Obrazek 32bit
			glTexImage2D(GL_TEXTURE_2D, 0, 4, img.GetWidth(), img.GetHeight(), 0,
			GL_RGBA, GL_UNSIGNED_BYTE, img.GetImg());
		else {
			printf("Nieobs³ugiwany format obrazka w pliku: %s \n", filename);
		}
	}
	else {
		printf("B³¹d przy wczytywaniu pliku: %s\n", filename);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	return tex;
}

Object::Object(const char *file, const char *texture, ShaderProgram *sp)
{
	this->shaderProgram = sp;
	textureID = readTexture(texture);
	bool result = loadObject(file, vertices, uvs, normals);
	setupVAO();
}

void Object::assignVBOtoAttribute(char* attributeName, GLuint bufVBO, int variableSize) 
{
	GLuint location = shaderProgram->getAttribLocation(attributeName); //Pobierz numery slotów dla atrybutu
	glBindBuffer(GL_ARRAY_BUFFER, bufVBO);  //Uaktywnij uchwyt VBO 
	glEnableVertexAttribArray(location); //W³¹cz u¿ywanie atrybutu o numerze slotu zapisanym w zmiennej location
	glVertexAttribPointer(location, variableSize, GL_FLOAT, GL_FALSE, 0, NULL); //Dane do slotu location maj¹ byæ brane z aktywnego VBO
}

//Procedura tworz¹ca VAO - "obiekt" OpenGL wi¹¿¹cy numery slotów atrybutów z buforami VBO
void Object::setupVAO() {
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	assignVBOtoAttribute("vertex", vertexBuffer, 3); //"vertex" odnosi siê do deklaracji "in vec4 vertex;" w vertex shaderze
	//assignVBOtoAttribute("color", makeBuffer(colors), sizeof(glm::vec4)); //"color" odnosi siê do deklaracji "in vec4 color;" w vertex shaderze
	//assignVBOtoAttribute("normal", makeBuffer(normals), sizeof(glm::vec4)); //"normal" odnosi siê do deklaracji "in vec4 normal;" w vertex shaderze
	assignVBOtoAttribute("texCoord", uvBuffer, 2); //"texCoord" odnosi siê do deklaracji "in vec2 texCoord;" w vertex shaderze

	glBindVertexArray(0);
}

Object::~Object()
{
	glDeleteBuffers(1, &uvBuffer);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &_vao);
}

void Object::draw() 
{
	updateModelMatrix();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(shaderProgram->getUniformLocation("textureMap0"), 0);
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	GLuint err = glGetError();
	glBindVertexArray(0);
}

void Object::updateModelMatrix()
{
	glm::mat4 matM = glm::translate(glm::mat4(1.0f), glm::vec3(this->_x, this->_y, this->_z));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, glm::value_ptr(matM));
}