//
//  main.cpp
//  easy
//
//  Created by 欧阳建华 on 16/8/10.
//  Copyright © 2016年 hackerc. All rights reserved.
//

#include <iostream>
#include <sys/time.h>
#include <thread>

#include "base.hpp"

#include "Logger.hpp"
using namespace easy;

#define log(x) std::cout<<(x)<<std::endl

int main(int argc, const char * argv[]) {
    
    struct timeval begin, end;
    gettimeofday(&begin, 0);

    easy::runtime::Logger logger;
     easy::runtime::Logger::Init();
    for (int i = 0; i < 200; ++i) {
        logger.debug("Hehe");
        logger.info("Xixi");
        logger.error("Haha");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
   
    
    
    gettimeofday(&end, 0);
    std::cout<<"used: "<<end.tv_usec - begin.tv_usec + ((end.tv_sec - begin.tv_sec) == 0 ? 0 : (end.tv_sec - begin.tv_sec) * 1000000)<<std::endl;

    
    std::this_thread::sleep_for(std::chrono::seconds(100));
    
    return 0;
}
