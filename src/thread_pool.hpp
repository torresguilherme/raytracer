#include <thread>
#include <vector>
#include <functional>
#include <queue>
#include <mutex>

template <class Task>
struct ThreadPool
{
    std::queue<Task> tasks;
    std::mutex lock;
    bool stop;
    std::size_t num_threads;
    std::vector<std::thread> threads;

    ThreadPool(std::size_t nt);
    ThreadPool(ThreadPool&&);
    ~ThreadPool() noexcept;

    void emplace(Task new_task);
    void join_and_stop();
};
