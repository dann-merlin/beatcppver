#!/bin/sh
dir=$(dirname "$(readlink -f $0)")

[ "$OS" == "Windows_NT" ] && echo "This script only works for UNIX Systems" && exit 1

[ -f "$dir/build/libbeatcppver.so" ] || "$dir/build.sh"

sudo cmake --install "$dir/build"
