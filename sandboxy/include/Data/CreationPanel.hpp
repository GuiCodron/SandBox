#pragma once

#include <memory>
#include <vector>

namespace Sandboxy {

struct PanelUnit {
  uint16_t id;
  bool selected = false;
};

struct CreationPanelCtx {
  size_t sel_idx = 1;
  std::vector<PanelUnit> units = {
      {0, false}, {1, true}, {2, false}, {3, false}};
};
using CreationPanelCtxPtr = std::shared_ptr<CreationPanelCtx>;

} // namespace Sandboxy
