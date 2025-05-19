# Yellow Ketchapp

This repository provides templates for a gRPC server written in Go and a simple GUI client written in Python.

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

Both components use the shared `proto/` directory. Run the commands below from
each subdirectory to generate the language-specific stubs:

```bash
# From server/
protoc -I ../proto --go_out=proto --go-grpc_out=proto ../proto/helloworld.proto

# From gui/
python -m grpc_tools.protoc -I ../proto --python_out=proto --grpc_python_out=proto ../proto/helloworld.proto
```
