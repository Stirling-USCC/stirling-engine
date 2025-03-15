project(GLAD)

# Compile the GLAD OpenGL bindings into a static library, which can be linked into the engine
add_library(glad STATIC src/gl.c)
target_include_directories(glad PUBLIC include)