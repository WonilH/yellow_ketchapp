# Yellow Ketchapp

This repository provides templates for a gRPC server written in Go and a simple GUI client written in Python. The server now exposes an `ImageService` API so clients can list and download image files.

- `server/` contains the Go gRPC server template.
- `gui/` contains the Python GUI client template.
- `proto/` holds the shared Protocol Buffers definitions used by both components.

Refer to the README files in each directory for details on building and running the components.
For the Python client specifically, make sure to install its requirements before
generating the gRPC stubs:

```bash
pip install -r gui/requirements.txt
```

## Generating gRPC Code

Both components share the top-level `proto/` directory. You can generate the
language-specific stubs from the repository root with the following commands:

```bash
# Go stubs for the server
protoc -I ./proto --go_out=./server --go-grpc_out=./server ./proto/imagestorage.proto

# Python stubs for the GUI client
python -m grpc_tools.protoc -I ./proto --python_out=./gui --grpc_python_out=./gui ./proto/imagestorage.proto
```
