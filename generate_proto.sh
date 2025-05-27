#!/bin/bash
set -e

# Python 코드 생성
python -m grpc_tools.protoc \
  -I=./proto \
  --python_out=./client/pyside/proto \
  --grpc_python_out=./client/pyside/proto \
  ./proto/helloworld.proto

# Go 코드 생성
protoc \
  -I=./proto \
  --go_out=./server/go \
  --go-grpc_out=./server/go \
  ./proto/helloworld.proto

# C++ 코드 생성
protoc \
  -I=./proto \
  --cpp_out=./server/cpp \
  --grpc_out=./server/cpp \
  ./proto/helloworld.proto
