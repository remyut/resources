//
// Created by remy on 26/4/20.
//

#ifndef RECORDING_CALLBACK_IMP_H
#define RECORDING_CALLBACK_IMP_H

#include <array>
#include <atomic>
#include <cstdint>
#include <string>
#include "../../../../../../oboe-c-lib/oboe/include/oboe/AudioStream.h"
#include "macros.h"
#include <logging_macros.h>

constexpr unsigned int kMaxSamples = __NUM_SAMPLES__; //see macro

class RecordingCallbackImp {

public:
    int32_t write(float *audioData, int32_t numFrames);
    std::array<float, kMaxSamples> getAudioData();
    const char * getRecordedData();
    void clear();

private:
    std::atomic<int32_t> mWriteIndex { 0 };
    std::array<float, kMaxSamples> mData { 0 };
};

#endif //RECORDING_CALLBACK_IMP_H