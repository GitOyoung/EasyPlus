//
//  main.cpp
//  easy
//
//  Created by 欧阳建华 on 16/8/10.
//  Copyright © 2016年 hackerc. All rights reserved.
//

#include <iostream>

#include "base.hpp"
using namespace easy;

int main(int argc, const char * argv[]) {
    
//    Int a = 0xCC; //相当于Int a(Int(9));
    String s("123 45 67 8 9");
    
    
    String ss("abc d ef g h");
    
    ss = s + ss;
    
    std::cout<<ss<<std::endl;
    ss.trim();
    std::cout<<ss<<std::endl;
    ss = ss - 8;
    std::cout<<ss<<std::endl;
    ss -=3;
    ss += "hah";
    std::cout<<ss<<std::endl;
    return 0;
}
