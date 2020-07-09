//
// Created by remy on 26/4/20.
//

#include <sstream>
#include "Utils.h"


std::shared_ptr<std::vector<double>> Utils::generateNormalizedHammingWindow() {
    //generate the raw window
    double alpha = 0.54, beta = 0.46, windSum = 0;
    auto window = std::make_shared<std::vector<double>>();
    //auto normalizedWindow = std::make_shared<std::vector<double>>();

    for (unsigned int n = 0; n < __WINDOW_SIZE__; n++) {
        window.get()->push_back((alpha - beta * cos((2 * M_PI * n) / (__WINDOW_SIZE__ - 1))));
    }
    //normalise the analysis window
    //for (unsigned int i = 0; i < __WINDOW_SIZE__; i++)
      //  windSum += window.get()->at(i);

    //for (unsigned int i = 0; i < __WINDOW_SIZE__; i++)
        //normalizedWindow.get()->push_back(window.get()->at(i) / windSum);

    return window;
}

std::shared_ptr<std::vector<double>> Utils::extractSample(const std::array<float, __NUM_SAMPLES__> & x) {

    unsigned int start = x.size() / 2; // Take from the middle of the signal //todo make sure that start->stop contain __WINDOW_SIZE__
    unsigned int stop = start + __WINDOW_SIZE__; //Take from the middle to the window size = the signal sample.
    //todo maybe it is better to take from the begging start at 0 -> window size

    auto x1 = std::make_shared<std::vector<double>>();

    for(unsigned int n = start; n <= stop; n++) {
        x1.get()->push_back(x[n]);
    }

    return x1;
}

bool Utils::isPower2(int n) {
    return (n !=0) && (((n) & (n - 1)) == 0);
}

std::shared_ptr<std::vector<double>>
Utils::windowedTheSignal(const std::shared_ptr<std::vector<double>> & normWindow,
                         const std::shared_ptr<std::vector<double>> & extract) {

    auto windowedSignal = std::make_shared<std::vector<double>>();

    for (unsigned int i = 0; i < __WINDOW_SIZE__; i++) {
        windowedSignal.get()->push_back(extract.get()->at(i) * normWindow.get()->at(i));
    }

    return windowedSignal;
}

const char *Utils::writeInString(const std::shared_ptr<std::vector<double>> & data) {
        std::ostringstream ss;

        LOGD("Dumping...");
        ss << "#X";
        ss << "          ";
        ss << "Y";
        ss << "\n";

        if(__LOG_IN_FILE__) {
            for (unsigned int i = 0; i < data.get()->size(); ++i) {
                ss << i;
                ss << "          ";
                ss << data.get()->at(i);
                ss << "\n";
            }
        }
        std::string s(ss.str());
        LOGD("%s", s.c_str());
        LOGD("Dumping... Done OK");
        return s.c_str();
}

const char *Utils::writeInString(const std::array<float, __NUM_SAMPLES__> & data) {
        std::ostringstream ss;

        LOGD("Dumping...");
        ss << "#X";
        ss << "          ";
        ss << "Y";
        ss << "\n";
        if(__LOG_IN_FILE__) {
            for (unsigned int i = 0; i < data.size(); ++i) {
                ss << i;
                ss << "          ";
                ss << data[i];
                ss << "\n";
            }
        }
        std::string s(ss.str());
        LOGD("%s", s.c_str());
        LOGD("Dumping... Done OK");
        return s.c_str();
}



