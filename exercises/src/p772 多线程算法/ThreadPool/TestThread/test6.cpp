#include <iostream>  
#include <future>  
#include <thread>  
  
int main()   
{  
    auto asyncTask = std::async(std::launch::async, [](const char *message) {  
        std::cout << message << std::flush;  
    }, "Hello, ");  
  
    std::cout << "World!" << std::endl;  
    asyncTask.get();  // 等待异步任务完成  
    return 0;  
}