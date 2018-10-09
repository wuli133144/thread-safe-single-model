#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <chrono>
#include <string>
#include <vector>
#include <array>
#include <atomic>
#include <stdio.h>
#include <unordered_map>
#include <deque>
#include <functional>
#include <algorithm>
#include <unistd.h>
using namespace std;



std::atomic<size_t>  threadNum{20};
std::mutex            mu;
int                   count=0;
condition_variable    cond;

using  task=function<void()>;


std::deque<task>queue;
//test condition_variable

int test()
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout<<"test sleep"<<std::endl;
    return 3;
}



int add()
{
  
      size_t size=queue.size();
      if(size > INT32_MAX)
      {
          return 0;
      }
      {
        std::unique_lock<std::mutex>lock1(mu);
        queue.emplace_back([&](){
            std::cout<<"task"<<std::endl;
        });
        
        if (!queue.empty()) {
            /* code */
            cond.notify_one();
        }
        lock1.unlock();
      }


}


class single{

public: 
    static single *app;
    static std::mutex m_mutex;
    static single *Instance(){
        if(nullptr==app)
        {
            //std::lock_guard<std::mutex>lock(m_mutex);
            m_mutex.lock();
            if(nullptr==app)
            {
                app=new single();
            }
            m_mutex.unlock();

        }
        return app;
    }

    static void destroy(){
        std::lock_guard<std::mutex>lock(m_mutex);
        if(nullptr!=app){
            delete app;
            app=nullptr;
             std::cout<<"destroy!"<<std::endl;

        }
    }
   
private:
    single(){}
    ~single(){}
    
public:
     void handle(){
         std::cout<<"hello world"<<std::endl;
     }

};

 single * single::app=nullptr;
 std::mutex single::m_mutex;


int main(){
   

  
 single *app=single::Instance();
 app->handle();
 single::destroy();

 single::destroy();
 single::destroy();
 app->handle();



vector<std::thread *>threads(100);
std::transform(threads.begin(),threads.end(),threads.begin(),[](std::thread *p){
    
    return new  thread([](){
         single *app=single::Instance();
         app->handle();
         single::destroy();
    });    
});

for_each(threads.begin(),threads.end(),[](std::thread *pthread){
    if(pthread->joinable()){
        pthread->join();
    }
});








// packaged_task<int (void)>task(test);
// std::future<int>fu=task.get_future();
// thread t(std::move(task));

// try
// {
//     /* code */
//     int ret=fu.get();
//     fu.get();
//     std::cout<<"result="<<ret<<std::endl;
// }
// catch(const std::future_error& e)
// {
//     std::cerr << e.what() << '\n';
// }

// t.join();

//    std::thread t([&](){
//        std::this_thread::sleep_for(chrono::milliseconds(3000));   
        
//    });
    
//     vector<std::thread>threads;
//     for(auto i=0;i <threadNum ;i++)
//     {
//          threads.emplace_back(thread([=](){
//                  std::cout<<">>>>>>>>>>>>>thread>>>>>>>>>>"<<this_thread::get_id()<<std::endl;
//                  std::lock_guard<std::mutex>guard(mu);
//                  count++;
//                  std::cout<<"safa-thread count"<<count<<std::endl;
//          }));
//     }
   
//    std::cout<<"hello world"<<std::endl;
//     //t.join();
//     for(auto i=0;i <threadNum;i++)
//     {
//          threads[i].join();   
//     }
    return 0;
}
