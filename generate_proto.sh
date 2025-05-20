#!/bin/bash
set -e

# Python 코드 생성
python -m grpc_tools.protoc \
  -I=./proto \
  --python_out=./client_pyside/proto \
  --grpc_python_out=./client_pyside/proto \
  ./proto/imagestorage.proto

# Go 코드 생성
protoc \
  -I=./proto \
  --go_out=. \
  --go-grpc_out=. \
  ./proto/imagestorage.proto
