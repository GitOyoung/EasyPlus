//
//  main.cpp
//  easy
//
//  Created by 欧阳建华 on 16/8/10.
//  Copyright © 2016年 hackerc. All rights reserved.
//

#include <iostream>
#include <sys/time.h>

#include "base.hpp"
using namespace easy;

#define log(x) std::cout<<(x)<<std::endl

int main(int argc, const char * argv[]) {
    
    struct timeval begin, end;
    gettimeofday(&begin, 0);
    
    String name = "12 34 56 7 8 90";
    String password = "AB CD E FG";
    String result = name + ":" + password;
    log(result);
    log(result.stringByTrim());
    result.trim();
    String cn = "你好啊abc";
    log(cn.length());
    log(result.stringByInsertAt(9, "987654321"));
    log(result);
    gettimeofday(&end, 0);
    std::cout<<"used: "<<end.tv_usec - begin.tv_usec + ((end.tv_sec - begin.tv_sec) == 0 ? 0 : (end.tv_sec - begin.tv_sec) * 1000000)<<std::endl;

    return 0;
}
