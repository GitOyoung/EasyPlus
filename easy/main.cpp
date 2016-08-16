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

    
    gettimeofday(&end, 0);
    std::cout<<"used: "<<end.tv_usec - begin.tv_usec<<std::endl;

    return 0;
}
