//
//  base.cpp
//  easy
//
//  Created by 欧阳建华 on 16/8/10.
//  Copyright © 2016年 hackerc. All rights reserved.
//

#include "base.hpp"
#include <string.h>

#if EASY_DEBUG > 0u
#include <iostream>
#endif


namespace easy {
    
    Int::Int(int value) : BaseType<int>(value) {}
    Int::Int(const Int& other): BaseType<int>(other) {}
    
    Int &Int::operator=(const easy::Int &other) {
        BaseType<int>::operator=(other);
        return *this;
    }
    
    Int &Int::operator=(int other) {
        BaseType<int>::operator=(other);
        return *this;
    }
    
    Int &Int::operator=(easy::Int && other) {
        BaseType<int>::operator=(other);
        return *this;
    }
    
    Int32& Int32::operator=(const easy::Int32 &other) {
        BaseType<signed long>::operator=(other);
        return *this;
    }
    
    Int32& Int32::operator=(easy::Int32 &&other) {
        BaseType<signed long>::operator=(other);
        return *this;
    }
    
    Int32& Int32::operator=(signed long other) {
        BaseType<signed long>::operator=(other);
        return *this;
    }
    
    Char::Char(char c): BaseType<char>(c) {}
    Char::Char(const Char &other): BaseType<char>(other) {}
    

    class String::StringStruct {
    public:
        StringStruct(const char *str = 0, size_t length = 0);
        StringStruct(char *str, int length);
        StringStruct(const StringStruct &other);
        int length() const;
        int &length();
        StringStruct &trim();
        bool startWith(const StringStruct &) const;
        bool endWith(const StringStruct &) const;
        operator const char *() const {
            data_[length_] = '\0';
            return data_;
        }
        
        StringStruct &operator=(const char *);
        StringStruct &operator=(const StringStruct &);
        StringStruct &operator+(const StringStruct &);
  
    private:
        size_t length_;
        char *data_;
    };

#if EASY_DEBUG > 0u
    base::Debug::Debug() {
        std::cout<<"构造次数+1"<<std::endl;
    }
    
    base::Debug::~Debug() {
        std::cout<<"析够次数+1"<<std::endl;
    }
#endif

    String::String(const char *str): priv_(new StringStruct(str, strlen(str))) {}
    String::String(const String &other): priv_(new StringStruct(*other.priv_)) {}
    
    String::String(String::StringStruct *priv): priv_(priv) {}
    String::String(String::StringStruct &priv): priv_(&priv) {}
    
    int String::length() const {
        return priv_->length();
    }
    
    int &String::length() {
        return priv_->length();
    }
    
    bool String::startWith(const easy::base::String &str) const {
        return priv_->startWith(*str.priv_);
    }
    
    bool String::endWith(const easy::base::String &str) const {
        return priv_->endWith(*str.priv_);
    }
    
    String::operator const char *() const {
        return (const char *)*priv_;
    }
    
    String &String::operator=(const char *str) {
        priv_->operator=(str);
        return *this;
    }
    
    String &String::operator=(const easy::base::String &other) {
        priv_->operator=(*other.priv_);
        return *this;
    }
    
    String String::subString(int index, int length) {
        const char *str =  (const char *)*priv_ + index;
        if(index < 0) str += this->length();
        if(length < 0) length = (int)strlen(str);
        return String(new StringStruct(str, length));
    }
    
    String String::operator+(const easy::base::String &other) {
        return String(*priv_ + *other.priv_);
    }
    
    String &String::operator+=(const easy::base::String &other) {
        if(other.length() > 0)*this = *this + other;
        return *this;
    }
    
    String String::operator-(int tail) {
        int length = this->length() - tail;
        return length > 0 ? subString(0, length) : String();
    }
    
    String& String::operator-=(int tail) {
        if(length() >= tail) length() -= tail;
        return *this;
    }
    
    String& String::trim() {
        priv_->trim();
        return *this;
    }
    
    String::~String() {
        
        
        if(priv_ != 0){
#if EASY_DEBUG > 0u
            std::cout<<"String: "<<*this<<" 释放次数+1"<<std::endl;
#endif
            delete priv_;
        }
        priv_ = 0;
    }
    
    
    String::StringStruct::StringStruct(const char *str, size_t length): length_(length) {
        if(str != 0) {
            data_ = new char[length_ + 1];
        } else {
            length_ = 0;
            data_ = new char[1];
        }
        memcpy(data_, str, length_);
    }
    
    String::StringStruct::StringStruct(char *str, int length): length_(length), data_(str) {}
    
    String::StringStruct::StringStruct(const StringStruct &other): length_(other.length_), data_(new char[length_ + 1]) {
        memcpy(data_, other.data_, length_);
    }
    
    int String::StringStruct::length() const {
        return (int)length_;
    }
    
    int &String::StringStruct::length() {
        return *(int *)&length_;
    }
    
    bool String::StringStruct::startWith(const easy::base::String::StringStruct &start) const {
        if(length_ < start.length_) return false;
        for(int i = 0; i < start.length_; ++i) {
            if(data_[i] != start.data_[i]) return false;
        }
        return true;
    }
    
    bool String::StringStruct::endWith(const easy::base::String::StringStruct &end) const {
        if(length_ < end.length_) return false;
        const char *pChar = &data_[length_ - 1];
        size_t length = end.length_;
        while (length--) {
            if( *pChar-- != end.data_[length]) return false;
        }
        return true;
    }
    
    String::StringStruct& String::StringStruct::trim() {
        int currentIndex = 0;
        size_t index = 0;
        char currentChar;
        while(index < length_) {
            currentChar = data_[index++];
            if(currentChar != ' ' && currentChar != '\r' && currentChar != '\n') {
                data_[currentIndex++] = currentChar;
            }
        }
        length_ = currentIndex;
        return *this;
    }
    
    String::StringStruct & String::StringStruct::operator=(const char *str) {
        if(str != data_) {
            delete[] data_;
            length_ = strlen(str);
            data_ = new char[length_ + 1];
            memcpy(data_, str, length_);
        }
        return *this;
    }
    
    String::StringStruct & String::StringStruct::operator=(const String::StringStruct &other) {
        if (this != &other) {
            delete [] data_;
            length_ = other.length_;
            data_ = new char[length_ + 1];
            memcpy(data_, other.data_, length_);
        }
        return *this;
    }
    
    String::StringStruct& String::StringStruct::operator+(const easy::base::String::StringStruct &other) {
        size_t length = length_ + other.length_;
        char *data = new char[length + 1];
        memcpy(data, data_, length_);
        memcpy(data + length_, other.data_, other.length_);
        return *new StringStruct(data, (int)length);
    }
    
    
    
}
