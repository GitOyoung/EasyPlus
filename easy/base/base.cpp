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

#define dbg(x) std::cout<<(x)<<std::endl
#else
#define dbg(x)
#endif


namespace easy {
    
    namespace  util {
        size_t suggestSize(size_t real) {
            return real + 1;
        }
    }
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
    
    Int &Int::repeat(callBack cb) {
        int index = 0;
        while(index < *this && cb(index++));
        return *this;
    }
    
    Int Int::fromChar(char c) {
        return  Int((int)c);
    }
    
    Int Int::fromShort(short s) {
        return Int((int)s);
    }
    
    Int Int::fromString(const char *str) {
        int value = 0;
        Int len((int)strlen(str));
        len.repeat([&](int i) -> bool {
            if(str[i] >= '0' && str[i] <= '9') {
                value = value * 10 + str[i] - '0';
                return true;
            }
            return false;
        });
        return Int(value);
    }
    
    Int Int::fromString(const easy::base::String &str) {
        Int length(str.length());
        int value = 0;
        length.repeat([&](int i)-> bool {
            if(str[i] >= '0' && str[i] <= '9') {
                value = value * 10 + str[i] - '0';
                return true;
            }
            return false;
        });
        return Int(value);
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
        int resize(size_t);  //重新分配空间，返回空间变化大小, 单位byte
        StringStruct& insertAt(int index, const char *str, size_t length);
        bool startWith(const StringStruct &) const;
        bool endWith(const StringStruct &) const;
        operator const char *() const {
            data_[length_] = '\0';
            return data_;
        }
        
        StringStruct &operator=(const char *);
        StringStruct &operator=(const StringStruct &);
        StringStruct &operator+(const StringStruct &);
        StringStruct &operator+=(const StringStruct &);
        char *data() const {
            return data_;
        }
    private:
        size_t length_;
        size_t size_;
        char *data_;
    };
    
#if EASY_DEBUG == 1
    base::Debug::Debug() {
        std::cout<<"构造次数+1"<<std::endl;
    }
    
    base::Debug::~Debug() {
        std::cout<<"析够次数+1"<<std::endl;
    }
#endif
    String::String(char *data, int length): priv_(new StringStruct(data, length)) {}
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
    
