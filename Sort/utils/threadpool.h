#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <stdexcept>
#include <utility>
#include <vector>
#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <memory>

class ThreadPool {
private:
    using Task = std::function<void()>;

    std::vector<std::thread> m_pool;
    std::queue<Task> m_tasks;
    std::mutex m_mtx;
    std::condition_variable m_cv;
    bool m_stop;
    size_t m_threadNum;

public:
    ThreadPool(size_t threadNum): m_threadNum(threadNum), m_stop(false) {
        for(size_t i = 0; i < threadNum; i++) {
            m_pool.emplace_back([this]() {
                for(;;) {
                    Task task;
                    {
                        std::unique_lock<std::mutex> lk(m_mtx);
                        m_cv.wait(lk, [this]() { return m_stop || !m_tasks.empty(); });
                        if(m_stop && m_tasks.empty()) {
                            return;
                        }
                        task = std::move(m_tasks.front());
                        m_tasks.pop();
                    }
                    task();
                }
            }
            );
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lk(m_mtx);
            m_stop = true;
        }
        m_cv.notify_all();
        for(auto& thd:m_pool) {
            if(thd.joinable())
                thd.join();
        }
    }

    template<typename F>
    void submit(F&& f) {
        Task task = std::forward<F>(f);
        {
            std::unique_lock<std::mutex> lk(m_mtx);
            m_tasks.emplace(std::move(task));
        }
        m_cv.notify_one();
    }

    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args)->std::future<decltype(f(args...))> {
        using ReturnType = decltype(f(args...));
        auto taskPtr = std::shared_ptr<std::packaged_task<ReturnType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        std::future<ReturnType> future = taskPtr->get_future();
        {
            std::unique_lock<std::mutex> lk(m_mtx);
            if(m_stop) throw std::runtime_error("Submit task after threadpool stopping");
            m_tasks.emplace([taskPtr]() { (*taskPtr)();});
        }
        m_cv.notify_one();
        return future;
    }
};

#endif
