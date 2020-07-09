//
// Created by remy on 26/4/20.
//
#include <jni.h>
#include "AudioRecordEngine.h"
#include <logging_macros.h>

static AudioRecordEngine engine;

extern "C"
JNIEXPORT void JNICALL
Java_test_r_oboerecording_RecordingEngine_startEngine(JNIEnv *env, jclass clazz) {
    engine.startEngine();
}

extern "C"
JNIEXPORT void JNICALL
Java_test_r_oboerecording_RecordingEngine_stopEngine(JNIEnv *env, jclass clazz) {
    engine.stopEngine();
}

extern "C"
JNIEXPORT void JNICALL
Java_test_r_oboerecording_RecordingEngine_setRecording(JNIEnv *env, jclass clazz,
        jboolean state) {
    engine.setRecording(state);
}
extern "C"
JNIEXPORT jstring JNICALL
Java_test_r_oboerecording_RecordingEngine_getRecordedData(JNIEnv *env, jclass clazz) {
    const char* s = engine.getRecordedData();
    return env -> NewStringUTF(s);

}

extern "C"
JNIEXPORT jstring JNICALL
Java_test_r_oboerecording_RecordingEngine_getNormalizedWindow(JNIEnv *env, jclass clazz) {
    const char* s = engine.getNormalizedWindow();
    return env -> NewStringUTF(s);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_test_r_oboerecording_RecordingEngine_getExtract(JNIEnv *env, jclass clazz) {
    const char* s = engine.getExtractedSignal();
    return env -> NewStringUTF(s);
}


extern "C"
JNIEXPORT jstring JNICALL
Java_test_r_oboerecording_RecordingEngine_getSpectrum(JNIEnv *env, jclass clazz) {
    const char* s = engine.getSpectrum();
    return env -> NewStringUTF(s);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_test_r_oboerecording_RecordingEngine_getWindowedSignal(JNIEnv *env, jclass clazz) {
    const char* s = engine.getWindowedSignal();
    return env -> NewStringUTF(s);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_test_r_oboerecording_RecordingEngine_getFFTbuffer(JNIEnv *env, jclass clazz) {
    const char* s = engine.getFFTbuffer();
    return env -> NewStringUTF(s);
}
extern "C"
JNIEXPORT jstring JNICALL
Java_test_r_oboerecording_RecordingEngine_getHPSResult(JNIEnv *env, jclass clazz) {
    const char* s = engine.getHPSRes();
    return env -> NewStringUTF(s);
}