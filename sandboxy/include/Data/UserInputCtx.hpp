#pragma once

#include <unordered_map>

#include <SDL.h>

namespace Sandboxy {

struct UserInputCtx {
  Sint32 m_x;
  Sint32 m_y;
  Uint8 lb_pressed = false;
  Uint8 rb_pressed = false;
  std::unordered_map<Uint32, bool> keys_pressed;
};
using UserInputCtxPtr = std::shared_ptr<UserInputCtx>;

} // namespace Sandboxy
