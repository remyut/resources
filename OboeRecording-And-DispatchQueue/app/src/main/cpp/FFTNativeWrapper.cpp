//
// Created by remy on 26/4/20.
//

#include "FFTNativeWrapper.h"
#include "MyFFTAnalysis.h"
#include "Utils.h"
#include "macros.h"

std::shared_ptr<std::vector<double>>  FFTNativeWrapper::w = nullptr;
std::shared_ptr<std::vector<double>>  FFTNativeWrapper::x1 = nullptr;
std::shared_ptr<std::vector<double>>  FFTNativeWrapper::windowedSignal = nullptr;
std::shared_ptr<std::vector<double>>  FFTNativeWrapper::fftBuffer = nullptr;
std::shared_ptr<std::vector<double>>  FFTNativeWrapper::spectrum = nullptr;
std::shared_ptr<std::vector<double>>  FFTNativeWrapper::hpsRes = nullptr;

double FFTNativeWrapper::fftEntryPoint(const std::array<float, __NUM_SAMPLES__> & inputData) {
        if(prepareSignal(inputData)){ // the fft buffer exists
        auto f =  std::make_unique<MyFFTAnalysis>(MyFFTAnalysis(fftBuffer));
        f.get()->fft();

        auto mX = f.get()->getmX();

        if(__LOG_IN_FILE__)
            spectrum = mX;

        if(f.get()->checkValidity(mX)) {
            hpsRes = f.get()->hpsAlgo(mX); //Hps not used
            double freq = f.get()->f0Detection(mX); //todo something's fishy here...
            LOGD("Note detected %d", freq);
            return freq;
        }
        else {
            LOGD("Spectrum not valid");
            return -1;
        }
    }
    return -1;
}


bool FFTNativeWrapper::prepareSignal(const std::array<float, __NUM_SAMPLES__> & inputData) {
    //pre-processing
    if (!Utils::isPower2(__FFT_SIZE__))
        LOGD("FFT__ size (N) is not a power of 2");

   // if (__WINDOW_SIZE__ > __FFT_SIZE__)
     //   LOGD("Window size (M) is bigger than FFT__ size");

    if(w == nullptr)
        w = Utils::generateNormalizedHammingWindow(); //The window generation

    x1 = Utils::extractSample(inputData);
    //valuable information
    if(x1 != nullptr)
    {
        //apply the normalized window in the extracted signal
        windowedSignal = Utils::windowedTheSignal(w, x1);

        if(windowedSignal != nullptr){
            //create the FFT Buffer with zero phase
            unsigned int hN2 = __WINDOW_SIZE__ / 2;

            fftBuffer = std::make_shared<std::vector<double>>();

            for(unsigned int i = hN2; i < __WINDOW_SIZE__; i++)
                fftBuffer.get()->push_back(windowedSignal.get()->at(i));

            for(unsigned int i = 0; i < hN2; i++)
                fftBuffer.get()->push_back(windowedSignal.get()->at(i));

        }
    }
    return fftBuffer != nullptr;
}

std::shared_ptr<std::vector<double>> FFTNativeWrapper::getNormalizedWindowDebug() {
    return w;
}

const std::shared_ptr<std::vector<double>> & FFTNativeWrapper::getExtractedSignalDebug() {
    return x1;
}

const std::shared_ptr<std::vector<double>> & FFTNativeWrapper::getWindowedSignalDebug() {
    return windowedSignal;
}

const std::shared_ptr<std::vector<double>> & FFTNativeWrapper::getfftBufferDebug() {
    return fftBuffer;
}

const std::shared_ptr<std::vector<double>> &FFTNativeWrapper::getSpectrumDebug() {
    return spectrum;
}

const std::shared_ptr<std::vector<double>> &FFTNativeWrapper::getHPSResultDebug() {
    return hpsRes;
}
