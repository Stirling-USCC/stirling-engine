#ifndef RENDERER_OPENGL_TYPES_HPPP_
#define RENDERER_OPENGL_TYPES_HPPP_

#include <glad/gl.h>

namespace renderer::opengl {

/**
 * @class Name
 * @brief A class representing an OpenGL name/ID.
 *
 * This class encapsulates an OpenGL name/ID and provides mechanisms to manage
 * its validity and movement. Copying of Name objects is disallowed to prevent
 * accidental duplication or double-freeing of OpenGL resources.
 *
 * Classes that manage OpenGL resources should inherit from Name, to provide the
 * common helper methods. They *must* also implement a destructor if the
 * resource needs to be freed.
 *
 * @note The class provides conversion operators to check the validity of the
 * name and to retrieve the raw OpenGL name.
 */
class Name {
public:
  /**
   * @brief Construct a default, invalid Name object.
   */
  Name() = default;
  /**
   * @brief Construct a Name object with an existing OpenGL name.
   *
   * @param id The OpenGL name to be associated with this Name object.
   */
  Name(GLuint id) : id_(id) {}

  // Disallow copying Name objects
  Name(const Name &) = delete;
  Name &operator=(const Name &) = delete;

  /**
   * @brief Move a Name to a new object.
   */
  Name(Name &&other) noexcept;
  /**
   * @brief Move a Name to another object.
   */
  Name &operator=(Name &&other) noexcept;

  /**
   * @brief Test if a Name is valid.
   * @returns true if the Name is valid (nonzero ID), false otherwise.
   */
  [[nodiscard]] operator bool() const { return id_ != 0; }

  /**
   * @brief Convert a Name to its raw OpenGL name.
   */
  [[nodiscard]] operator GLuint() const { return id_; }

protected:
  GLuint id_ = 0; /**< The OpenGL ID / name */
};

/**
 * @class Buffer
 * @brief A class representing an OpenGL buffer.
 *
 * The Buffer class encapsulates the creation, management, and destruction
 * of an OpenGL buffer object. It provides mechanisms to generate,
 * and destroy buffers.
 */
class Buffer : public Name {
public:
  /**
   * @brief Generate a new buffer.
   */
  Buffer();

  /**
   * @brief Constructs a Buffer object with an existing OpenGL buffer ID.
   *
   * @param id The OpenGL buffer ID to be associated with this Buffer object.
   */
  Buffer(GLuint id) : Name(id) {}

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

/**
 * @class Shader
 * @brief Represents an OpenGL shader object.
 *
 * The Shader class encapsulates the creation, management, and compilation of
 * OpenGL shader objects. It provides functionality to set the GLSL source
 * code and compile the shader.
 *
 * @see Name
 */
class Shader : public Name {
public:
  /**
   * @brief Constructs a Shader object with the specified type.
   *
   * @param type The type of the shader (e.g., GL_VERTEX_SHADER,
   * GL_FRAGMENT_SHADER).
   */
  Shader(GLenum type);
  /**
   * @brief Constructs a Shader object with the specified type and source code.
   *
   * @param type The type of the shader (e.g., GL_VERTEX_SHADER,
   * GL_FRAGMENT_SHADER).
   * @param source The source code of the shader.
   */
  Shader(GLenum type, const char *source);

  // Disallow copying Shader objects
  Shader(const Shader &) = delete;
  Shader &operator=(const Shader &) = delete;

  /**
   * @brief Move a shader to a new object.
   */
  Shader(Shader &&other) noexcept;
  /**
   * @brief Move a shader to another object.
   */
  Shader &operator=(Shader &&other) noexcept;

  ~Shader() noexcept;

  /**
   * @brief Sets the source code for the shader.
   *
   * @param source The source code of the shader.
   * @param size The length of the source code. If -1, the source code is
   * assumed to be null-terminated.
   *
   * @see glShaderSource
   */
  void setSource(const char *source, GLint size = -1);

  /**
   * @brief Compile the shader.
   *
   * This function compiles the shader source code that was previously set using
   * setSource().
   *
   * @throws std::runtime_error if the shader compilation fails.
   * @see glCompileShader
   */
  void compile();
};

/**
 * @class Program
 * @brief Represents an OpenGL program object.
 *
 * The Program class encapsulates an OpenGL shader program object, providing
 * functionality to attach shaders, link the program, and manage its lifecycle.
 */
class Program : public Name {
public:
  /**
   * @brief Constructs a new Program object.
   */
  Program();
  Program(GLuint id) : Name(id) {}

  // Disallow copying Program objects
  Program(const Program &) = delete;
  Program &operator=(const Program &) = delete;

  /**
   * @brief Move a program to a new object.
   */
  Program(Program &&other) noexcept;
  /**
   * @brief Move a program to another object.
   */
  Program &operator=(Program &&other) noexcept;

  /**
   * @brief Attaches a shader to the program.
   *
   * Calls to this function can be chained to attach multiple shaders to the
   * program in a readable way.
   *
   * @param shader The shader to attach to the program.
   * @returns A reference to the program object.
   * @see glAttachShader
   */
  Program &attach(const Shader &shader) &;

  /**
   * @brief Links the attached shaders to create an executable program.
   *
   * @throws std::runtime_error if the program linking fails.
   * @see glLinkProgram
   */
  void link();
};

} // namespace renderer::opengl

#endif // RENDERER_OPENGL_TYPES_HPPP_