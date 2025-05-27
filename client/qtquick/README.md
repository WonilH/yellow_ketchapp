# Qt Quick gRPC Client using QtProtobuf

This directory provides a minimal QML application built with Qt Quick. The code demonstrates how QtGrpc and QtProtobuf can be used from QML to talk to the gRPC server.

The example mirrors the widgets client and simply sends a greeting using the
`Greeter` service.

## Building

Generate the Qt stubs and build the project using CMake:

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```
