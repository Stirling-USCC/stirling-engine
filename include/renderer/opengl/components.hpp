#ifndef COMPONENTS_RENDERER_OPENGL_HPP_
#define COMPONENTS_RENDERER_OPENGL_HPP_

#include <flecs.hpp>
#include <glad/gl.h>

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

} // namespace renderer::opengl

#endif // COMPONENTS_RENDERER_OPENGL_HPP_