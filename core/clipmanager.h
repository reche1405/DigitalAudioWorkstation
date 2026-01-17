#ifndef CLIPMANAGER_H
#define CLIPMANAGER_H

#include "structs.h"
namespace Core {

class ClipManager
{
public:
    ClipManager();
    virtual ~ClipManager() = default;
    virtual void prepare(uint32_t sampleRate) = 0;
private:

};

} // namespace Core

#endif // CLIPMANAGER_H
