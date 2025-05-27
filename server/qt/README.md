# Qt gRPC Server using QtProtobuf

This directory contains a minimal gRPC server implemented with Qt. The
implementation uses Qt's QtGrpc and QtProtobuf modules and exposes the
same `Greeter` service defined in `proto/helloworld.proto`.

## Prerequisites

- Qt 6.5 or later built with the QtGrpc and QtProtobuf modules
- `protoc` with the Qt plugins (`protoc-gen-qt` and `protoc-gen-qtgrpc`)
- CMake 3.16 or newer

## Generating Code

Generate the Qt sources from the repository root:

```bash
protoc -I ./proto --qt_out=./server/qt --qt-grpc_out=./server/qt ./proto/helloworld.proto
```

## Building

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```

Running the resulting `grpc_server_qt` executable will start the server on
`:50051`.
