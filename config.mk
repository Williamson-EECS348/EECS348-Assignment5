export BUILD_DIR=$(abspath build)
export SRC_DIR=$(abspath JackWilliamson_Assignment5)

export CC=gcc
export CFLAGS=-Wall -Wextra -std=c2x -pedantic -g -I$(SRC_DIR) -O2 # -Werror
export CLIBS=