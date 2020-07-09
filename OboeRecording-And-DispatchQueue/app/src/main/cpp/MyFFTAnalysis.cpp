//
// Created by remy on 26/4/20.
//

#include <logging_macros.h>
#include "MyFFTAnalysis.h"
#include "macros.h"

MyFFTAnalysis::MyFFTAnalysis(const std::shared_ptr<std::vector<double>> & fftBuffer) {
    auto complexFFTBuffer = std::make_unique<Complex[]>(__FFT_SIZE__);


    for (unsigned int i = 0; i < __FFT_SIZE__; i++) {
        complexFFTBuffer[i] = Complex(fftBuffer.get()->at(i), 0);
    }
    CArray x(complexFFTBuffer.get(), static_cast<size_t>(__FFT_SIZE__)); //todo maybe memory leak here...
    this->x = x;
}

std::shared_ptr<std::vector<double>> MyFFTAnalysis::getmX() {

    auto mX = std::make_shared<std::vector<double>>();

    for (int i = 0; i< __FFT_SIZE__/2; i++)
    {
        mX.get()->push_back(20 *log10(std::abs(x[i]))); //gives DBFS value. 0 is the highest
    }

    return mX;
}

void MyFFTAnalysis::fft() {
    fft(this->x);
}

// Cooley-Tukey FFT (in-place, breadth-first, decimation-in-frequency)
// Better optimized but less intuitive
// !!! Warning : in some cases this code make result different from not optimised version above (need to fix bug)
// The bug is now fixed @2017/05/30
void MyFFTAnalysis::fft(CArray &x)
{
    // DFT
    unsigned int N = x.size(), k = N, n;
    double thetaT = 3.14159265358979323846264338328L / N;
    Complex phiT = Complex(cos(thetaT), -sin(thetaT)), T;
    while (k > 1)
    {
        n = k;
        k >>= 1;
        phiT = phiT * phiT;
        T = 1.0L;
        for (unsigned int l = 0; l < k; l++)
        {
            for (unsigned int a = l; a < N; a += n)
            {
                unsigned int b = a + k;
                Complex t = x[a] - x[b];
                x[a] += x[b];
                x[b] = t * T;
            }
            T *= phiT;
        }
    }
    // Decimate
    unsigned int m = (unsigned int)log2(N);
    for (unsigned int a = 0; a < N; a++)
    {
        unsigned int b = a;
        // Reverse bits
        b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
        b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
        b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
        b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
        b = ((b >> 16) | (b << 16)) >> (32 - m);
        if (b > a)
        {
            Complex t = x[a];
            x[a] = x[b];
            x[b] = t;
        }
    }
    //// Normalize (This section make it not working correctly)
    //Complex f = 1.0 / sqrt(N);
    //for (unsigned int i = 0; i < N; i++)
    //	x[i] *= f;
}


std::shared_ptr<std::vector<double>> MyFFTAnalysis::hpsAlgo(const std::shared_ptr<std::vector<double>> & mX){

    //get the smallest vector size
    double smallestVectorSize = getSmallestVectorSize(mX->size(), 4);

    //y contains the original spectrum, the first step for the downsampling
    auto y = getSmallestVector(mX, smallestVectorSize);

    //todo need a third down sampling res vector?
    std::vector<double> res1;
    std::vector<double> res2;
    auto downsamplingRes = std::make_shared<std::vector<double>>();


    //downsampling
    for(unsigned int i = 2; i < 4; i++)
    {
        if (i == 2)
        {
            for (unsigned int j = 0, k = 0; j<smallestVectorSize; j+=2, k++)
                res1.push_back(y.at(j)); // une valeur sur deux
        }
        else if (i == 3)
        {
            for (unsigned int j = 0, k = 0; j<smallestVectorSize; j+=3, k++)
                res2.push_back(y.at(j)); // une valeur sur trois
        }
    }

    //make sure res1 and res 2 are size of the smallest Vector
    int res1SizeLeft = (int)smallestVectorSize - (int)res1.size();
    int res2SizeLeft = (int)smallestVectorSize - (int)res2.size();

    for(int i = 0; i < res1SizeLeft; i++){
        res1.push_back(1.0);
    }

    for(int i = 0; i < res2SizeLeft; i++){
        res2.push_back(1.0);
    }

    //multiplication
    for(unsigned int i = 0; i < smallestVectorSize; i++)
        downsamplingRes.get()->push_back(y.at(i) * res1.at(i) * res2.at(i));

    return downsamplingRes;


}

double MyFFTAnalysis::getSmallestVectorSize(int mXLenght, int factor) {
    return std::ceil((double)mXLenght / factor);

}

std::vector<double> MyFFTAnalysis::getSmallestVector(const std::shared_ptr<std::vector<double>> & mX, double length) {
    std::vector<double> myVect;

    for(unsigned int i = 0; i < length; i++){
        myVect.push_back(mX->at(i));
    }

    return myVect;
}

double MyFFTAnalysis::f0Detection(const std::shared_ptr<std::vector<double>> & hpsRes) {
    // step 1 - calculate the frequency axis vector
    std::vector<double> freqAxis;
    std::vector<double> freqVector;
    double highestPeak = -1;
    int f0Index = -1;

    //get the normalise axis
    for(int i = 0; i < hpsRes->size(); i++)
    {
        freqAxis.push_back(i / (float)__FFT_SIZE__); //todo why divide by win size
    }

    //step 2 - find the frequencies corresponding to the spectrum
    for(unsigned int i = 0; i < hpsRes->size(); i++)
    {
        freqVector.push_back(freqAxis.at(i) * __SAMPLING_RATE__); // get the actual frequencies from the normalised axis
    }

    auto result = std::max_element(hpsRes->begin(), hpsRes->end());

    //step 3 - get the value of the f0 - get the index of the highest peak value - take max value
    // Hopeful the highest peak is within the 50 first values !!
    for(unsigned int i = 0; i < hpsRes->size(); i++) /* todo remove hardcoded value, I dunno why I have positive values in here 50 is more then enought, check if other audio file has positive values... it is due to accumulate error of accuracy (calcul) */
    {
        if (hpsRes->at(i) == *result) {
            f0Index = i;
            break;
        }
    }
    if(f0Index != -1)
    {
        LOGD("F0index %d", f0Index);
        //Log.v("FLOW_TAG", "Estimated Freq:" + freqVector[f0Index]);
        //Log.v("FLOW_TAG", "Estimated dB:" + );
        //step 4 - find the corresponding frequency of the max value (The highest peak) with its index with a ceiling
        //return Math.ceil(freqVector[f0Index]); //todo do not round the estimated frequency
        return freqVector.at(static_cast<unsigned int>(f0Index)); //return the estimated frequency
        //f0Index - 1 because it cannot be 0Hz donc ceste erroner de 1

    }
    else
        return -1;





}

//Check if the spectrogram has some value above the noise threshold -6dBfs
bool MyFFTAnalysis::checkValidity(const std::shared_ptr<std::vector<double>> & mX){

    for(unsigned int i = 0; i < mX->size(); i++) { //Valid if above 0dB
        if(mX->at(i) > 0)
            return true;
    }
    return false;
}

MyFFTAnalysis::MyFFTAnalysis() {
    this->x = NULL;
}

MyFFTAnalysis::~MyFFTAnalysis() {
    //dynamically array allocated handled by smart pointers
    //No need to invoke delete
    x.resize(0);
}