#ifndef ADSR_H
#define ADSR_H
#include "../core/parameter.h"
namespace Instruments {
class ADSR
{
public:
    ADSR();
    float attack() {return m_attack.getNextValue();}
    float decay() {return m_decay.getNextValue();}
    float sustain() {return m_sustain.getNextValue();}
    float release() {return m_release.getNextValue(); }


private:
    Core::Attack m_attack;
    Core::Decay m_decay;
    Core::Sustain m_sustain;
    Core::Release m_release;

};

} // namespace Instruments

#endif // ADSR_H
