#ifndef MODULES_HPP_
#define MODULES_HPP_

#include <flecs.hpp>

#include "renderer/opengl/components.hpp"
#include "renderer/opengl/systems.hpp"

struct all_engine_modules {
  all_engine_modules(flecs::world &world) {
    world.import <renderer::opengl::components>();
    world.import <renderer::opengl::systems>();
  }
};

#endif // MODULES_HPP_