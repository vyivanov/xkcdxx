# xkcdxx

![](https://img.shields.io/github/v/tag/vyivanov/xkcdxx?color=green&label=release)
![](https://img.shields.io/badge/support-C-blue.svg)
![](https://img.shields.io/badge/support-C++-blue.svg)
![](https://img.shields.io/badge/support-Python3-blue.svg)

This library could be used to bring funny [xkcd][1] web-comics to your applications.

Like this:

![Exploits of a Mom](https://imgs.xkcd.com/comics/exploits_of_a_mom.png "Her daughter is named Help I'm trapped in a driver's license factory.")

Do you remember? [Live][2] example. The work was inspired by existing [Python][3] package.

[1]: https://xkcd.com/
[2]: https://clck.app/
[3]: https://pypi.org/project/xkcd/

## Description

There are no specific external dependencies except stuff in standards and popular [OpenSSL][4] (>= 1.1.1) library.
Implemented both static and shared thread-safe variants.

Supported interfaces:

- Plain C
- Modern C++
- Python-3 binding

Pre-built packages:

- Ubuntu 18.04 LTS, amd64
- Ubuntu 20.04 LTS, amd64

[4]: https://www.openssl.org/

## Installation guide

Ready packages are available from Canonical PPA:

```bash
$ sudo add-apt-repository --yes --update ppa:vyivanov/xkcdxx
$ sudo apt install --yes xkcdxx python3-xkcdxx
```

## Usage examples

- **Plain C** &ndash; [complete interface](binary/inc/xkcd.h)

```C
#include <xkcd.h>
#include <stdio.h>

xkcd_comic idx = xkcd_comic_latest();
if (idx) {
    xkcd_info info = xkcd_comic_info(idx);
    printf("%s", info.url);
    xkcd_comic_destroy(idx);
    idx = XKCD_COMIC_NULL;
} else {
    printf("%s", xkcd_comic_error());
}
```

- **Modern C++** &ndash; [complete interface](binary/inc/xkcdxx.h)

```C++
#include <xkcdxx.h>
#include <iostream>

try {
    xkcdxx::Comic comic{xkcdxx::Comic::Number::Latest};
    std::cout << comic.url();
} catch (xkcdxx::Comic::RequestFailed& ex) {
    std::cout << ex.what();
}
```

- **Python-3 binding** &ndash; [complete interface](python/xkcdxx/__init__.py)

```Python
import xkcdxx

try:
    comic = xkcdxx.Comic(xkcdxx.Comic.LATEST)
    print(comic.url())
except xkcdxx.Comic.RequestFailed as ex:
    print(ex)
```
