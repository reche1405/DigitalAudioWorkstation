#ifndef AUDIODOUBLEBUFFER_H
#define AUDIODOUBLEBUFFER_H

#include "doublebuffer.h"

namespace Core {

class AudioDoubleBuffer : public DoubleBuffer<float>
{
public:
    AudioDoubleBuffer(size_t size) : DoubleBuffer(size) {

    };
    template <typename Processor>
    void processBlock(Processor&& processor) {
        float* writeBuffer = getWriteBuffer();
        processor(writeBuffer, capacity());
        if(getAvailableReadSamples() == 0 && isNewDataAvailable()) {

            commitWrite();
        }
    }
};

} // namespace Core

#endif // AUDIODOUBLEBUFFER_H
