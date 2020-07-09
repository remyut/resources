//
// Created by remy on 30/6/20.
//
#include "../../../../../../oboe-c-lib/oboe/src/common/OboeDebug.h"
#include "DispatchQueue.h"
#include <iostream>

DispatchQueue::DispatchQueue(std::string name, size_t thread_cnt) : _name{std::move(name)}, _threads(thread_cnt)
{
    for(size_t i = 0; i < _threads.size(); i++)
        _threads[i] = std::thread(&DispatchQueue::dispatch_thread_handler, this);
}

DispatchQueue::~DispatchQueue()
{
    LOGD("Destructor: Destroying dispatch threads...\n");


    // Signal to dispatch threads that it's time to wrap up
    std::unique_lock<std::mutex> lock(_lock);
    _quit = true;
    lock.unlock();
    _cv.notify_all();

    // Wait for threads to finish before we exit
    for(size_t i = 0; i < _threads.size(); i++)
    {
        if(_threads[i].joinable())
        {
            LOGD("Destructor: Joining thread %zu until completion \n", i);
            _threads[i].join();
        }
    }
}

void DispatchQueue::dispatch(fp_t &&item)
{
    std::unique_lock<std::mutex> lock(_lock);

    //add condition variable if queue not full jai pas de taille de Queue.

    _q.push(item);

    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lock.unlock();
    _cv.notify_one();
}

void DispatchQueue::dispatch_thread_handler(void){

    std::unique_lock<std::mutex> lock(_lock);
    //std::cout << "In thread handler" << std::endl;

    do {
        //wait until we have data in the queue or quit signal
        _cv.wait(lock, [this] { return(_q.size() || _quit);
        });

        //after the wait we own the lock
        if(!_quit && _q.size()) {
            auto op = std::move(_q.front());
            _q.pop();

            //unlock now that we're done messing with the queue
            lock.unlock();

            auto data = op();

            LOGD("In the dispatcher  op() : %s", data.c_str());


            //do some operation
            lock.lock(); //relock because the conditino variable will take care of releasing the lock or keep it lock if the condition is satisfied.
        }
    } while(!_quit);
}


