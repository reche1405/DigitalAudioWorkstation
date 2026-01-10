#include "playhead.h"

namespace Graphics {



void Playhead::updateHeight(int newHeight) {
    prepareGeometryChange();
    m_height = newHeight;
}

} // namespace Graphics
