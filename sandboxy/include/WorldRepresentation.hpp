#pragma once

#include <map>
#include <memory>
#include <vector>

#include <Entity/Entity.hpp>

#define PIX_WIDTH 2
#define PIX_HEIGHT 2

namespace Sandboxy {

class WorldFrame {
public:
  WorldFrame(size_t width, size_t height) {
    frame = std::vector<std::vector<EntityPtr>>(width,
                                                std::vector<EntityPtr>(height));
  }

public:
  std::vector<std::vector<EntityPtr>> frame;
};

typedef std::shared_ptr<WorldFrame> WorldFramePtr;

} // namespace Sandboxy