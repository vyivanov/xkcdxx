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

#include <stdexcept>
#include <string>
#include <cstdint>
#include <ctime>
#include <memory>

#ifndef API_XKCDXX
#define API_XKCDXX __attribute__((visibility("default")))
#endif

namespace xkcdxx {

class API_XKCDXX Comic {
public:
    enum class Number {
        Latest, Random
    };
    struct request_failed final: std::runtime_error {
        explicit request_failed(const std::string& why) noexcept;
    };
    explicit Comic(Comic::Number number);
    explicit Comic(std::uint32_t number);
    virtual ~Comic();
public:
    const std::uint32_t& number() const noexcept;
    const std::time_t&   date()   const noexcept;
    const std::string&   url()    const noexcept;
    const std::string&   title()  const noexcept;
    const std::string&   alt()    const noexcept;
private:
    class Impl;
    const std::shared_ptr<const Comic::Impl> m_pimpl;
};

};
