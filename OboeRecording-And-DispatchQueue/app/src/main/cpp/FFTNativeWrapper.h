//
// Created by remy on 26/4/20.
//

#include <vector>
#include "Utils.h"
#include "MyFFTAnalysis.h"

class FFTNativeWrapper {

public:
    static double fftEntryPoint(const std::array<float, __NUM_SAMPLES__> &);
    static std::shared_ptr<std::vector<double>> getNormalizedWindowDebug();
    static const std::shared_ptr<std::vector<double>> & getExtractedSignalDebug();
    static const std::shared_ptr<std::vector<double>> & getWindowedSignalDebug();
    static const std::shared_ptr<std::vector<double>> & getfftBufferDebug();
    static const std::shared_ptr<std::vector<double>> & getSpectrumDebug();

    static const std::shared_ptr<std::vector<double>> &getHPSResultDebug();

private:
    //by default smart pointer are set to nullptr when not initialized.
    static std::shared_ptr<std::vector<double>> w;
    static std::shared_ptr<std::vector<double>> x1;
    static std::shared_ptr<std::vector<double>> fftBuffer;
    static std::shared_ptr<std::vector<double>> windowedSignal;
    static std::shared_ptr<std::vector<double>> spectrum;
    static std::shared_ptr<std::vector<double>> hpsRes;
    static bool prepareSignal(const std::array<float, __NUM_SAMPLES__> &);
};