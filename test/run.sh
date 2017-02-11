#!/usr/bin/env bash

if [ "$(uname)" == "Linux" ]; then
	export LD_LIBRARY_PATH=$(dirname $(readlink -f ../libft_malloc.so))/
	export LD_PRELOAD=$(readlink -f ../libft_malloc.so)
else
	export DYLD_LIBRARY_PATH=../
	export DYLD_INSERT_LIBRARIES="../libft_malloc.so"
	export DYLD_FORCE_FLAT_NAMESPACE=1 
fi

$@
