#ifndef DOUBLEBUFFER_H
#define DOUBLEBUFFER_H
#include <algorithm>
#include <array>
#include <atomic>
#include <cstddef>

namespace Core {

template<typename T>
class DoubleBuffer {
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


    // Tells the read buffer to start at position index 0 in
    // whichever buffer used to be the write buffer.
    void swapBuffer() noexcept {
        int readIdx = readIndex.load(std::memory_order_acquire);
        int newIdx = (readIdx + 1) % 2;
        readIndex.store(readIdx, std::memory_order_release);

        readPos.store(0, std::memory_order_release);
    }

    friend void swap(DoubleBuffer& a, DoubleBuffer& b) noexcept {
        using std::swap;
        swap(a.buffers, b.buffers);
        swap(a.readIndex, b.readIndex);
        swap(a.writeIndex, b.writeIndex);
        swap(a.readPos, b.readPos);
        swap(a.writePos, b.writePos);
        swap(a.m_capacity, b.m_capacity);
    }

public:
    DoubleBuffer(size_t size) : m_capacity(size) {};

    DoubleBuffer(const DoubleBuffer&) = delete;
    DoubleBuffer& operator=(const DoubleBuffer&) = delete;

    DoubleBuffer(DoubleBuffer&& other) {
        swap(*this, other);
    }
    // Write buffer logic for use in the audio engine thread.

    // Get a pointer the memory address of the write buffer to be filled.
    T* getWriteBuffer() noexcept {
        return buffers[writeIndex.load(std::memory_order_acquire)];

    }

    // get the write position for stream writes.
    size_t getWritePosition() const noexcept {
        return writePos.load(std::memory_order_relaxed);
    }

    // write a sample to the write buffer (for streamig mode.)
    void writeSample(T sample) noexcept {
        size_t posSnapshot = writePos.load(std::memory_order_relaxed);
        buffers[writeIndex.load(std::memory_order_acquire)][posSnapshot] = sample;
        writePos.store(posSnapshot + 1, std::memory_order_release);
    }

    // Write a block to the write buffer
    void writeBlock(const T* data, size_t count) noexcept {
        int idx = writeIndex.load(std::memory_order_acquire);
        size_t pos = writePos.load(std::memory_order_relaxed);
        std::copy_n(data, count, buffers[idx] + pos);
        writePos.store(pos + count, std::memory_order_release);
    }

    // Commits the written block and switches the write buffer index if necessary.
    void commitWrite() noexcept {
        writePos.store(0, std::memory_order_release);

        int writeIdx = writeIndex.load(std::memory_order_acquire);
        int readIdx = readPos.load(std::memory_order_acquire);
        if (writeIdx != readIdx) {
            int newWriteIdx = (writeIdx + 1) % 2;
            writeIndex.store(newWriteIdx, std::memory_order_release);
        }
    }

    size_t getAvialableWriteSamples() const noexcept {
        return m_capacity - writePos.load(std::memory_order_relaxed);
    }


    // Read buffer logic for use in the audio playback thread.


    // Returns a pointer to the address in memory for the read buffer.
    T* getReadBuffer() noexcept {
        return buffers[readIndex.load(std::memory_order_acquire)];
    }

    // Get the current index of the read buffer for sample based reading.
    size_t getReadPosition() const noexcept {
        return readPos.load(std::memory_order_relaxed);

    }
    // Returns the current sample for the read buffer, swaps buffer if the read position reaches capacity.
    T readSample() noexcept {
        size_t posSnapshot = readPos.load(std::memory_order_relaxed);
        T sample = buffers[readIndex.load(std::memory_order_acquire)];
        readPos.store(posSnapshot + 1, std::memory_order_release);

        //TODO:: Implement swap buffers helper function.

        if(readPos >= m_capacity) {

            swapBuffer();
        }
        return sample;
    }

    void readBlock(T* output, size_t count) noexcept {
        int idx = readIndex.load(std::memory_order_acquire);
        size_t pos = readPos.load(std::memory_order_relaxed);
        std::copy_n(buffers[idx] + pos, count, output);

        readPos.store(pos + count, std::memory_order_release);
        if(readPos >= m_capacity) {

            swapBuffer();
        }
    }

    bool isNewDataAvailable() const noexcept {
        return readIndex.load(std::memory_order_acquire) !=
               writeIndex.load(std::memory_order_acquire);
    }

    size_t getAvailableReadSamples() const noexcept {
        return m_capacity - readPos.load(std::memory_order_relaxed);
    }

    // Buffer mamanagement

    void clear() noexcept {
        for(int i=0; i < 2; i++) {
            std::fill_n(buffers[i], m_capacity, T(0));
        }
        readPos.store(0);
        writePos.store(0);

        readIndex.store(0);
        writeIndex.store(1);

    }

    size_t capacity() const noexcept {return m_capacity; }





};
}; // namespace Core
#endif // DOUBLEBUFFER_H
