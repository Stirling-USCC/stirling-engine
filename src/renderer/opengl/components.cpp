#include "renderer/opengl/components.hpp"

#include <SDL3/SDL_log.h>
#include <flecs.hpp>
#include <glad/gl.h>

#include "flecs/addons/cpp/c_types.hpp"
#include "renderer/opengl/types.hpp"

namespace renderer::opengl {

// Module renderer.opengl.components:

components::components(flecs::world &world) {
  world.module<components>("renderer.opengl.components");

  // Components
  world.component<VertexBuffer>();
  world.component<IndexBuffer>();
  world.component<VertexArray>();
  world.component<Program>();
  // Relationships
  world.component<UsingShaderProgram>().add(flecs::Relationship);
  world.component<UsingVertexArray>().add(flecs::Relationship);
}

} // namespace renderer::opengl