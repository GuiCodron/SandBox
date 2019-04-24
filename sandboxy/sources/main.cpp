#include <iostream>

#include <Controller/WorldView.hpp>
#include <Front.hpp>
#include <WorldRepresentation.hpp>

#define WIDTH 1080
#define HEIGHT 720
#define FRAME_WIDTH (WIDTH / PIX_WIDTH)
#define FRAME_HEIGHT (HEIGHT / PIX_HEIGHT)

namespace Sandboxy {
using namespace std::chrono_literals;

void random_gen(WorldFramePtr wf) {

  for (size_t k = 0; k < 30; k++) {
    auto start = std::chrono::steady_clock::now();
    size_t w = wf->frame.size();
    size_t h = wf->frame[0].size();
    for (size_t i = 0; i < w; i++) {
      for (size_t j = 0; j < h; j++) {
        auto r_val = std::rand() % 100;
        if (r_val < 25) {
          wf->frame[i][j] = std::make_shared<Entity>(1);
        } else {
          wf->frame[i][j] = nullptr;
        }
      }
    }
    std::this_thread::sleep_until(start + 333ms);
  }
}

void test() {
  SDL_Window *window_ = NULL;
  SDL_Renderer *renderer_ = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    throw std::runtime_error("could not create window");
  } else {
    window_ =
        SDL_CreateWindow("Sandboxy", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
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
  SDL_Event e;
  SDL_Rect rect{0, 0, 20, 20};
  int vx = 1;
  int vy = 1;
  while (true) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == 27) // ESC
          exit(0);
      }
      if (rect.w + rect.x + vx > 800 || rect.w + vx < 0) {
        vx *= -1;
      }
      if (rect.h + rect.y + vy > 800 || rect.h + vy < 0) {
        vy *= -1;
      }
      rect.x += vx;
      rect.y += vy;
      SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0xFF);
      SDL_RenderClear(renderer_);
      SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 0xFF);
      SDL_RenderFillRect(renderer_, &rect);
      SDL_RenderPresent(renderer_);
    }
  }
}

int run(int argc, char *argv[]) {
  auto duration = std::chrono::steady_clock::now().time_since_epoch();
  auto ns_duration =
      std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
  std::srand(ns_duration.count());

  auto wf = std::make_shared<WorldFrame>(FRAME_WIDTH, FRAME_HEIGHT);
  auto user_input_ctx = std::make_shared<UserInputCtx>();
  auto user_loop = std::make_shared<UserEventLoop>(user_input_ctx);
  auto creation_ctx = std::make_shared<CreationPanelCtx>();
  auto sw = std::make_shared<SDLWrapper>(wf, user_loop);
  auto wvc = WorldViewController(wf, creation_ctx, user_input_ctx, user_loop);
  sw->start();
  return 0;
}

} // namespace Sandboxy

int main(int argc, char *argv[]) {
  //
  Sandboxy::test();
  return 0;
  // return Sandboxy::run(argc, argv);
}
