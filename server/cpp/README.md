# C++ gRPC Server

This directory contains a minimal gRPC server implemented in C++.
The server provides the same `Greeter` service defined in `proto/helloworld.proto` and listens on `:50051`.

## Prerequisites

- gRPC and Protocol Buffers libraries
  - The CMake build will automatically download gRPC **v1.56.0** if the
    `gRPC::grpc++` target is not found. This requires network access during the
    first configure.
  - You can also install gRPC manually as described below.
- CMake 3.16 or newer

### Building gRPC from Source

The following steps install gRPC **v1.56.0** along with the Protocol Buffers
compiler. Once installed, `grpc_cpp_plugin` should be available in your
`PATH`.

```bash
sudo apt-get update
sudo apt-get install -y git build-essential autoconf libtool pkg-config cmake
sudo apt-get install -y protobuf-compiler libprotobuf-dev

git clone --recurse-submodules -b v1.56.0 https://github.com/grpc/grpc.git
cd grpc
git submodule update --init --recursive

mkdir -p cmake/build
cd cmake/build
cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF ../..
make -j
sudo make install
```

You can verify the installation with:

```bash
which grpc_cpp_plugin
```

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
