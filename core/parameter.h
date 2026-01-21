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
    Parameter(Core::ParamConstraints info, std::string label = "Unamed");
    void updateSampleRate(double sr);
    float getNextValue();
    void setTarget(float value);
    std::string title() const {return m_title;}
    Core::ID& id() const {return m_id; }
};

class Gain : public Parameter {
public:
    Gain() :
        Parameter(Core::ParamConstraints{Core::ParameterType::Continuous, 0.0f, 1.0f, 20.0f, 0}, "Gain") {
        m_currentValue = 0.9f;
    }
};

class Pan : public Parameter {
public:
    Pan() :
        Parameter(Core::ParamConstraints{Core::ParameterType::Continuous, -1.0f, 1.0f, 40.0f, 0}, "Pan") {
        m_currentValue = 0.0f;
    }
};

class Attack : public Parameter {
public:
    Attack() :
        Parameter(Core::ParamConstraints{Core::ParameterType::Continuous, 0.0f, 20000.0f, 20.0f, 0}, "Attack") {
        m_currentValue = 0.0f;
    }
};

class Decay : public Parameter {
public:
    Decay() :
        Parameter(Core::ParamConstraints{Core::ParameterType::Continuous, 0.0f, 20000.0f, 20.0f, 0}, "Decay") {
        m_currentValue = 6000.0f;
    }
};

class Sustain : public Parameter {
public:
    Sustain() :
        Parameter(Core::ParamConstraints{Core::ParameterType::Continuous, 0.0f, 1.0f, 20.0f, 0}, "Sustain") {
        m_currentValue = 6000.0f;
    }
};


class Release : public Parameter {
public:
    Release() :
        Parameter(Core::ParamConstraints{Core::ParameterType::Continuous, 0.0f, 20000.0f, 20.0f, 0}, "Release") {
        m_currentValue = 6000.0f;
    }
};

} // namespace Audio

#endif // PARAMETER_H
