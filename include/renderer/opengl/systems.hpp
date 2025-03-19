#ifndef RENDERER_OPENGL_SYSTEMS_HPP_
#define RENDERER_OPENGL_SYSTEMS_HPP_

#include <flecs.hpp>

#include "renderer/opengl/components.hpp"

namespace renderer::opengl {

struct systems {
  systems(flecs::world &world);
};

} // namespace renderer::opengl

#endif // RENDERER_OPENGL_SYSTEMS_HPP_