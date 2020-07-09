package test.r.oboerecording;

import android.content.Context;
import android.media.AudioManager;
import android.os.Build;

public enum RecordingEngine
{
    INSTANCE;

    // Load native library
    static {
        System.loadLibrary("nativeRecording");
    }

    // Native methods
    static native void startEngine();
    static native void stopEngine();
    static native void setRecording(boolean recordingState);
    static native String getRecordedData();
    static native String getNormalizedWindow();
    static native String getExtract();
    static native String getSpectrum();
    static native String getWindowedSignal();
    static native String getFFTbuffer();
    static native String getHPSResult();


}