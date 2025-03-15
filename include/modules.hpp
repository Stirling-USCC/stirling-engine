#ifndef MODULES_HPP_
#define MODULES_HPP_

#include <flecs.h>
#include <flecs/addons/cpp/flecs.hpp>

#include "renderer/opengl/components.hpp"

struct all_engine_modules {
  all_engine_modules(flecs::world &world) {
    world.import <renderer::opengl::components>();
  }
};

#endif // MODULES_HPP_