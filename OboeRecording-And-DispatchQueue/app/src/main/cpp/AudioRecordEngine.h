//
// Created by remy on 26/4/20.
//

#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H


#include <oboe/AudioStreamCallback.h>
#include <oboe/AudioStreamBuilder.h>
#include <jni.h>
#include "RecordingCallbackImp.h"
#include "FFTNativeWrapper.h"
#include "DispatchQueue.h"
#include "Worker.h"
#include <string>

class AudioRecordEngine : public oboe::AudioStreamCallback {

private:
    oboe::AudioStream *mRecordingStream;
    RecordingCallbackImp mRecordingCallbackImp;
    bool mIsRecording = false;
    int32_t mTotalFrameRead = 0;
    DispatchQueue* queue;
    //Worker worker;
    fp_t *myFunc;

public:
    ~AudioRecordEngine();
    void startEngine();
    void stopEngine();
    void setRecording(bool recordingState);
    oboe::DataCallbackResult
    onAudioReady(oboe::AudioStream *oboeStream, void *audioData, int32_t numFrames) override;

    std::string run(void);

    //Accessors
    const char * getRecordedData();
    const char *getNormalizedWindow();
    const char *getExtractedSignal();
    const char *getSpectrum();
    const char *getWindowedSignal();
    const char *getFFTbuffer();

    const char *getHPSRes();

    void initDispatchQueue();
};

#endif //AUDIO_ENGINE_H
