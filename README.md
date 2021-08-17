# xkcdxx

This library could be used to bring funny [xkcd][1] web-comics to your C and C++ applications.

Like this:

![Exploits of a Mom](https://imgs.xkcd.com/comics/exploits_of_a_mom.png "Her daughter is named Help I'm trapped in a driver's license factory.")

Do you remember? [Live][2] example. The work was inspired by existing [Python][3] package.

[1]: https://xkcd.com/
[2]: https://clck.app/
[3]: https://pypi.org/project/xkcd/

## Description

Provided both static and shared library variants. There are no specific external dependencies except stuff in standards and popular [OpenSSL][4] (>=1.1.1) library.

Implemented interfaces:

- plain C
- modern C++
- maybe fast Python-binding also will be added

Available pre-built packages:

| Distribution     | Architecture  |
|------------------|---------------|
| Debian 9.0       | amd64         |
| Debian 10.0      | amd64         |
| Ubuntu 18.04 LTS | amd64         |
| Ubuntu 20.04 LTS | amd64         |

How to install package from PPA:

```bash
$ sudo add-apt-repository --yes --update ppa:vyivanov/xkcdxx
$ sudo apt install --yes xkcdxx
```

[4]: https://www.openssl.org/
