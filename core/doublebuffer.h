#ifndef DOUBLEBUFFER_H
#define DOUBLEBUFFER_H
#include <array>
#include <atomic>
#include <cstddef>

namespace Core {

template<typename T>
class DoubleBuffer {

public:
private:
    // Both the read and write buffers.
    std::array<T*, 2> buffers;
    // The index of the read buffer in the above structure.
    std::atomic<int> readIndex{0};
    // The position of the write index in the above structure.
    std::atomic<int> writeIndex{1};
    // The capacity of both buffers;

    size_t m_capacity;

    // The position within the buffer to read from within the audio callback.
    std::atomic<size_t> readPos{0};
    // The position within the buffer to write to in the engine thread.
    std::atomic<size_t> writePos{0};
};
}; // namespace Core
#endif // DOUBLEBUFFER_H
