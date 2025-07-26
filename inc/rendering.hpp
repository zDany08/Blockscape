#ifndef RENDERING_HPP
#define RENDERING_HPP

#include <resources.hpp>
#include <player.hpp>

void enableDepth();

void disableDepth();

struct Shader {
public:
	Resource resource;
	GLenum type;

	Shader(Resource, GLenum);
};

class ShaderProgram {
private:
	GLuint id;
public:
	ShaderProgram();
	
	void attachShader(Shader);

	void link();

	void bind();

	void uniform(GLint, std::string);

	void uniform(glm::vec4, std::string);

	void uniform(glm::mat4, std::string);

	void unbind();

	~ShaderProgram();
};

class VertexArrayObject {
private:
	GLuint id;
public:
	VertexArrayObject();

	void bind();

	void unbind();

	~VertexArrayObject();
};

class BufferObject {
private:
	GLuint id;
	GLenum target;
public:
	BufferObject(GLenum);

	void bind();

	void data(GLsizeiptr, const GLvoid*, GLenum);

	void subData(GLintptr, GLsizeiptr, const GLvoid*);

	void attrib(GLuint, GLint, GLenum, GLsizei, GLvoid*);

	void drawArrays(GLenum, GLint, GLsizei);

	void drawElements(GLenum, GLsizei, GLenum);

	GLuint get();

	void unbind();

	~BufferObject();
};

struct TextureUnit {
public:
	float texX, texY, texWidth, texHeight;

	TextureUnit(int, int, int, int, int, int);
};

class Texture {
private:
	GLuint id;
	int channels;
public:
	int width, height;

	Texture(Resource);

	TextureUnit get(int, int, int, int);

	void bind();

	void unbind();

	~Texture();
};

#endif
