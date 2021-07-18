//
//  event_loop.h
//  comm
//
//  Created by TimCho on 16/7/2017.
//  Copyright © 2017 vipkid. All rights reserved.
//

#ifndef event_loop_h
#define event_loop_h

#include <iostream>
#include <memory>
#include <thread>

#include "asio.hpp"

#ifdef ANDROID
#include <jni.h>
#ifndef D_EN_MIDDLEWARE_SUPPORT
#include "djinni_support.hpp"
#endif

extern JavaVM * java;
extern JNIEnv * jenv;

#endif

namespace comm
{
  static const int PARALLEL     = 1;
  static const int SEQUENTIAL   = 2;

  extern void jvm_run(std::function<void()> _f);

  class Event
  //:public std::enable_shared_from_this<Event>
  {
  public:
    explicit Event(std::function<void()> _f):fn_ptr_(std::make_shared<std::function<void()>>(_f)){
    };
    void Execute(){(*fn_ptr_.get())();};
  protected:
    std::shared_ptr<std::function<void()>> fn_ptr_;
  };
  
  class DelayEvent
  :public Event
  {
  public:
    explicit DelayEvent(std::function<void()> _f, asio::io_service &_io):Event(_f), timer_(_io){};
    asio::steady_timer& Timer(){
      return timer_;
    };
  protected:
    asio::steady_timer timer_;
  };
  
  class EventLoop
//  :public std::enable_shared_from_this<EventLoop>
  {
  public:
    static void Deleter(EventLoop *ptr){
      ptr->Release();
    }
  public:
    explicit EventLoop(const std::string &_loop_name, const int &_thread_nums = 1);
    asio::io_service& Io(){return io_;};
    void Post(Event *_event, const int &_type = PARALLEL);
    void Post(std::function<void()> _f, const int &_type = PARALLEL);
    void Post(std::shared_ptr<Event> event, const int &_type = PARALLEL);
    void Release();
    void PostDelay(std::function<void()> _f, const uint64_t &_delay/*, const int &_type = PARALLEL*/);
    void PostDelay(std::shared_ptr<DelayEvent> event, const uint64_t &_delay/*, const int &_type = PARALLEL*/);
    void PostDelay(DelayEvent *event, const uint64_t &_delay/*, const int &_type = PARALLEL*/);
  private:
    ~EventLoop();
    EventLoop(const EventLoop &_loop) = delete;
    EventLoop& operator = (const EventLoop &_loop) = delete;
  private:
    asio::io_service io_;
    asio::io_service::strand strand_;
    asio::io_service::work work_;
    std::vector<std::thread> thread_group_;
  };
}

#endif /* event_loop_h */
