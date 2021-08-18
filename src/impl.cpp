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

#include "impl.h"
#include "xkcdxx.h"

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "dep/httplib.h"
#include "dep/picojson.h"

#include <cstdint>
#include <random>
#include <string>
#include <ctime>
#include <sstream>

namespace xkcdxx {

Comic::Impl::Impl(const Comic::Number number)
    : m_info(get_info(number)) {
}

Comic::Impl::Impl(const std::uint32_t number)
    : m_info(get_info(number)) {
}

Comic::Impl::Info Comic::Impl::get_info(const Comic::Number number) {
    Impl::Info info = {};
    if (Comic::Number::Random == number) {
        auto rnd = std::random_device();
        auto gen = std::mt19937(rnd());
        auto end = get_info(Comic::Number::Latest).number;
        auto uid = std::uniform_int_distribution<std::uint32_t>(1, end);
        info = get_info(uid(gen));
    } else if (Comic::Number::Latest == number) {
        info = do_request("/info.0.json");
    } else {
        assert("uncovered branch" && false);
    }
    return info;
}

Comic::Impl::Info Comic::Impl::get_info(const std::uint32_t number) {
    return do_request("/" + std::to_string(number) + "/info.0.json");
}

Comic::Impl::Info Comic::Impl::do_request(const std::string& resource) {
    auto xkcd = httplib::Client{"https://xkcd.com"};
    xkcd.set_keep_alive(true);
    xkcd.set_follow_location(true);
    xkcd.enable_server_certificate_verification(false);
    const httplib::Result response = xkcd.Get(resource.c_str());
    if (response && response->status == 200) {
        picojson::value json = {};
        picojson::parse(json, response->body);
        std::tm date = {};
        {
            date.tm_mday = std::stoi(json.get("day")  .to_str()) - 0;
            date.tm_mon  = std::stoi(json.get("month").to_str()) - 1;
            date.tm_year = std::stoi(json.get("year") .to_str()) - 1900;
        }
        Impl::Info info = {};
        {
            info.number = std::stoi(json.get("num").to_str());
            info.date   = std::mktime(&date);
            info.url    = json.get("img")  .to_str();
            info.title  = json.get("title").to_str();
            info.alt    = json.get("alt")  .to_str();
        }
        return info;
    } else {
        if (response) {
            const auto why = std::string{"xkcd.com returned:\x20"} + httplib::detail::status_message(response->status);
            throw Comic::RequestFailed(why);
        } else {
            std::stringstream ss{};
            ss << response.error();
            const auto why = std::string{"network error:\x20"} + ss.str();
            throw Comic::RequestFailed(why);
        }
    }
}

};
