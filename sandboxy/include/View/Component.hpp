#pragma once

#include <SDL.h>

namespace Sandboxy {

class Component {
public:
  Component(SDL_Rect display_zone) : display_zone_(display_zone){};

  virtual void display(SDL_Renderer *renderer) = 0;

  SDL_Rect getDisplayZone() { return display_zone_; }

private:
  SDL_Rect display_zone_;
};

class CompositeComponent : public Component {
  using Component::Component;

public:
  void display(SDL_Renderer *renderer) {
    for (auto &sub : sub_components_) {
      sub.display(renderer);
    }
  }

  virtual void addComponent(Component &&component) {
    sub_components_.push_back(std::move(component));
  }

private:
  std::vector<Component> sub_components_;
};

class Clickable : public Component {
public:
  template <typename Lambda> void onClick(SDL_Renderer *renderer);
};

} // namespace Sandboxy