#include "renderer/opengl/systems.hpp"

#include "SDL3/SDL_log.h"
#include <flecs.hpp>

#include "renderer/opengl/types.hpp"

namespace renderer::opengl {

systems::systems(flecs::world &world) {
  world.module<systems>("renderer.opengl.systems");

  // This module ddepends on the components module, so we need to import it
  // first
  world.import <components>();

  // Query: Program($shader), VertexArray($vao), (UsingShaderProgram, $shader),
  // (UsingVertexArray, $vao)
  world.system<const Program, const VertexArray>("render")
      .term_at(0)
      .src("$shader")
      .term_at(1)
      .src("$vao")
      .with<UsingShaderProgram>("$shader")
      .with<UsingVertexArray>("$vao")
      .with<UsingShaderProgram>("$shader")
      .with<UsingVertexArray>("$vao")
      .kind(flecs::OnUpdate)
      .each(
          [](flecs::entity e, const Program &program, const VertexArray &vao) {
            SDL_Log("Matched entity: %s", e.name().c_str());
            glUseProgram(program);
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);
          });
}

} // namespace renderer::opengl