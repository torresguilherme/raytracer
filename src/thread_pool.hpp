#pragma once

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

template <class Task>
ThreadPool<Task>::ThreadPool(std::size_t nt): num_threads(nt)
{
    stop = false;
    for(uint i = 0; i < num_threads; i++)
    {
        threads.emplace_back([=] {
            while(true)
            {
                if(tasks.empty() && stop)
                {
                    break;
                }
                
                if(!tasks.empty())
                {
                    std::unique_lock<std::mutex> unilock(lock);
                    Task task = tasks.front();
                    tasks.pop();
                    unilock.unlock();
                    task();
                }
            }
        });
    }
}

// copy constructor
template <class Task>
ThreadPool<Task>::ThreadPool(ThreadPool&& other)
{
    num_threads = other.num_threads;
    threads = other.threads;
    stop = other.stop;
    tasks = other.tasks;
}

template <class Task>
ThreadPool<Task>::~ThreadPool() noexcept
{
    threads.clear();
}

template <class Task>
void ThreadPool<Task>::emplace(Task new_task)
{
    tasks.emplace(std::move(new_task));
}

template <class Task>
void ThreadPool<Task>::join_and_stop()
{
    stop = true;
    for(uint i = 0; i < num_threads; i++)
    {
        threads[i].join();
    }
}