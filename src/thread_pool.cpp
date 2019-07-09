#include "thread_pool.hpp"

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
    join_and_stop();
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