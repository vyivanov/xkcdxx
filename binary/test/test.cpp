#include "xkcdxx.h"

#include <iostream>

int main() {
    try {
        xkcdxx::Comic a{xkcdxx::Comic::Number::Random};
        xkcdxx::Comic b{a};
        std::cout << (a.number() == b.number()) << '\x20' << a.number() << '\n';
        std::cout << (a.date()   == b.date())   << '\x20' << a.date()   << '\n';
        std::cout << (a.url()    == b.url())    << '\x20' << a.url()    << '\n';
        std::cout << (a.title()  == b.title())  << '\x20' << a.title()  << '\n';
        std::cout << (a.alt()    == b.alt())    << '\x20' << a.alt()    << '\n';
    } catch (const xkcdxx::Comic::RequestFailed& ex) {
        std::cout << ex.what() << '\n';
    }
}
