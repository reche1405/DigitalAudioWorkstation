#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <vector>
#include <atomic>
#include <cstdint>

namespace CoreUtils {
template < typename T >
    class RingBuffer
    {
    private:
        std::atomic<size_t> m_head;
        std::atomic<size_t> m_tail;
        size_t m_capacity;
        size_t m_mask;
        std::vector<T> m_buffer;



    public:
        explicit RingBuffer(size_t capacity) {
            m_capacity = capacity;
            m_mask = capacity - 1;
            m_buffer.resize(m_capacity);
            m_head.store(0);
            m_tail.store(0);
        };
        bool push(T& data) {
            size_t head = m_head.load(std::memory_order_relaxed);
            size_t nextHead = (head + 1) & m_mask;

            // If the buffer is full
            if(nextHead == m_tail.load(std::memory_order_acquire)) {
                return false;
            }
            m_buffer[head] = data;
            m_head.store(nextHead,std::memory_order_release);
            return true;

        };
        bool pop(T& data) {
            size_t tail = m_tail.load(std::memory_order_relaxed);
            if(tail == m_head.load(std::memory_order_acquire)) {
                return false;
            }
            data = m_buffer[tail];
            m_tail.store((tail + 1) & m_mask, std::memory_order_release);
            return true;
        }

        size_t availableSamples() const {
            size_t head = m_head.load(std::memory_order_acquire);
            size_t tail = m_tail.load(std::memory_order_acquire);
            return (head - tail) & m_mask;
        }
    };
}

#endif // RINGBUFFER_H
