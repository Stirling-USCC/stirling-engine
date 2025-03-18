#include "renderer/opengl/types.hpp"

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

} // namespace renderer::opengl