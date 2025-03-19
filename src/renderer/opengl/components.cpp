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

  // Example shaders used to render triangle
  opengl::Shader vertex_shader(GL_VERTEX_SHADER, R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    void main() {
      gl_Position = vec4(aPos, 1.0);
    }
  )");
  opengl::Shader fragment_shader(GL_FRAGMENT_SHADER, R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
      FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    }
  )");
  vertex_shader.compile();
  fragment_shader.compile();

  opengl::Program triangleProgram;
  triangleProgram.attach(vertex_shader).attach(fragment_shader).link();

  // Construct an example triangle
  VertexBuffer vertices;
  const float VERTICES[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                            0.0f,  0.0f,  0.5f, 0.0f};
  glBindBuffer(GL_ARRAY_BUFFER, vertices);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

  opengl::VertexArray vao;
  vao.bind();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  flecs::entity triangleRenderable =
      world.entity("triangleRenderable")
          .set<VertexBuffer>(std::move(vertices))
          .set<VertexArray>(std::move(vao))
          .set<Program>(std::move(triangleProgram));
}

} // namespace renderer::opengl