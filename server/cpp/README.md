# C++ gRPC Server

This directory contains a minimal gRPC server implemented in C++.
The server provides the same `Greeter` service defined in `proto/helloworld.proto` and listens on `:50051`.

## Prerequisites

- gRPC and Protocol Buffers libraries
  - The `CMakeLists.txt` will automatically fetch **gRPC v1.56.0** if it is not
    already installed on your system. Internet access is therefore required on
    the first build. If you prefer a manual installation, see below.
- CMake 3.16 or newer

### Building gRPC from Source

If you prefer to pre-install gRPC (e.g. for offline builds), the commands below
install **v1.56.0** along with the Protocol Buffers compiler. Once installed,
`grpc_cpp_plugin` will be available in your `PATH`.

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

On the first invocation, CMake will automatically download and compile gRPC if
it is not already installed. The resulting executable `grpc_server` can then be
run to start the server.
