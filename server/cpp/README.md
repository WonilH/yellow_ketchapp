# C++ gRPC Server

This directory contains a minimal gRPC server implemented in C++.
The server provides the same `Greeter` service defined in `proto/helloworld.proto` and listens on `:50051`.

## Prerequisites

- gRPC and Protocol Buffers libraries
- CMake 3.16 or newer

## Generating Code

Generate the C++ sources from the repository root:

```bash
protoc -I ./proto --cpp_out=./server/cpp --grpc_out=./server/cpp ./proto/helloworld.proto
```

## Building

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```

The resulting executable `grpc_server` can then be run to start the server.
