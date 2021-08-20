# MIT License

# Copyright (c) 2021 Vladimir Yu. Ivanov <inbox@vova-ivanov.info>

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import ctypes


class _opaque_struct(ctypes.Structure):
    _fields_ = []


class _xkcd_info(ctypes.Structure):
    _fields_ = [
        ('number', ctypes.c_uint  ),
        ('date',   ctypes.c_uint64),
        ('url',    ctypes.c_char_p),
        ('title',  ctypes.c_char_p),
        ('alt',    ctypes.c_char_p),
    ]


_DSO = ctypes.cdll.LoadLibrary("/usr/lib/libxkcdxx.so")

_xkcd_comic = ctypes.POINTER(_opaque_struct)

_DSO.xkcd_comic_latest.argtypes  = None
_DSO.xkcd_comic_latest.restype   = _xkcd_comic
_DSO.xkcd_comic_random.argtypes  = None
_DSO.xkcd_comic_random.restype   = _xkcd_comic
_DSO.xkcd_comic_exact.argtypes   = None
_DSO.xkcd_comic_exact.restype    = _xkcd_comic
_DSO.xkcd_comic_error.argtypes   = None
_DSO.xkcd_comic_error.restype    = ctypes.c_char_p
_DSO.xkcd_comic_info.argtypes    = [_xkcd_comic]
_DSO.xkcd_comic_info.restype     = _xkcd_info
_DSO.xkcd_comic_destroy.argtypes = [_xkcd_comic]
_DSO.xkcd_comic_destroy.restype  = None

xkcd_comic_latest  = _DSO.xkcd_comic_latest
xkcd_comic_random  = _DSO.xkcd_comic_random
xkcd_comic_exact   = _DSO.xkcd_comic_exact
xkcd_comic_error   = _DSO.xkcd_comic_error
xkcd_comic_info    = _DSO.xkcd_comic_info
xkcd_comic_destroy = _DSO.xkcd_comic_destroy


class Comic():
    LATEST = 1
    RANDOM = 2

    class RequestFailed(RuntimeError):
        def __init__(self, why):
            RuntimeError.__init__(self, why)

    def __init__(self, number):
        self.__idx = Comic.__get_comic(number)
        if not self.__idx:
            why = xkcd_comic_error()
            raise Comic.RequestFailed(why)
        self.__info = xkcd_comic_info(self.__idx)

    def __del__(self):
        xkcd_comic_destroy(self.__idx)
        self.__idx = 0

    def __get_comic(number):
        if number is Comic.LATEST:
            return xkcd_comic_latest()
        elif number is Comic.RANDOM:
            return xkcd_comic_random()
        else:
            return xkcd_comic_exact(number)

    def number(self):
        return self.__info.number

    def date(self):
        return self.__info.date

    def url(self):
        return self.__info.url

    def title(self):
        return self.__info.title

    def alt(self):
        return self.__info.alt
