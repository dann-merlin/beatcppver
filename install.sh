#!/bin/sh
dir=$(dirname "$(readlink -f $0)")

[ -f "$dir/build/libbeatcppver.so" ] || "$dir/build.sh"

cmake --install "$dir/build"
