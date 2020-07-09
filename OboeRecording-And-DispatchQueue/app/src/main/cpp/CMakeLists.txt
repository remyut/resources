cmake_minimum_required(VERSION 3.4.1)
project(nativeRecording LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)


get_filename_component(ROOT_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/.. ABSOLUTE)

# Build our own native library
add_library (nativeRecording
        SHARED
        jni-bridge.cpp
        AudioRecordEngine.cpp
        RecordingCallbackImp.cpp
        debug-utils/trace.cpp
        Utils.cpp
        MyFFTAnalysis.cpp
        FFTNativeWrapper.cpp
        DispatchQueue.cpp
        Worker.cpp)

target_include_directories(nativeRecording
        PRIVATE
        ${OBOE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/debug-utils)

# Specify the libraries which our native library is dependent on, including Oboe
target_link_libraries (nativeRecording
        PRIVATE
        oboe
        log
        android
        atomic)

# Build the Oboe library
set (OBOE_DIR /home/remy/oboe-c-lib/oboe)
add_subdirectory (${OBOE_DIR} ./oboe)

target_include_directories(nativeRecording
        PRIVATE
        debug-utils
        ${OBOE_DIR}/include)


# Make the Oboe public headers available to our app
include_directories (${OBOE_DIR}/include)

# Enable optimization flags: if having problems with source level debugging,
# disable -Ofast ( and debug ), re-enable it after done debugging.
#target_compile_options(liveEffect PRIVATE -Wall -Werror "$<$<CONFIG:RELEASE>:-Ofast>")