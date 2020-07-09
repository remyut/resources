//
// Created by remy on 26/4/20.
//
#include "RecordingCallbackImp.h"
#include "Utils.h"

void RecordingCallbackImp::clear(){ mWriteIndex = 0; }

int32_t
RecordingCallbackImp::write(float *sourceData, int32_t numSamples) {
    LOGD("Yeah, hit the callback implementation num sample %d", numSamples);
    if (mWriteIndex + numSamples > kMaxSamples) {
        numSamples = kMaxSamples - mWriteIndex;
    }

    for (int i = 0; i < numSamples; ++i) {
        mData[mWriteIndex++] = sourceData[i];
    }
    return numSamples;
}

const char* RecordingCallbackImp::getRecordedData() {
    return Utils::writeInString(mData);
}

std::array<float, kMaxSamples> RecordingCallbackImp::getAudioData() {
    return mData;
}
