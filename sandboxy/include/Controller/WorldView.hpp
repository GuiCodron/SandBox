#pragma once

#include <chrono>
#include <random>

#include "Controller/UserInput.hpp"
#include "Data/CreationPanel.hpp"

namespace Sandboxy {

using namespace std::chrono_literals;

class WorldViewController {
public:
  WorldViewController(WorldFramePtr wf, CreationPanelCtxPtr creation_ctx,
                      UserInputCtxPtr user_ctx, UserEventLoopPtr user_loop)
      : wf_(wf), creation_ctx_(creation_ctx), user_ctx_(user_ctx),
        user_loop_(user_loop) {
    user_loop_->registerHandler(
        SDL_MOUSEBUTTONDOWN, [this](const SDL_Event &e, UserInputCtxPtr ctx) {
          this->addEntity(e, ctx);
        });
  }

  void addEntity(const SDL_Event &e, UserInputCtxPtr ctx) {
    if (e.button.button == SDL_BUTTON_LEFT) {
      size_t x = e.button.x / PIX_WIDTH;
      size_t y = e.button.y / PIX_HEIGHT;
      std::cout << "addEntity event at " << x << ", " << y << "\n";
      wf_->frame[x][y] = createEntity();
      // std::thread t([this] {
      //   std::cout << "press thread started\n";
      //   while (user_ctx_->lb_pressed) {
      //     std::this_thread::sleep_for(100ms);
      //     std::cout << "Button still pressed\n";
      //     if (user_ctx_->lb_pressed)

      //       std::cout << "addEntity event at " << user_ctx_->m_x << ", "
      //                 << user_ctx_->m_y << " done\n";
      //     wf_->frame[user_ctx_->m_x][user_ctx_->m_y] = createEntity();
      //   }
      // });
    }
  }

  EntityPtr createEntity() {
    auto idx = creation_ctx_->sel_idx;

    auto e = std::make_shared<Entity>(1);
    std::cout << "entity created\n";
    e->color_ = {static_cast<uint8_t>(std::rand()),
                 static_cast<uint8_t>(std::rand()),
                 static_cast<uint8_t>(std::rand())};
    std::cout << "Color " << e->color_ << " added\n";
    return e;
  }

private:
  WorldFramePtr wf_;
  CreationPanelCtxPtr creation_ctx_;
  UserInputCtxPtr user_ctx_;
  UserEventLoopPtr user_loop_;
};

} // namespace Sandboxy