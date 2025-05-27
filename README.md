# Yellow Ketchapp

This repository provides templates for gRPC servers written in Go, C++, and Qt as well as a simple client written in various GUI frameworks. The servers only implement a `Greeter` service.

- `server/go/` contains the Go gRPC server template.
- `server/cpp/` contains a C++ gRPC server example.
- `server/qt/` contains a Qt based gRPC server using QtProtobuf.
  Note that as of Qt 6.9 only client code generation is officially
  supported, so the server example is for reference until full support
  lands.
- `client/pyside/` contains the Python GUI client template built with PySide6.
- `client/qtwidget/` contains a Qt gRPC client implemented in C++ using QtProtobuf.
- `client/qtquick/` contains a Qt Quick client implemented in QML using QtProtobuf.
- `proto/` holds the shared Protocol Buffers definitions used by both components.

Refer to the README files in each directory for details on building and running the components.
For the Python client specifically, make sure to install its requirements before
generating the gRPC stubs:

```bash
 pip install -r client/pyside/requirements.txt
```

## Generating gRPC Code

Both components share the top-level `proto/` directory. Only **client** code
generation is officially supported in Qt 6.9. The commands below demonstrate
how to generate the available stubs:

```bash
# Go stubs for the Go server
protoc -I ./proto --go_out=./server/go --go-grpc_out=./server/go ./proto/helloworld.proto

# Python stubs for the PySide client
python -m grpc_tools.protoc -I ./proto --python_out=./client/pyside --grpc_python_out=./client/pyside ./proto/helloworld.proto

# Qt C++ stubs for the Qt client
protoc -I ./proto --qt_out=./client/qtwidget --qt-grpc_out=./client/qtwidget ./proto/helloworld.proto
protoc -I ./proto --qt_out=./client/qtquick --qt-grpc_out=./client/qtquick ./proto/helloworld.proto

# Qt C++ stubs for the Qt server
# Server side generation is not yet officially supported in Qt 6.9.
# The following command is kept for reference when full support arrives.
protoc -I ./proto --qt_out=./server/qt --qt-grpc_out=./server/qt ./proto/helloworld.proto

# C++ stubs for the C++ server
protoc -I ./proto --cpp_out=./server/cpp --grpc_out=./server/cpp ./proto/helloworld.proto
```

The Qt client is built using CMake. See `client/qtwidget/README.md` for details on configuring a Qt environment and compiling the application.
