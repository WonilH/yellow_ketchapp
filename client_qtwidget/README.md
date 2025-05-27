# Qt gRPC Client using QtProtobuf

This directory contains a minimal Qt Widgets application written in C++ that communicates with the gRPC server using Qt's gRPC and QtProtobuf modules. The example simply sends a greeting using the `Greeter` service.

## Prerequisites

- Qt 6.5 or later built with the Qt GRPC and Protobuf modules
- `protoc` with the Qt plugins (`protoc-gen-qt` and `protoc-gen-qtgrpc`)
- CMake 3.16 or newer

## Building

Generate the Qt C++ stubs and build the project using CMake:

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```

The generated executable `client_qtwidget` can then be run to connect to a running server.
