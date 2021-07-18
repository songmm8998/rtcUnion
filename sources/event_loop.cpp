//
//  event_loop.cpp
//  comm
//
//  Created by TimCho on 16/7/2017.
//  Copyright © 2017 vipkid. All rights reserved.
//

#include "event_loop.h"
#include <chrono>
#include "comm_defs.h"
#ifndef BUILD_TARGET_WINDOWS
#include <pthread.h>
#endif

namespace comm
{
#ifdef ANDROID
#ifndef D_EN_MIDDLEWARE_SUPPORT
    static pthread_key_t g_thread_key;
    static pthread_once_t g_key_once = PTHREAD_ONCE_INIT;
    
    static void VIPKID_JNI_ThreadDestroyed(void* value)
    {
        JavaVM *jvm =djinni::getJavaVM();
        JNIEnv *env = (JNIEnv*) value;
        if (env != NULL) {
            jvm->DetachCurrentThread();
            pthread_setspecific(g_thread_key, NULL);
        }
    }

    static void make_thread_key()
    {
        pthread_key_create(&g_thread_key, VIPKID_JNI_ThreadDestroyed);
    }

    jint VIPKID_JNI_SetupThreadEnv(JNIEnv **p_env)
    {
        JavaVM *jvm =djinni::getJavaVM();
        
        if (!jvm) {
            return -1;
        }

        pthread_once(&g_key_once, make_thread_key);
        //pthread_t tid = pthread_self();
        JNIEnv *env = (JNIEnv*) pthread_getspecific(g_thread_key);
        if (env) {
            *p_env = env;
            return 0;
        }
        const jint get_res = jvm ->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6);
        switch (get_res) {
            case JNI_OK:
                pthread_setspecific(g_thread_key, env);
                *p_env = env;
                break;
            case JNI_EDETACHED:
                if (jvm->AttachCurrentThread(&env, NULL) == JNI_OK) {
                    pthread_setspecific(g_thread_key, env);
                    *p_env = env;

                }
                break;
            default:
                return -1;
        }
        return 0;
    }
#endif //D_EN_MIDDLEWARE_SUPPORT
#endif //ANDROID

    void jvm_run(std::function<void()> _f)
    {
#ifdef BUILD_TARGET_ANDROID
#ifndef D_EN_MIDDLEWARE_SUPPORT
        JNIEnv * jenv=NULL;
        int ret = VIPKID_JNI_SetupThreadEnv(&jenv);
        if(ret != 0) return;
#endif
        _f();
#else
    _f();
#endif
}

  EventLoop::EventLoop(const std::string &_loop_name, const int &_thread_nums)
  :strand_(io_), work_(io_)
  {
    for(int i = 0; i < _thread_nums; i++){
      thread_group_.emplace_back([=](){
        io_.run();
      });
    }
  }
  
  EventLoop::~EventLoop()
  {
    std::cerr << "~EventLoop" <<std::endl;
  }
  
  void EventLoop::Release()
  {
    std::cerr << "Loop Release" <<std::endl;
    io_.stop();
    work_.~work();
    std::thread t([=](){
#ifndef BUILD_TARGET_WINDOWS
    #ifdef BUILD_TARGET_ANDROID
        pthread_setname_np(pthread_self(),"Cleaner");
    #else
		pthread_setname_np("Cleaner");
    #endif
#endif
      for(auto &thread : thread_group_){
        if(thread.joinable()){
          std::cerr << "Join" <<std::endl;
          thread.join();
        }
      }
      delete this;
    });
    t.detach();
  }
  
  void
  EventLoop::Post(Event *event, const int &_type)
  {
    switch (_type) {
      case PARALLEL:
      {
        io_.dispatch([=](){
          event->Execute();
          free(event);
        });
        break;
      }
      case SEQUENTIAL:
        strand_.post([=](){
          event->Execute();
          free(event);
        });
        break;
    }
  }
  
  void
  EventLoop::Post(std::shared_ptr<Event> event, const int &_type)
  {
    switch (_type) {
      case PARALLEL:
      {
        io_.dispatch([=](){
          event->Execute();
        });
        break;
      }
      case SEQUENTIAL:
        strand_.post([=](){
          event->Execute();
        });
        break;
    }
  }
  
  void
  EventLoop::Post(std::function<void()> _f, const int &_type)
  {
    std::shared_ptr<std::function<void()>> fun_ptr = std::make_shared<std::function<void()>>(std::move(_f));
    switch (_type) {
      case PARALLEL:
      {
        io_.dispatch([=](){
          (*fun_ptr.get())();
        });
        break;
      }
      case SEQUENTIAL:
        strand_.post([=](){
          (*fun_ptr.get())();
        });
        break;
    }
  }
  
  void
  EventLoop::PostDelay(std::function<void()> _f, const uint64_t &_delay/*, const int &_type = PARALLEL*/)
  {
    std::shared_ptr<DelayEvent> event = std::make_shared<DelayEvent>(_f, io_);
    PostDelay(event, _delay);
  }
 
  void
  EventLoop::PostDelay(std::shared_ptr<DelayEvent> event, const uint64_t &_delay/*, const int &_type*/)
  {
    /*
    switch (_type) {
      case PARALLEL:
     */
        if(_delay > 0){
          event->Timer().expires_from_now(std::chrono::milliseconds(_delay));
          event->Timer().async_wait([=](std::error_code ec){
            if(ec.value() == 0){
              event->Execute();
            }
          });
        }else{
          io_.dispatch([=](){
            event->Execute();
          });
        }
    /*
        break;
      case SEQUENTIAL:
        if(_delay > 0){
          event->Timer().expires_from_now(std::chrono::milliseconds(_delay));
          event->Timer().async_wait(strand_.wrap([=](asio::error_code ec){
            if(ec.value() == 0){
              event->Execute();
            }
          }));
        }else{
          io_.post(strand_.wrap([=](){
            event->Execute();
          }));
        }
        break;
    }
     */
  }
  
  void
  EventLoop::PostDelay(DelayEvent *event, const uint64_t &_delay/*, const int &_type*/)
  {
    /*
    switch (_type) {
      case PARALLEL:
     */
        if(_delay > 0){
          event->Timer().expires_from_now(std::chrono::milliseconds(_delay));
          event->Timer().async_wait([=](std::error_code ec){
            if(ec.value() == 0){
              event->Execute();
            }
            free(event);
          });
        }else{
          io_.dispatch([=](){
            event->Execute();
            free(event);
          });
        }
    /*
        break;
      case SEQUENTIAL:
        if(_delay > 0){
          event->Timer().expires_from_now(std::chrono::milliseconds(_delay));
          event->Timer().async_wait(strand_.wrap([=](std::error_code ec){
            if(ec.value() == 0){
              event->Execute();
            }
            free(event);
          }));
        }else{
          io_.post(strand_.wrap([=](){
            event->Execute();
            free(event);
          }));
        }
        break;
    }
     */
  }

  
}
