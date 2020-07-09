//
// Created by remy on 26/4/20.
//

#ifndef MACRO_H
#define MACRO_H

    static const bool __LOG_IN_FILE__ = true;
    static const unsigned int __RECORD_TIME__ = 1;
    static const unsigned int __SAMPLING_RATE__ = 44100;
    static constexpr unsigned int __NUM_SAMPLES__RESULT__ = __RECORD_TIME__ * __SAMPLING_RATE__;
    static const unsigned int __NUM_SAMPLES__ = __NUM_SAMPLES__RESULT__;
    static const unsigned int __WINDOW_SIZE__ = 4096;
    static const unsigned int __FFT_SIZE__ = __WINDOW_SIZE__;



#endif //MACRO_H