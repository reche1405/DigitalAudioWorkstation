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

class Gain : public Parameter {

    Gain() :
        Parameter(Core::ParamConstraints{Core::ParameterType::Continuous, 0.0f, 1.0f, 20.0f, 0}) {}
};
class Pan : public Parameter {
    Pan() :
        Parameter(Core::ParamConstraints{Core::ParameterType::Continuous, -1.0f, 1.0f, 40.0f, 0}) {}
};

} // namespace Audio

#endif // PARAMETER_H
