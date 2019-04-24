#pragma once

#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

#include <SDL.h>
#include <Data/UserInputCtx.hpp>
#include <Toolset/Stoppable.hpp>
#include <WorldRepresentation.hpp>

namespace Sandboxy {

void handleKeyboard(const SDL_Event &e, UserInputCtxPtr ctx);

void handleMouseButton(const SDL_Event &e, UserInputCtxPtr ctx);

void handleMouseMotion(const SDL_Event &e, UserInputCtxPtr ctx);

typedef std::function<void(const SDL_Event &, UserInputCtxPtr)> EventHandler;
class UserEventLoop {
public:
  UserEventLoop(UserInputCtxPtr ctx) : ctx_(ctx) {
    registerHandler(SDL_KEYDOWN, handleKeyboard);
    registerHandler(SDL_KEYUP, handleKeyboard);
    registerHandler(SDL_MOUSEBUTTONDOWN, handleMouseButton);
    registerHandler(SDL_MOUSEBUTTONUP, handleMouseButton);
    registerHandler(SDL_MOUSEMOTION, handleMouseMotion);
  }

  void registerHandler(uint16_t type, EventHandler h) {
    handlers_map_[type].push_back(h);
  }

  void start() {
    b_ = true;
    while (b_) {
      SDL_Event e;
      if (SDL_WaitEventTimeout(&e, 10) > 0) {
        for (auto &h : handlers_map_[e.type]) {
          h(e, ctx_);
        }
      }
    }
  }

  void stop() { b_ = false; }

private:
  UserInputCtxPtr ctx_;

  std::unordered_map<uint16_t, std::vector<EventHandler>> handlers_map_;

  std::atomic<bool> b_;
};

using UserEventLoopPtr = std::shared_ptr<UserEventLoop>;

void handleKeyboard(const SDL_Event &e, UserInputCtxPtr ctx) {
  ctx->keys_pressed[e.key.keysym.sym] = (e.key.state == SDL_PRESSED);
}

void handleMouseMotion(const SDL_Event &e, UserInputCtxPtr ctx) {
  ctx->m_x = e.motion.x / PIX_WIDTH;
  ctx->m_y = e.motion.y / PIX_HEIGHT;
//   printf("x,y - %4d, %4d\n", ctx->m_x, ctx->m_y);
}

void handleMouseButton(const SDL_Event &e, UserInputCtxPtr ctx) {
  ctx->m_x = e.button.x / PIX_WIDTH;
  ctx->m_y = e.button.y / PIX_HEIGHT;
  std::cout << "button event: "
            << ((e.button.state == SDL_PRESSED) ? "pressed" : "released")
            << "\n";

  if (e.button.button == SDL_BUTTON_LEFT) {
    ctx->lb_pressed = (e.button.state == SDL_PRESSED);
  } else if (e.button.button == SDL_BUTTON_RIGHT) {
    ctx->rb_pressed = (e.button.state == SDL_PRESSED);
  }
}

} // namespace Sandboxy
