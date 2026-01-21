#include "parameter.h"

namespace Core {

Parameter::Parameter(Core::ParamConstraints info, std::string label) :
    m_constraints(info),
    m_currentValue(info.min),
    m_targetValue(info.min),
    m_id(Core::IdManager::instance().generateId())


{
m_title = label;
}

void Parameter::updateSampleRate(double sr) {
    if(m_constraints.rampTimeMs <= 0.0f) {
        m_coeff = 1.0f;
        return;
    }
    float rampSamples = (m_constraints.rampTimeMs * 0.001) * sr;
    m_coeff = 1.0 - std::exp(-1.0 / rampSamples);
}

float Parameter::getNextValue() {
    float target = m_targetValue.load();
    if(m_constraints.type == Core::ParameterType::Continuous) {
        m_currentValue += (target - m_currentValue) * m_coeff;
    } else {
        m_currentValue = target;
    }
    return m_currentValue;
}

void Parameter::setTarget(float newTarget) {
    m_targetValue.store(newTarget);
}
} // namespace Audio

