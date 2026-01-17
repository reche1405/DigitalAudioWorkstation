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
    std::string m_title;
    Core::ID& m_id;
public:
    Parameter(Core::ParamConstraints info);
    void updateSampleRate(double sr);
    float getNextValue();
    void setTarget(float value);
    std::string title() const {return m_title;}
    Core::ID& id() const {return m_id; }
};

} // namespace Audio

#endif // PARAMETER_H