    int String::resize(size_t size) {
        return priv_->resize(size);
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
    
    char &String::operator[](int i) {
        char *p = priv_->data();
        return *(p + i);
    }
    
    String& String::append(const easy::base::String &other) {
        return *this += other;
    }
    
    String String::stringByAppend(const easy::base::String &other) const {
        String cp(*this);
        return cp += other;
    }
    

    
    String String::operator()(int index, int  length) {
        return substring(index, length);
    }
    String String::substring(int index, int length) {
        int len = this->length();
        index > len && (index = len);
        index < -len && (index = -len);
        const char *str =  (const char *)*priv_ + index;
        if(index < 0) str += this->length();
        if(length < 0) length = (int)strlen(str);
        return String(new StringStruct(str, length));
    }
    
    String& String::insertAt(int index, char c) {
        (index < 0 || index > length()) ||
        priv_->insertAt(index, &c, 1);
        return *this;
    }
    
    String& String::insertAt(int index, const char *str) {
        (str == 0 || index < 0 || index > length()) ||
        priv_->insertAt(index, str, strlen(str));
        return *this;
    }
    
    String& String::insertAt(int index, const easy::base::String &str) {
        (index < 0 || index > length()) ||
        priv_->insertAt(index, str, str.length());
        return *this;
    }
    
    String& String::removeAt(int index, int length) {
        int left = this->length() - index;
        length > left && (length =  left);
        //TODO
        return *this;
    }
    
    String String::stringByTrim() const {
        String cp(*this);
        return cp.trim();
    }
    
    String String::stringByInsertAt(int index, char c) const {
        String cp(*this);
        return cp.insertAt(index, c);
    }
    
    String String::stringByInsertAt(int index, const char *str) const {
        String cp(*this);
        return cp.insertAt(index, str);
    }
    
    String String::stringByInsertAt(int index, const easy::base::String &str) const {
        String cp(*this);
        return cp.insertAt(index, str);
    }
    
    String String::operator+(const easy::base::String &other) {
        return String(*priv_ + *other.priv_);
    }
    
    String &String::operator+=(const easy::base::String &other) {
        *priv_ += *other.priv_;
        return *this;
    }
    
    String String::operator-(int tail) {
        int length = this->length() - tail;
        return length > 0 ? substring(0, length) : String();
    }
    
    String& String::operator-=(int tail) {
        if(length() >= tail) length() -= tail;
        return *this;
    }
    
    String& String::trim() {
        priv_->trim();
        return *this;
    }
    
    String String::fromNumber(long long ll) {
        char str[20];
        sprintf(str, "%lld", ll);
        return String(str);
    }
    
    String String::fromNumber(double db, int pre) {
        char str[32];
        char fmt[8];
        sprintf(fmt, "%%.%df", pre);
        sprintf(str, fmt, db);
        return String(str);
    }
    
    String::~String() {
        
        
        if(priv_ != 0){
#if EASY_DEBUG  == 1
            std::cout<<"String: "<<*this<<" 释放次数+1"<<std::endl;
#endif
            delete priv_;
            priv_ = 0;
        }
        
    }
    
    
    String::StringStruct::StringStruct(const char *str, size_t length): length_(length), size_(util::suggestSize(length)) {
        if(str != 0) {
            data_ = new char[size_];
        } else {
            length_ = 0;
            data_ = new char[size_];
        }
        memcpy(data_, str, length_);
    }
    
    String::StringStruct::StringStruct(char *str, int length): length_(length), size_(util::suggestSize(length_)), data_(str) {}
    
    String::StringStruct::StringStruct(const StringStruct &other): length_(other.length_), size_(other.size_), data_(new char[other.size_]) {
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
    
    int String::StringStruct::resize(size_t size) {
        int delta = int(size - size_);
        char *data = 0;
        if (delta > 0) {
            data = new char[size];
            memcpy(data, data_, length_);
            delete [] data_;
            data_ = data;
            size_ = size;
            return delta;
        } else {
            return  0;
        }
    }
    
    String::StringStruct& String::StringStruct::insertAt(int index, const char *str, size_t length) {
        size_t total = length_ + length;
        if(length == 0 || index < 0 || index > length_) return *this;
        if (total > size_) {
            resize(util::suggestSize(total));
        }
        size_t i = length_;
        while (i-- > index) {
            data_[i + length] = data_[i];
        }
        memcpy(data_ + index, str, length);
        length_ = total;
        return *this;
    }
    
    String::StringStruct & String::StringStruct::operator=(const char *str) {
        if(str != data_) {
            size_t strLen = strlen(str);
            if(size_ < strLen + 1) {
                delete[] data_;
                size_ = strLen + 1;
                data_ = new char[size_];
            }
            length_ = strLen;
            
            memcpy(data_, str, length_);
        }
        return *this;
    }
    
    String::StringStruct & String::StringStruct::operator=(const String::StringStruct &other) {
        if (this != &other) {
            if(size_ < other.length_ ) {
                delete [] data_;
                size_ = other.length_ + 1;
                data_ = new char[size_];
            }
            length_ = other.length_;
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
    
    String::StringStruct& String::StringStruct::operator+=(const easy::base::String::StringStruct &other) {
        size_t length = length_ + other.length_;
        if(size_ < length + 1) {
            size_ = length + 1;
            char *str = new char[size_];
            memcpy(str, data_, length_);
            delete [] data_;
            data_ = str;
        }
        memcpy(data_ + length_, other.data_, other.length_);
        length_ = length;
        return *this;
    }
    
    
}
