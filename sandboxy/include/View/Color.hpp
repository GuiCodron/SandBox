#pragma once

#include <ostream>

namespace Sandboxy {

struct Color {
  uint8_t r, g, b;
};

std::ostream &operator<<(std::ostream &os, const Color &c) {
  return os << "c{" << static_cast<int>(c.r) << ", " << static_cast<int>(c.g)
            << ", " << static_cast<int>(c.b) << "}";
}

} // namespace Sandboxy
