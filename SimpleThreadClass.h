#ifndef SIMPLETHREADCLASS_H
#define SIMPLETHREADCLASS_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

class SimpleThread{
public:
    SimpleThread(){

    }
    ~SimpleThread(){
        if(thread.joinable())
            std::terminate();//
    }
    SimpleThread(SimpleThread const&) = delete;
    SimpleThread operator = (SimpleThread const&) = delete;
    bool StartThread(){thread = std::thread(&SimpleThread::Run, this);
                       if(thread.joinable()) return true;
                       return false;}
    //virtual function
    virtual void configure(){return;}
    virtual void start(){return;}
    //
    void Run(){
        configure();
        start();
    }
    //
    bool Pause(){
        if(stopedThread)
        {
            std::unique_lock<std::mutex> lk(mute);  //don't call function from main thread. stop it
            dataCond.wait(lk,[this]
            {return !stopedThread;});
        }
        return stopedThread;
    }
    //
    bool Continue(){
        stopedThread = !stopedThread;
        std::lock_guard<std::mutex> lk(mute);
        dataCond.notify_all();
        return stopedThread;
    }
    bool Stop(){
        if(thread.joinable())
            thread.join();
        return true;
    }
    bool stopedThread;
    bool stopMeasurements;
private:
    std::condition_variable dataCond;//переменная для ожидания условия
    std::mutex mute;//
protected:
    std::thread thread;//измерительный поток
};

#endif // SIMPLETHREADCLASS_H
