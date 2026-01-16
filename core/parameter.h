#ifndef PARAMETER_H
#define PARAMETER_H


#include "structs.h"
namespace Core {

class Parameter
{

protected:
    Core::ParamConstraints m_constraints;
    float m_currentValue;
    std::atomic<float> m_targetValue;
    float m_coeff;
public:
    Parameter(Core::ParamConstraints info);
    void updateSampleRate(double sr);
    float getNextValue();
    void setTarget(float value);
};

} // namespace Audio

#endif // PARAMETER_H
