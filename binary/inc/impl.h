/*

MIT License

Copyright (c) 2021 Vladimir Yu. Ivanov <inbox@vova-ivanov.info>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#pragma once

#include "xkcdxx.h"

#include <cstdint>
#include <ctime>
#include <string>

#ifndef PRIVATE_XKCDXX
#define PRIVATE_XKCDXX __attribute__((visibility("hidden")))
#endif

namespace xkcdxx {

class PRIVATE_XKCDXX Comic::Impl final {
public:
    explicit Impl(Comic::Number number);
    explicit Impl(std::uint32_t number);
public:
    const std::uint32_t& number() const noexcept { return m_info.number; }
    const std::time_t&   date()   const noexcept { return m_info.date;   }
    const std::string&   url()    const noexcept { return m_info.url;    }
    const std::string&   title()  const noexcept { return m_info.title;  }
    const std::string&   alt()    const noexcept { return m_info.alt;    }
private:
    struct Info {
        std::uint32_t number;
        std::time_t   date;
        std::string   url;
        std::string   title;
        std::string   alt;
    };
    static Impl::Info get_info(Comic::Number number);
    static Impl::Info get_info(std::uint32_t number);
    static Impl::Info do_request(const std::string& url);
private:
    const Impl::Info m_info;
};

};
