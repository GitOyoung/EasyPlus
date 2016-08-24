//
//  base.hpp
//  easy
//
//  Created by 欧阳建华 on 16/8/10.
//  Copyright © 2016年 hackerc. All rights reserved.
//

#ifndef base_hpp
#define base_hpp
#include <functional>

namespace easy {    
    namespace base {
#define EASY_DEBUG 0
        
#if EASY_DEBUG == 1
        class Debug {
        public:
            Debug();
            ~Debug();
        };
        
        class String : public Debug{
#else
            class String {
#endif
            public:
                String(char *data, int length);
                String(const char *str = 0);
                String(const String &);
                int length() const;
                int &length();
                int resize(size_t);
                bool startWith(const String &) const;
                bool endWith(const String &) const;
                String &operator=(const char *str);
                String &operator=(const String &other);
                
                String operator()(int index, int length = -1);
                String substring(int index,  int length = -1);
                String operator+(const String &other);
                String& operator+=(const String &other);
                String operator-(int);
                String& operator-=(int);
                operator const char *() const;
                char &operator[](int);
                
                String& trim();
                String& reverse();
                String& append(const String&);
                String& insertAt(int index, char);
                String& insertAt(int index, const char *);
                String& insertAt(int index, const String&);
                String& removeAt(int index, int length = 1);
                
                
                String stringByTrim() const;
                String stringAfterReverse() const;
                String stringByAppend(const String &) const;
                String stringByInsertAt(int index, char) const;
                String stringByInsertAt(int index, const char *) const;
                String stringByInsertAt(int index, const String&) const;
                ~String();
            public:

                static String fromNumber(long long);
                static String fromNumber(double, int pre = 2);
            private:
                class StringStruct;
                StringStruct *priv_;
                String(StringStruct *);
                String(StringStruct &);
            };
            
        template<typename _Tp>
        class BaseType {
        public:
            BaseType(_Tp value = 0): value_(value) {}
            BaseType(const BaseType& other): value_(other.value_){}
            
            template<typename _U>
            BaseType(const BaseType<_U> &other): value_(_U(other)) {}
            BaseType &operator=(_Tp value) {
                value_ = value;
                return *this;
            }
            BaseType &operator=(const BaseType &other) {
                value_ = other.value_;
                return *this;
            }
            
            BaseType &operator=(BaseType &&other) {
                value_ = other.value_;
                return *this;
            }
            
            BaseType operator+(_Tp other) {
                return BaseType(value_ + other);
            }
            
            BaseType &operator+=(_Tp other) {
                value_ += other;
                return *this;
            }
            BaseType operator+(const BaseType &other) {
                
                return BaseType(value_ + other.value_);
            }
            BaseType &operator+=(const BaseType &other) {
                value_ += other.value_;
                return *this;
            }
            BaseType operator-(_Tp other) {
                return BaseType(value_ - other);
            }
            BaseType &operator-=(_Tp other) {
                value_ -= other;
                return *this;
            }
            BaseType operator-(const BaseType &other) {
                return BaseType(value_ - other.value_);
            }
            BaseType &operator-=(const BaseType &other) {
                value_ -= other.value_;
                return *this;
            }
            
            operator _Tp() const {
                return value_;
            }
        protected:
            _Tp value_;
        };
        template <typename _Tp>
        BaseType<_Tp> operator+(_Tp left, const BaseType<_Tp> &right) {
            return BaseType<_Tp>(left + _Tp(right));
        }
        
        template <typename _Tp>
        BaseType<_Tp> operator-(_Tp left, const BaseType<_Tp> &right) {
            return BaseType<_Tp>(left - _Tp(right));
        }
        
        
        class Int: public BaseType<int> {
        public:
            typedef std::function<bool(int)> callBack;
            static Int fromChar(char);
            static Int fromShort(short);
            static Int fromString(const char *);
            static Int fromString(const String&);
        public:
            Int(int value = 0);
            Int(const Int&);
            Int & operator=(int );
            Int & operator=(const Int &);
            Int & operator=(Int &&);
            Int& repeat(callBack cb);
            template<typename U>
            Int(const BaseType<U> &other): BaseType<int>(other) {}
        };
        
        class Int32: public BaseType<signed long> {
            Int32 & operator=(signed long);
            Int32 & operator=(const Int32 &);
            Int32 & operator=(Int32 &&);
        };
        
        class Int64: public BaseType<signed long long> {
            
        };
        class String;
        class Char: public BaseType<char> {
        public:
            Char(char);
            Char(const Char &);
        };
        
        class UChar: public BaseType<unsigned char> {
            
        };

        class UInt: public BaseType<unsigned int> {
            
        };
        
        class UInt32: public BaseType<unsigned long> {
            
        };
        
        class UInt64: public BaseType<unsigned long long> {
            
        };

            
            
    }
    typedef base::Int Int;
    typedef base::Int32 Int32;
    typedef base::Int64 Int64;
    typedef base::Char Char, SByte;
    
    typedef base::UInt UInt;
    typedef base::UInt32 UInt32;
    typedef base::UInt64 UInt64;
    typedef base::UChar UChar, Byte;
    
    typedef base::String String;
    
}




#endif /* base_hpp */
