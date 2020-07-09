//
// Created by remy on 26/4/20.
//
#include "AudioRecordEngine.h"
#include "../../../../../../oboe-c-lib/oboe/src/common/OboeDebug.h"
#include <oboe/Oboe.h>
#include "Worker.h"

using namespace oboe;

void AudioRecordEngine::startEngine() {

    //initDispatchQueue();

    AudioStreamBuilder streamBuilder;
    streamBuilder.setCallback(this);
    streamBuilder.setDirection(Direction::Input);
    streamBuilder.setPerformanceMode(PerformanceMode::LowLatency);
    streamBuilder.setSampleRate(44100);
    streamBuilder.setChannelCount(1);
    streamBuilder.setFormat(AudioFormat::Float);
    //streamBuilder.setDeviceId(deviceId); //todo external mic - Usb
    streamBuilder.setSharingMode(SharingMode::Exclusive);
    Result r = streamBuilder.openStream(&mRecordingStream);

    if(r != Result::OK){
        LOGE("Error opening stream %s", convertToText(r));
    }

    r = mRecordingStream->requestStart();

    if(r != Result::OK){
        LOGE("Error starting stream %s", convertToText(r));
        mRecordingStream->close();
    }
}

void AudioRecordEngine::stopEngine() {
    LOGD("Closing stream");
    oboe::Result inputResult;
    inputResult = mRecordingStream->requestStop();

    if (inputResult != oboe::Result::OK) {
        LOGE("cannot close the recording stream");
    }
    mRecordingStream->close();
}

void AudioRecordEngine::setRecording(bool recordingState) {
    if(recordingState) {
        mRecordingCallbackImp.clear();
        queue = new DispatchQueue("Queue restarted", 1);
        initDispatchQueue();
    } else{
        queue->~DispatchQueue();
        delete(queue);
        queue = nullptr;
    }
     mIsRecording = recordingState;
}
/**
* Handles playback stream's audio request. In this sample, we simply block-read
* from the record stream for the required samples.
*
* @param oboeStream: the playback stream that requesting additional samples
* @param audioData:  the buffer to load audio samples for playback stream
* @param numFrames:  number of frames to load to audioData buffer
* @return: DataCallbackResult::Continue.
*/


oboe::DataCallbackResult
AudioRecordEngine::onAudioReady(oboe::AudioStream *oboeStream, void *audioData, int32_t numFrames) {
    while (mIsRecording) {
        //LOGD("Yeah, forwarding the data to the callback implementation");
        int32_t framesWritten = mRecordingCallbackImp.write(static_cast<float *>(audioData),
                                                            numFrames);
        LOGD("read %d frame", framesWritten);
        mTotalFrameRead += framesWritten;
        if (framesWritten == 0) {
            //mIsRecording = false;
            //stopEngine();
            LOGD("1 sec recorded done");
        }
        else{
            LOGD("not recording, ignoring  the data...");
        }

        //LOGD("TOTAL FRAME READ %d", mTotalFrameRead);
        if (mTotalFrameRead == kMaxSamples) {

            LOGD("Post in queue");
            //call the fft entry point
            //FFTNativeWrapper::fftEntryPoint(mRecordingCallbackImp.getAudioData());
            //todo have to return the value !
            queue->dispatch(std::bind(&AudioRecordEngine::run, this));
        }
        //mRecordingCallbackImp.writeInLog();

        return DataCallbackResult::Continue;
    }
    LOGD("end done");
    return DataCallbackResult::Continue;
}

const char * AudioRecordEngine::getRecordedData() {
    return mRecordingCallbackImp.getRecordedData();
}

const char *AudioRecordEngine::getNormalizedWindow() {
    return Utils::writeInString(FFTNativeWrapper::getNormalizedWindowDebug());
}

const char *AudioRecordEngine::getExtractedSignal() {
    return Utils::writeInString(FFTNativeWrapper::getExtractedSignalDebug());
}

const char *AudioRecordEngine::getSpectrum() {
     return Utils::writeInString(FFTNativeWrapper::getSpectrumDebug()) == nullptr ? "" :
     Utils::writeInString(FFTNativeWrapper::getSpectrumDebug());

}

const char *AudioRecordEngine::getWindowedSignal() {
    return Utils::writeInString(FFTNativeWrapper::getWindowedSignalDebug());
}

const char *AudioRecordEngine::getFFTbuffer() {
    return Utils::writeInString(FFTNativeWrapper::getfftBufferDebug());
}

const char *AudioRecordEngine::getHPSRes() {
    return Utils::writeInString(FFTNativeWrapper::getHPSResultDebug());
}

void AudioRecordEngine::initDispatchQueue() {
    queue = new DispatchQueue("MyQueue", 1);

}

AudioRecordEngine::~AudioRecordEngine() {
    LOGD("Audio Record Engine Destructor \n");

    //delete(queue);
    //todo delete worker maybe?
}

std::string AudioRecordEngine::run(void) {
    std::thread::id this_id = std::this_thread::get_id();
    LOGD("In the thread ID %zu  \n", this_id);
    return "from thread";
}


