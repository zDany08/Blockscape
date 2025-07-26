#include <stb/stb_image.h>
#include <rendering.hpp>

void enableDepth() {
	glEnable(GL_DEPTH_TEST);
}

void disableDepth() {
	glDisable(GL_DEPTH_TEST);
}

Shader::Shader(Resource resource_, GLenum type_) : resource(resource_), type(type_) {}

ShaderProgram::ShaderProgram() {
	id = glCreateProgram();
}

void ShaderProgram::attachShader(Shader shader) {
	GLuint shaderId = glCreateShader(shader.type);
	std::string shaderContent = shader.resource.toText();
	const char* shaderSource = shaderContent.c_str();
	glShaderSource(shaderId, 1, &shaderSource, NULL);
	glCompileShader(shaderId);
	GLint success;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if(!success) {
		char log[512];
		glGetShaderInfoLog(shaderId, 512, NULL, log);
		std::cerr << "Failed to compile shader \"" << shader.resource.path << "\": " << log << std::endl;
	}
	glAttachShader(id, shaderId);
	glDeleteShader(shaderId);
}

void ShaderProgram::link() {
	glLinkProgram(id);
	GLint success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (success) return;
	char log[512];
	glGetProgramInfoLog(id, 512, NULL, log);
	std::cerr << "Failed to link renderer \"" << id << "\": " << log << std::endl;
}

void ShaderProgram::bind() {
	glUseProgram(id);
}

void ShaderProgram::uniform(GLint value, std::string name) {
	GLint location = glGetUniformLocation(id, name.c_str());
	glUniform1i(location, value);
}

void ShaderProgram::uniform(glm::vec4 value, std::string name) {
	GLint location = glGetUniformLocation(id, name.c_str());
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void ShaderProgram::uniform(glm::mat4 value, std::string name) {
	GLint location = glGetUniformLocation(id, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::unbind() {
	glUseProgram(0);
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(id);
}

VertexArrayObject::VertexArrayObject() {
	glGenVertexArrays(1, &id);
	if(id != 0) return;
	std::cerr << "Failed to generate vertex array object \"" << id << "\"" << std::endl;
}

void VertexArrayObject::bind() {
	glBindVertexArray(id);
}

void VertexArrayObject::unbind() {
	glBindVertexArray(0);
}

VertexArrayObject::~VertexArrayObject() {
	glDeleteVertexArrays(1, &id);
}

BufferObject::BufferObject(GLenum target_) : target(target_) {
	glGenBuffers(1, &id);
	if (id != 0) return;
	std::cerr << "Failed to generate buffer object \"" << id << "\"" << std::endl;
}

void BufferObject::bind() {
	glBindBuffer(target, id);
}

void BufferObject::data(GLsizeiptr size, const GLvoid* data, GLenum usage) {
	glBufferData(target, size, data, usage);
}

void BufferObject::subData(GLintptr offset, GLsizeiptr size, const GLvoid* data) {
	glBufferSubData(target, offset, size, data);
}

void BufferObject::attrib(GLuint index, GLint size, GLenum type, GLsizei stride, GLvoid* pointer) {
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
}

void BufferObject::drawArrays(GLenum mode, GLint first, GLsizei count) {
	glDrawArrays(mode, first, count);
}

void BufferObject::drawElements(GLenum mode, GLsizei count, GLenum type) {
	glDrawElements(mode, count, type, (GLvoid*) 0);
}

GLuint BufferObject::get() {
	return id;
}

void BufferObject::unbind() {
	glBindBuffer(target, 0);
}

BufferObject::~BufferObject() {
	glDeleteBuffers(1, &id);
}

TextureUnit::TextureUnit(int width, int height, int x, int y, int w, int h) : texX((float) x / width), texY((float) y / height), texWidth((float) w / width), texHeight((float) h / height) {}

Texture::Texture(Resource resource) : channels(0), width(0), height(0) {
	glGenTextures(1, &id);
	if(id == 0) {
		std::cerr << "Failed to generate \"" << resource.path << "\" texture" << std::endl;
		return;
	}
	bind();
	stbi_set_flip_vertically_on_load(true);
	unsigned char* img = resource.toImage(&width, &height);
	if(img == NULL) {
		std::cerr << "Failed to load \"" << resource.path << "\" texture" << std::endl;
		return;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	unbind();
	stbi_image_free(img);
}

TextureUnit Texture::get(int x, int y, int w, int h) {
	return TextureUnit(width, height, x, y, w, h);
}

void Texture::bind() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Texture::unbind() {
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}
