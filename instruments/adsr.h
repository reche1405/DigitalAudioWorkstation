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
    Core::Parameter m_attack;
    Core::Parameter m_decay;
    Core::Parameter m_sustain;
    Core::Parameter m_release;
};

} // namespace Instruments

#endif // ADSR_H
