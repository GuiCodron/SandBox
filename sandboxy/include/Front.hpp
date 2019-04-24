#pragma once

#include <SDL.h>

#include <Controller/UserInput.hpp>
#include <WorldRepresentation.hpp>

#include <chrono>
#include <exception>
#include <iostream>
#include <memory>
#include <thread>
#include <unordered_map>
#include <vector>

#include <View/Color.hpp>

namespace Sandboxy {

class SDLWrapper {
public:
  SDLWrapper(WorldFramePtr w_frame, UserEventLoopPtr user_loop);

  ~SDLWrapper();

  void startDrawLoop();

  void stopDrawLoop();

  void start();

  void stop();

private:
  WorldFramePtr w_frame_;

  // The window renderer
  SDL_Window *window_ = NULL;
  SDL_Renderer *renderer_ = NULL;
  // SDL_Surface* screen_surface_ = NULL;
  UserEventLoopPtr user_loop_;

  std::thread draw_thread_;
  std::atomic<bool> draw_thread_bool_;
};
typedef std::shared_ptr<SDLWrapper> SDLWrapperPtr;

SDLWrapper::~SDLWrapper() {
  // stop threads
  stop();
  // Destroy window
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  // Quit SDL subsystems
  SDL_Quit();
}

SDLWrapper::SDLWrapper(WorldFramePtr w_frame, UserEventLoopPtr user_loop)
    : w_frame_(w_frame), user_loop_(user_loop) {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    throw std::runtime_error("could not create window");
  } else {
    window_ = SDL_CreateWindow(
        "Sandboxy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        w_frame_->frame.size() * PIX_WIDTH,
        w_frame_->frame[0].size() * PIX_HEIGHT, SDL_WINDOW_SHOWN);
    if (window_ == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      throw std::runtime_error("could not create window");
    } else {
      renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
      if (renderer_ == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n",
               SDL_GetError());
        throw std::runtime_error("could not create window");
      }
    }
  }
  user_loop_->registerHandler(SDL_KEYDOWN, [](auto e, auto ctx) {
    if (e.key.keysym.sym == 27) // ESC
      exit(0);
  });
}

void SDLWrapper::startDrawLoop() {
  using namespace std::chrono_literals;
  draw_thread_bool_ = true;

  draw_thread_ = std::thread([this] {

    while (draw_thread_bool_) {
      // SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0xFF);
      // SDL_RenderClear(renderer_);
      auto start = std::chrono::steady_clock::now();
      int w = w_frame_->frame.size();
      int h = w_frame_->frame[0].size();
      for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
          if (auto entity = w_frame_->frame[i][j]) {
            if (entity.get() == nullptr)
              continue;
            // std::cout << "Displaying " << entity->color_ << " at "
            //           << i * PIX_WIDTH << ", " << (h - 1 - j) * PIX_HEIGHT
            //           << "\n";

            SDL_Rect fill_rect;
            fill_rect.x = i * PIX_WIDTH;
            fill_rect.y = (h - 1 - j) * PIX_HEIGHT;
            fill_rect.w = 50;
            fill_rect.h = 50;

            SDL_SetRenderDrawColor(renderer_, 255, 255, 0, 0xFF);
            SDL_RenderFillRect(renderer_, &fill_rect);
          }
        }
      }
      std::this_thread::sleep_until(start + 33ms);
      SDL_RenderPresent(renderer_);
      std::cout << "Frame rendering\n";
    }
  });
}

void SDLWrapper::stopDrawLoop() {
  draw_thread_bool_ = false;
  if (draw_thread_.joinable()) {
    draw_thread_.join();
  }
}

void SDLWrapper::start() {
  startDrawLoop();
  user_loop_->start();
}
void SDLWrapper::stop() {
  stopDrawLoop();
  user_loop_->stop();
}

} // namespace Sandboxy