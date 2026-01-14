#ifndef AUDIOPARAMETER_H
#define AUDIOPARAMETER_H


#include "audiostructs.h"
namespace Audio {

class AudioParameter
{

protected:
    Core::ParamConstraints m_constraints;
    float m_currentValue;
    std::atomic<float> m_targetValue;
    float m_coeff;
public:
    AudioParameter(Core::ParamConstraints info);
    void updateSampleRate(double sr);
    float getNextValue();
    void setTarget(float value);
};

} // namespace Audio

#endif // AUDIOPARAMETER_H
