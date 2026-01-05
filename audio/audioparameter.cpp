#include "audioparameter.h"

namespace Audio {

AudioParameter::AudioParameter(ParamConstraints info) :
    m_constraints(info),
    m_currentValue(info.min),
    m_targetValue(info.min)

{

}

void AudioParameter::updateSampleRate(double sr) {
    if(m_constraints.rampTimeMs <= 0.0f) {
        m_coeff = 1.0f;
        return;
    }
    float rampSamples = (m_constraints.rampTimeMs * 0.001) * sr;
    m_coeff = 1.0 - std::exp(-1.0 / rampSamples);
}

float AudioParameter::getNextValue() {
    float target = m_targetValue.load();
    if(m_constraints.type == ParameterType::Continuous) {
        m_currentValue += (target - m_currentValue) * m_coeff;
    } else {
        m_currentValue = target;
    }
    return m_currentValue;
}

void AudioParameter::setTarget(float newTarget) {
    m_targetValue.store(newTarget);
}
} // namespace Audio

