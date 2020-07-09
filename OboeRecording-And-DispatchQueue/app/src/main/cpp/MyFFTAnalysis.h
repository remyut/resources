//
// Created by remy on 26/4/20.
//

#ifndef _MYFFTANALYSIS_H
#define _MYFFTANALYSIS_H
#include <complex>
#include <iostream>
#include <valarray>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <memory>

const double PI = 3.141592653589793238460;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

//todo Manage memory allocation and deallocation
class MyFFTAnalysis {

private:
    CArray x;

public:
    MyFFTAnalysis();
    ~MyFFTAnalysis(); //todo to implement
    MyFFTAnalysis(const std::shared_ptr<std::vector<double>>&);
    std::shared_ptr<std::vector<double>> getmX();
    std::shared_ptr<std::vector<double>> hpsAlgo(const std::shared_ptr<std::vector<double>> &);
    double getSmallestVectorSize(int, int);
    std::vector<double> getSmallestVector(const std::shared_ptr<std::vector<double>> &, double);
    double f0Detection(const std::shared_ptr<std::vector<double>> &);
    bool checkValidity(const std::shared_ptr<std::vector<double>> &);

    void fft();
    void fft(CArray &x);



};
#endif //_MYFFTANALYSIS_H
