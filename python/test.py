import xkcdxx
import time


def print_info(comic):
    print("number =", comic.number())
    print("date   =", time.ctime(comic.date()))
    print("url    =", comic.url())
    print("title  =", comic.title())
    print("alt    =", comic.alt())
    print('\n')


comic = xkcdxx.Comic(xkcdxx.Comic.LATEST)
print_info(comic)

comic = xkcdxx.Comic(xkcdxx.Comic.RANDOM)
print_info(comic)

comic = xkcdxx.Comic(100)
print_info(comic)

try:
    comic = xkcdxx.Comic(1000000000000000000)
    print_info(comic)
except xkcdxx.Comic.RequestFailed as ex:
    print(ex)
