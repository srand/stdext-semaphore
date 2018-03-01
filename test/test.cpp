#include <gtest/gtest.h>
#include <stdext/semaphore.h>
#include <thread>

TEST(Semaphore, Wait) {
  stdext::semaphore sem(3);

  sem.wait();

  EXPECT_TRUE(sem.wait_for(std::chrono::nanoseconds(0)));
  EXPECT_TRUE(sem.wait_until(std::chrono::system_clock::now()));

  EXPECT_FALSE(sem.wait_for(std::chrono::nanoseconds(0)));
  EXPECT_FALSE(sem.wait_until(std::chrono::system_clock::now()));
}

TEST(Semaphore, Post) {
  stdext::semaphore sem;
  auto now = std::chrono::system_clock::now();
  auto zero = std::chrono::nanoseconds(0);

  EXPECT_FALSE(sem.wait_until(now));
  sem.post();
  EXPECT_TRUE(sem.wait_until(now));
  EXPECT_FALSE(sem.wait_until(now));

  EXPECT_FALSE(sem.wait_for(zero));
  sem.post();
  EXPECT_TRUE(sem.wait_for(zero));
  EXPECT_FALSE(sem.wait_for(zero));
}

TEST(Semaphore, Threads) {
  stdext::semaphore sem(2);
  auto now = std::chrono::system_clock::now();

  std::thread t1([&sem, now] { sem.wait_until(now); });
  std::thread t2([&sem, now] { sem.wait_until(now); });

  t1.join();
  t2.join();
}

TEST(Semaphore, Reset) {
  stdext::semaphore sem_start, sem_done;

  std::thread t1([&sem_start, &sem_done] {
    sem_start.post();
    sem_done.wait();
  });
  std::thread t2([&sem_start, &sem_done] {
    sem_start.post();
    sem_done.wait();
  });

  sem_start.wait();
  sem_start.wait();

  sem_done.reset(2);

  t1.join();
  t2.join();
}

TEST(Semaphore, Value) {
  stdext::semaphore sem1, sem2(1);
  auto now = std::chrono::system_clock::now();

  EXPECT_EQ(0, sem1.value());
  EXPECT_EQ(1, sem2.value());

  sem1.post();
  EXPECT_EQ(1, sem1.value());

  sem1.wait();
  EXPECT_EQ(0, sem1.value());

  sem1.wait_until(now);
  EXPECT_EQ(0, sem1.value());
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
