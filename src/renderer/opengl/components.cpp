#include "renderer/opengl/components.hpp"

#include <SDL3/SDL_log.h>
#include <flecs.hpp>
#include <glad/gl.h>

#include "renderer/opengl/types.hpp"

namespace renderer::opengl {

// Module renderer.opengl.components:

components::components(flecs::world &world) {
  world.module<components>("renderer.opengl.components");

  world.component<Name>();
  world.component<Buffer>("Buffer").is_a<Name>();
  world.component<ArrayBuffer>().is_a<Buffer>();
}

} // namespace renderer::opengl