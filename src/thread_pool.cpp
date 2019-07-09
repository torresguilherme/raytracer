#include "thread_pool.hpp"

template <typename Task>
ThreadPool<Task>::ThreadPool(std::size_t nt): num_threads(nt)
{
    for(uint i = 0; i < num_threads; i++)
    {
        threads.emplace_back([=] {
            while(true)
            {
                if(tasks.empty() && stop)
                {
                    break;
                }
                
                if(!tasks.empty)
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

template <typename Task>
ThreadPool<Task>::~ThreadPool() noexcept
{
    join_and_stop();
}

template <typename Task>
void ThreadPool<Task>::emplace(Task new_task)
{
    tasks.emplace(std::move(new_task));
}

template <typename Task>
void ThreadPool<Task>::join_and_stop()
{
    stop.notify_all();
    for(uint i = 0; i < num_threads; i++)
    {
        threads[i].join();
    }
}