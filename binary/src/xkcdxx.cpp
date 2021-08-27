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

#include "xkcdxx.h"
#include "impl.h"

#include <string>
#include <stdexcept>
#include <memory>
#include <cstdint>
#include <ctime>

namespace xkcdxx {

Comic::RequestFailed::RequestFailed(const std::string& why) noexcept
    : std::runtime_error(why) {
}

Comic::Comic(const Comic::Number number)
    : m_pimpl(std::make_shared<Comic::Impl>(number)) {
}

Comic::Comic(const std::uint32_t number)
    : m_pimpl(std::make_shared<Comic::Impl>(number)) {
}

Comic::~Comic() = default;

const std::uint32_t& Comic::number() const noexcept {
    return m_pimpl->number();
}

const std::time_t& Comic::date() const noexcept {
    return m_pimpl->date();
}

const std::string& Comic::url() const noexcept {
    return m_pimpl->url();
}

const std::string& Comic::title() const noexcept {
    return m_pimpl->title();
}

const std::string& Comic::alt() const noexcept {
    return m_pimpl->alt();
}

}
