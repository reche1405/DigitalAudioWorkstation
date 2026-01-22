#ifndef AUDIOTHREADPOOL_H
#define AUDIOTHREADPOOL_H

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
namespace Core {

class AudioThreadPool
{
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable conditional;
    bool stop = false;
public:
    AudioThreadPool(size_t threads = std::thread::hardware_concurrency() - 2);
    ~AudioThreadPool() {
        {
            std::lock_guard lock(queueMutex);
            stop = true;
        }
        conditional.notify_all();
        for(std::thread& worker : workers) {
            worker.join();
        }
    }
    void enqueue(std::function<void()> task);
};

} // namespace Core

#endif // AUDIOTHREADPOOL_H
