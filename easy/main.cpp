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

int main(int argc, const char * argv[]) {
    
    struct timeval begin, end;
    gettimeofday(&begin, 0);
    String name = "1234567890";
    String password = "ABCDEFG";
    String result = name + ":" + password;
    
    std::cout<<"拼接结果:"<<result<<std::endl;
    std::cout<<"子串(头10):"<<result.subString(0, 10)<<std::endl;
    std::cout<<"子串(尾7):"<<result.subString(-7)<<std::endl;
    std::cout<<"反转结果:"<<result.reverse()<<std::endl;
    std::cout<<"反转后原字符串:"<<result<<std::endl;
    result.reverseSelf();
    std::cout<<"自身反转结果:"<<result<<std::endl;
    gettimeofday(&end, 0);
    std::cout<<"used: "<<end.tv_usec - begin.tv_usec<<std::endl;

    return 0;
}
