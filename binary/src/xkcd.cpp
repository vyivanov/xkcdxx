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

#include "xkcd.h"
#include "xkcdxx.h"

#include <stdint.h>

#include <string>
#include <memory>

constexpr xkcd_comic XKCD_COMIC_NULL = static_cast<xkcd_comic>(0);

namespace {

thread_local std::string latest_error = {};

template<typename Out, typename Inp>
constexpr Out to(const Inp input) noexcept {
    return reinterpret_cast<Out>(input);
}

template<typename T>
xkcd_comic comic(const T number) noexcept {
    xkcd_comic ret = XKCD_COMIC_NULL;
    try {
        const auto ptr = std::make_unique<xkcdxx::Comic>(number).release();
        const auto idx = ::to<xkcd_comic>(ptr);
        ret = idx;
    } catch (const xkcdxx::Comic::RequestFailed& ex) {
        ::latest_error = ex.what();
    }
    return ret;
}

}

xkcd_comic xkcd_comic_latest(void) {
    return ::comic(xkcdxx::Comic::Number::Latest);
}

xkcd_comic xkcd_comic_random(void) {
    return ::comic(xkcdxx::Comic::Number::Random);
}

xkcd_comic xkcd_comic_exact(const uint32_t number) {
    return ::comic(number);
}

const char* xkcd_comic_error(void) {
    return ::latest_error.c_str();
}

xkcd_info xkcd_comic_info(const xkcd_comic idx) {
    const auto comic = ::to<xkcdxx::Comic*>(idx);
    const auto info  = xkcd_info {
        .number = comic->number()       ,
        .date   = comic->date()         ,
        .url    = comic->url()  .c_str(),
        .title  = comic->title().c_str(),
        .alt    = comic->alt()  .c_str(),
    };
    return info;
}

void xkcd_comic_destroy(const xkcd_comic idx) {
    const auto ptr = ::to<xkcdxx::Comic*>(idx);
    const auto del = std::unique_ptr<xkcdxx::Comic>(ptr);
}
