#include "audiothreadpool.h"
#include <qdebug.h>

namespace Core {

AudioThreadPool::AudioThreadPool(size_t threads) {
    qDebug() << "Total threads" << (threads);
    for(size_t i =0; i < threads; ++i) {
        // Generate a worker for every thread.
        workers.emplace_back([this] {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock lock(queueMutex);
                    conditional.wait(lock, [this] {
                        return stop || !tasks.empty();
                    });
                    if (stop && tasks.empty()) return;
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                task(); // Execute the task that has been popped from the queue.
            }
        });

    }
}

void AudioThreadPool::enqueue(std::function<void ()> task)
{
    {
    std::lock_guard lock(queueMutex);
    tasks.push(std::move(task));
    }
    conditional.notify_one();
}

} // namespace Core
