#ifndef STRUCTS_H
#define STRUCTS_H

#include <cstdint>
#include <QString>
namespace CoreUtils {
enum AssetType {Audio, MIDI};


struct Asset {
    virtual ~Asset() = default;
    std::string assetID;
    QString fileName;
    QString path;
    bool online = true;
    double durationSeconds;

    virtual AssetType type()const = 0;

};

struct Clip {
    virtual ~Clip() = default;
    int64_t globalStartTick;
    int64_t localStartTick;
    int64_t localEndTick;

    bool operator<(Clip other) {
        return globalStartTick < other.globalStartTick;
    }
    int64_t globalEndTick() const {
        return globalStartTick + localEndTick;
    }
    int64_t getTotalTicks() const {
        return  localEndTick - localStartTick;
    }

};



enum class ParameterType { Continuous, Stepped, Toggle };
enum class ParamMapping { Linear, Logarithmic };
struct ParamConstraints {
    ParameterType type;
    float min = 0.0f;
    float max = 1.0f;
    float rampTimeMs = 20.0f;
    unsigned int steps = 0;

    ParamMapping mapping;
};


} // namespace CoreUtils

#endif // STRUCTS_H
