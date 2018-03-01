#ifndef STDEXT_SEMAPHORE_H
#define STDEXT_SEMAPHORE_H

#include <condition_variable>
#include <mutex>

namespace stdext {

class semaphore {
public:
  typedef std::unique_lock<std::mutex> lock_type;
  typedef int value_type;

  semaphore() : _value(0) {}

  semaphore(value_type count) : _value(count) {}

  void reset(value_type value) {
    _mutex.lock();
    _value = value;
    _mutex.unlock();
    _cond.notify_all();
  }

  void post() {
    _mutex.lock();
    _value++;
    _mutex.unlock();
    _cond.notify_one();
  }

  void wait() {
    lock_type lock(_mutex);
    _cond.wait(lock, [this] { return _value > 0; });
    _value--;
  }

  template <class Rep, class Period>
  bool wait_for(const std::chrono::duration<Rep, Period> &rel_time) {
    lock_type lock(_mutex);
    if (!_cond.wait_for(lock, rel_time, [this] { return _value > 0; })) {
      return false;
    }
    _value--;
    return true;
  }

  template <class Clock, class Duration>
  bool
  wait_until(const std::chrono::time_point<Clock, Duration> &timeout_time) {
    lock_type lock(_mutex);
    if (!_cond.wait_until(lock, timeout_time, [this] { return _value > 0; })) {
      return false;
    }
    _value--;
    return true;
  }

  value_type value() const { return _value; }

private:
  value_type _value;
  std::mutex _mutex;
  std::condition_variable _cond;
};

} // stdext

#endif // STDEXT_SEMAPHORE_H
