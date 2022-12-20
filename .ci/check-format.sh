#!/bin/bash

SOURCES=$(find $(git rev-parse --show-toplevel) | egrep "\.(cpp|hpp)\$")

CLANG_FORMAT=$(which clang-format)
if [ $? -ne 0 ]; then
    echo "[!] clang-format not installed. Unable to check source file format policy." >&2
    exit 1
fi

set -x

for file in ${SOURCES}; do
    $CLANG_FORMAT ${file} >expected-format
    diff -u -p --label="${file}" --label="expected coding style" ${file} expected-format
done
exit $($CLANG_FORMAT --output-replacements-xml ${SOURCES} | egrep -c "</replacement>")
