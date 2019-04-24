#pragma once

#include <atomic>
#include <functional>
#include <mutex>
#include <thread>

namespace Sandboxy {
//

class Stoppable {
public:
  Stoppable() = default;
  Stoppable(std::function<void(void)> &&f) : f_(std::move(f)) {}

  Stoppable(const Stoppable &s) = delete;

  Stoppable &operator=(const Stoppable &s) = delete;

  Stoppable &operator=(Stoppable &&s) {
    s.stop();
    f_ = std::move(s.f_);
    return *this;
  }

  Stoppable(Stoppable &&s) { *this = std::move(s); };

  void start() {
    std::lock_guard<std::mutex> l(m_);
    b_ = true;
    t_ = std::thread([this] {
      while (b_) {
        f_();
      }
    });
  }

  void stop() {
    std::lock_guard<std::mutex> l(m_);
    b_ = false;
    if (t_.joinable()) {
      t_.join();
    }
  }

protected:
  std::function<void(void)> f_;

private:
  std::atomic<bool> b_;
  std::thread t_;
  std::mutex m_;
};

} // namespace Sandboxy