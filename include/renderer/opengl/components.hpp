#ifndef COMPONENTS_RENDERER_OPENGL_HPP_
#define COMPONENTS_RENDERER_OPENGL_HPP_

#include <flecs.hpp>
#include <glad/gl.h>

/**
 * @brief contains components and systems for rendering using OpenGL.
 *
 * @see renderer::opengl::Module
 */

/**
 * @brief A Flecs module that contains components for rendering using OpenGL.
 */
struct components {
  /**
   * @brief Imports the components into the world.
   */
  components(flecs::world &world);
};
namespace renderer::opengl {

/**
 * @brief A Flecs module that contains components for rendering using OpenGL.
 */
struct components {
  /**
   * @brief Imports the components into the world.
   */
  components(flecs::world &world);
};

/**
 * @class Buffer
 * @brief A class representing an OpenGL buffer.
 *
 * The Buffer class encapsulates the creation, management, and destruction
 * of an OpenGL buffer object. It provides mechanisms to generate, move,
 * and destroy buffers, as well as to check their validity.
 *
 * Example usage:
 * @code
 * Buffer buffer;
 * if (buffer) {
 *     // Use the buffer
 * }
 * @endcode
 */
class Buffer {
public:
  /**
   * @brief Generate a new buffer.
   */
  Buffer();

  /**
   * @brief Constructs a Buffer object with the given OpenGL buffer ID.
   *
   * @param id The OpenGL buffer ID to be associated with this Buffer object.
   */
  Buffer(GLuint id);

  // Disallow copying Buffer objects
  Buffer(const Buffer &) = delete;
  Buffer &operator=(const Buffer &) = delete;

  /**
   * @brief Move a buffer to a new object.
   */
  Buffer(Buffer &&other) noexcept;
  /**
   * @brief Move a buffer to another object.
   */
  Buffer &operator=(Buffer &&other) noexcept;

  /**
   * @brief Destroy the buffer.
   */
  ~Buffer();

  /**
   * @brief Test if a buffer is valid.
   * @returns true if the buffer is valid (nonzero ID), false otherwise.
   */
  [[nodiscard]] operator bool() const { return id_ != 0; }

  /**
   * @brief Convert a Buffer to its raW OpenGL name.
   */
  [[nodiscard]] operator GLuint() const { return id_; }

protected:
  GLuint id_ = 0; /**< The OpenGL buffer ID / name */
};

class ArrayBuffer : public Buffer {
public:
  /**
   * @brief Binds the buffer to the GL_ARRAY_BUFFER target.
   */
  void bind() const { glBindBuffer(GL_ARRAY_BUFFER, id_); }

public: // Static methods
  /**
   * @brief Uploads data to the currently bound OpenGL array buffer.
   *
   * This function is Static, it uploads data to whatever is bound to
   * GL_ARRAY_BUFFER target.
   *
   * @param size Specifies the size in bytes of the data to upload.
   * @param data A pointer to the new data that will be copied into the buffer.
   * @param usage Specifies the expected usage pattern of the data store.
   *              Possible values are GL_STREAM_DRAW, GL_STATIC_DRAW, and
   * GL_DYNAMIC_DRAW.
   * @see glBufferData
   */
  static void data(GLsizeiptr size, const void *data, GLenum usage) noexcept {
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
  }
};

} // namespace renderer::opengl

#endif // COMPONENTS_RENDERER_OPENGL_HPP_