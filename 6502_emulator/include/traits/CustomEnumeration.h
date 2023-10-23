#pragma once
#include <cstring>
#include <type_traits>
#include <cstdlib>
#include <traits/types.h>


#define CustomEnum(Name, ...)                       \
    struct Name{                                     \
    public:                                         \
        enum Name##_{                               \
            __VA_ARGS__                             \
        };                                          \
        Name(Name::Name##_ v) : mValue(v){}         \
        operator Name::Name##_() const { return mValue; } \
        Name& operator=(Name::Name##_ v){           \
            mValue = v;                             \
            return *this;                           \
        }                                           \
    private:                                        \
        Name::Name##_ mValue;                       \
    }