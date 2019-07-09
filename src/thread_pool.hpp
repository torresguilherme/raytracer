#include <thread>
#include <vector>
#include <functional>
#include <queue>
#include <condition_variable>
#include <mutex>

template <typename Task>
struct ThreadPool
{
    std::queue<Task> tasks;
    std::mutex lock;
    std::condition_variable stop;
    std::size_t num_threads;
    std::vector<std::thread> threads;

    ThreadPool(std::size_t nt);
    ~ThreadPool() noexcept;

    void emplace(Task new_task);
    void join_and_stop();
};
