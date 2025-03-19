#ifndef COMPONENTS_RENDERER_OPENGL_HPP_
#define COMPONENTS_RENDERER_OPENGL_HPP_

#include <flecs.hpp>
#include <glad/gl.h>

#include "renderer/opengl/types.hpp"

/**
 * @brief contains components and systems for rendering using OpenGL.
 *
 * @see renderer::opengl::components
 */
namespace renderer::opengl {

/**
 * @class components
 * @brief A Flecs module that contains components for rendering using OpenGL.
 */
struct components {
  /**
   * @brief Imports the components into the world.
   */
  components(flecs::world &world);
};

/**
 * @brief A component that represents an OpenGL buffer of vertex data.
 *
 * @see renderer::opengl::Buffer
 */
class VertexBuffer : public Buffer {};
/**
 * @brief A component that represents an OpenGL buffer of index data,
 *
 *  Stores an index buffer (sometimes called an element buffer).
 *
 * @see renderer::opengl::Buffer
 */
class IndexBuffer : public Buffer {};

/**
 * @brief A relationship which points to an entity with a Program component.
 * @see renderer::opengl::Program
 */
struct UsingShaderProgram {};
/**
 * @brief A relationship which points to an entity with a VertexArray component.
 * @see renderer::opengl::VertexArray
 */
struct UsingVertexArray {};

} // namespace renderer::opengl

#endif // COMPONENTS_RENDERER_OPENGL_HPP_