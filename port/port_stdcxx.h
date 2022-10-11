#pragma once

#if defined(__has_include)
#if __has_include("port/port_config.h")
#include "port/port_config.h"
#endif
#endif

#if HAVE_CRC32C
#include <crc32c/crc32c.h>
#endif  // HAVE_CRC32C
#if HAVE_SNAPPY
#include <snappy.h>
#endif  // HAVE_SNAPPY

#include <cassert>
#include <condition_variable>  // NOLINT
#include <cstddef>
#include <cstdint>
#include <mutex>  // NOLINT
#include <string>

#include "port/thread_annotations.h"

namespace qstore {
namespace port {
class CondVar;

class CAPABILITY("mutex") Mutex {
 private:
  friend class CondVar;
  std::mutex mu_;

 public:
  Mutex() = default;
  Mutex(const Mutex &) = delete;
  Mutex &operator=(const Mutex &) = delete;
  ~Mutex() = default;

  void Lock() ACQUIRE() { mu_.lock(); }
  void Unlock() RELEASE() { mu_.unlock(); }
  void AssertHeld() ASSERT_CAPABILITY() {}
};

class CondVar {
 private:
  std::condition_variable cv_;
  Mutex *const mu_;

 public:
  explicit CondVar(Mutex *mu) : mu_(mu) { assert(mu != nullptr); }
  CondVar(const CondVar &) = delete;
  CondVar &operator=(const CondVar &) = delete;

  void Wait() {
    std::unique_lock<std::mutex> lock(mu_->mu_, std::adopt_lock);
    cv_.wait(lock);
    lock.release();
  }
  void Signal() { cv_.notify_one(); }
  void SignalAll() { cv_.notify_all(); }
};

}  // namespace port
}  // namespace qstore