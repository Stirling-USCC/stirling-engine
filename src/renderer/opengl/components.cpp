#include "renderer/opengl/components.hpp"

#include <SDL3/SDL_log.h>
#include <flecs.hpp>
#include <glad/gl.h>

namespace renderer::opengl {

// Module renderer.opengl.components:

components::components(flecs::world &world) {
  world.module<components>("renderer.opengl.components");

  world.component<Name>();
  world.component<Buffer>("Buffer").is_a<Name>();
  world.component<ArrayBuffer>().is_a<Buffer>();
}

// Component: Name

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

// Component Buffer:

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