#pragma once

#include <memory>

#include <View/Color.hpp>

namespace Sandboxy {

struct Entity {

  Entity(size_t creation_time)
      : id_(0), hp_(0), creation_time_(creation_time),
        current_time_(creation_time) {}

  ~Entity() = default;

  size_t id_;
  Color color_;
  size_t hp_;
  size_t creation_time_;
  size_t current_time_;
};

typedef std::shared_ptr<Entity> EntityPtr;

} // namespace Sandboxy
