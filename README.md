# Yellow Ketchapp

This repository provides templates for a gRPC server written in Go and a simple GUI client written in Python. The server now exposes an `ImageService` API so clients can list and download image files.

- `server/` contains the Go gRPC server template.
- `client_pyside/` contains the Python GUI client template built with PySide6.
- `client_qt/` contains a Qt gRPC client implemented in C++ using QtProtobuf.
- `proto/` holds the shared Protocol Buffers definitions used by both components.

Refer to the README files in each directory for details on building and running the components.
For the Python client specifically, make sure to install its requirements before
generating the gRPC stubs:

```bash
 pip install -r client_pyside/requirements.txt
```

## Generating gRPC Code

Both components share the top-level `proto/` directory. You can generate the
language-specific stubs from the repository root with the following commands:

```bash
# Go stubs for the server
protoc -I ./proto --go_out=./server --go-grpc_out=./server ./proto/imagestorage.proto

# Python stubs for the PySide client
python -m grpc_tools.protoc -I ./proto --python_out=./client_pyside --grpc_python_out=./client_pyside ./proto/imagestorage.proto

# Qt C++ stubs for the Qt client
protoc -I ./proto --qt_out=./client_qt --qt-grpc_out=./client_qt ./proto/imagestorage.proto
```

The Qt client is built using CMake. See `client_qt/README.md` for details on configuring a Qt environment and compiling the application.
