#!/bin/bash
set -e

# Generate Python code
python -m grpc_tools.protoc \
  -I=./proto \
  --python_out=./client/pyside/proto \
  --grpc_python_out=./client/pyside/proto \
  ./proto/helloworld.proto

# Generate Go code
protoc \
  -I=./proto \
  --go_out=./server/go \
  --go-grpc_out=./server/go \
  ./proto/helloworld.proto

# Generate C++ code
# This is handled by CMake.