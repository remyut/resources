//
// Created by remy on 30/6/20.
//
#include <thread>
#include <functional>
#include <vector>
#include <cstdio>
#include <queue>
#include <mutex>
#include <string>
#include <condition_variable>

typedef std::function<std::string(void)> fp_t;


class DispatchQueue {
public:
    DispatchQueue(std::string name, size_t thread_cnt = 1);
    ~DispatchQueue();
    //move
    void dispatch(fp_t && item);

private:

    std::string _name;
    std::queue<fp_t> _q;
    std::vector<std::thread> _threads;
    void dispatch_thread_handler(void);
    std::mutex _lock;
    std::condition_variable _cv;
    bool _quit;
};

