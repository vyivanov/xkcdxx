#!/usr/bin/env bash

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

declare -A MAP=(
    [bionic]=ubuntu18.04 [focal]=ubuntu20.04)

readonly TAG=$(git describe --tags --abbrev=0 | tr -d '\n')
readonly MSG=$(git log --pretty=format:"%s" -1)

if [ -z "${TAG}" ] || [ -z "${MSG}" ]; then
    echo 'check git tag and git msg';
    exit 1;
fi

readonly DIST=${1}
readonly ACTION=${2}

if [ -z "${DIST}" ]; then
    echo 'specify distribution';
    exit 2;
fi

readonly VER=${MAP[${DIST}]}

if [ -z "${VER}" ]; then
    echo 'check distribution';
    exit 3;
fi

DEBFULLNAME="Vladimir Yu. Ivanov" \
DEBEMAIL="inbox@vova-ivanov.info" \
    dch "${MSG}" --create --package=xkcdxx --newversion="${TAG}~${VER}" --distribution="${DIST}" \
 && if [ "${ACTION}" == 'publish' ]; then \
        debuild -S && \
        dput ppa:vyivanov/xkcdxx "../xkcdxx_${TAG}~${VER}_source.changes"; \
    else \
        debuild -uc -us; \
    fi \
 && debuild -- clean

rm -f debian/changelog
