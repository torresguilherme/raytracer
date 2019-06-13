#include <thread>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>

struct ThreadPool
{
    std::size_t num_threads;
    std::vector<std::thread> threads;

    ThreadPool(std::size_t nt): num_threads(nt) {};
    ~ThreadPool() noexcept;
};
