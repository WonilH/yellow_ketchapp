#!/bin/bash
set -e

# Python 코드 생성
python -m grpc_tools.protoc \
  -I=./proto \
  --python_out=./gui/proto \
  --grpc_python_out=./gui/proto \
  ./proto/helloworld.proto

# Go 코드 생성
protoc \
  -I=./proto \
  --go_out=. \
  --go-grpc_out=. \
  ./proto/helloworld.proto
