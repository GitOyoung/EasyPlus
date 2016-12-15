#ifndef PROPERTY_H
#define PROPERTY_H
#include <functional>

namespace easy {

template<class _Tp>
class Property {
    typedef _Tp Value;
    typedef _Tp &Ref;
    typedef _Tp *Pointer;
    typedef const _Tp  &ConstRef;
    typedef const _Tp  *ConstPointer;

    typedef std::function<Value()> Get;
    typedef std::function<void(ConstRef)> Set;
    typedef std::function<bool(ConstRef)> WillSet;
public:
    Property(ConstRef init = 0)
        : old(init)
    {

    }

    operator Value() const {
        if(get) {
            old =  get();
        }
        return old;
    }

    Property& operator =(ConstRef other) {
        bool yes = true;
        if(willSet) {
            yes = willSet(other);
        }
        if(yes) {
            if(set) {
                set(other);
            }
            if(didSet) {
                didSet(old);
            }
        }
        return *this;
    }

public:
    Get get;
    WillSet willSet;
    Set  set, didSet;
private:
    mutable Value old;
};

}

#endif // PROPERTY_H
