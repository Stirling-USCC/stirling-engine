#include "renderer/opengl/components.hpp"

#include <SDL3/SDL_log.h>
#include <glad/gl.h>

namespace renderer::opengl {

// Module renderer.opengl.components:

components::components(flecs::world &world) {
  world.module<components>("renderer.opengl.components");

  world.component<Buffer>("Buffer");
  world.component<ArrayBuffer>().is_a<Buffer>();
}

// Component Buffer:

Buffer::Buffer() { glGenBuffers(1, &id_); }

Buffer::Buffer(GLuint id) : id_(id) {}

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