#include "renderer/opengl/types.hpp"

#include <stdexcept>

namespace renderer::opengl {

// Class: Name

Name::Name(Name &&other) noexcept {
  id_ = other.id_;
  other.id_ = 0;
}

Name &Name::operator=(Name &&other) noexcept {
  if (this != &other) {
    id_ = other.id_;
    other.id_ = 0;
  }
  return *this;
}

// Class: Buffer:

Buffer::Buffer() { glGenBuffers(1, &id_); }

Buffer::Buffer(Buffer &&other) noexcept {
  id_ = other.id_;
  other.id_ = 0;
}

Buffer &Buffer::operator=(Buffer &&other) noexcept {
  if (this != &other) {
    id_ = other.id_;
    other.id_ = 0;
  }
  return *this;
}

Buffer::~Buffer() {
  if (id_ != 0) {
    glDeleteBuffers(1, &id_);
  }
}

// Class: Shader

Shader::Shader(GLenum type) : Name(glCreateShader(type)) {
  if (!*this) {
    throw std::runtime_error("Failed to create shader");
  }
}

Shader::Shader(GLenum type, const char *source) : Shader(type) {
  setSource(source);
}

Shader::Shader(Shader &&other) noexcept {
  id_ = other.id_;
  other.id_ = 0;
}

Shader &Shader::operator=(Shader &&other) noexcept {
  if (this != &other) {
    id_ = other.id_;
    other.id_ = 0;
  }
  return *this;
}

Shader::~Shader() noexcept {
  if (id_ != 0) {
    glDeleteShader(id_);
  }
}

void Shader::setSource(const char *source, GLint size) {
  glShaderSource(id_, 1, &source, &size);
}

void Shader::compile() {
  glCompileShader(id_);
  GLint success;
  glGetShaderiv(id_, GL_COMPILE_STATUS, &success);
  // If the compilation failed, get the error log and throw an exception
  if (!success) {
    GLint error_length;
    glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &error_length);
    // Allocate string of the right size
    std::string log(error_length, '\0');
    glGetShaderInfoLog(id_, error_length, nullptr, log.data());
    throw std::runtime_error("Failed to compile shader: " + log);
  }
}

// Class: Program

Program::Program() : Name(glCreateProgram()) {
  if (!*this) {
    throw std::runtime_error("Failed to create shader program");
  }
}

Program::Program(Program &&other) noexcept {
  id_ = other.id_;
  other.id_ = 0;
}

Program &Program::operator=(Program &&other) noexcept {
  if (this != &other) {
    id_ = other.id_;
    other.id_ = 0;
  }
  return *this;
}

Program &Program::attach(const Shader &shader) & {
  glAttachShader(id_, shader);
  return *this;
}

void Program::link() {
  glLinkProgram(id_);
  GLint success;
  glGetProgramiv(id_, GL_LINK_STATUS, &success);
  // If the linking failed, get the error log and throw an exception
  if (!success) {
    GLint error_length;
    glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &error_length);
    // Allocate string of the right size
    std::string log(error_length, '\0');
    glGetProgramInfoLog(id_, error_length, nullptr, log.data());
    throw std::runtime_error("Failed to link shader program: " + log);
  }
}

} // namespace renderer::opengl