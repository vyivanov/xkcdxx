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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <time.h>

#ifndef API_XKCD
#define API_XKCD __attribute__((visibility("default")))
#endif

typedef struct opaque{}* xkcd_comic;

API_XKCD xkcd_comic xkcd_comic_latest(void);
API_XKCD xkcd_comic xkcd_comic_random(void);
API_XKCD xkcd_comic xkcd_comic_exact(uint32_t number);

static const xkcd_comic XKCD_COMIC_NULL = (xkcd_comic) 0;

API_XKCD const char* xkcd_comic_error(void);

typedef struct {
    uint32_t    number;
    time_t      date;
    const char* url;
    const char* title;
    const char* alt;
} xkcd_info;

API_XKCD xkcd_info xkcd_comic_info(xkcd_comic idx);
API_XKCD void xkcd_comic_destroy(xkcd_comic idx);

#ifdef __cplusplus
}
#endif
