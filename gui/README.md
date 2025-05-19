# GUI gRPC Client Template

This directory contains a simple GUI application written in Python using the PySide6 toolkit that communicates with the gRPC server.

## Prerequisites

- Python 3.11 or later
- `grpcio` and `grpcio-tools` packages
- `PySide6` for the GUI

## Setup

Create a Python virtual environment and install the dependencies before
generating any code so that the `grpc_tools` module is available:

```bash
python -m venv .venv
source .venv/bin/activate
```

Then install the pinned package versions listed in `requirements.txt`. Pinning
`grpcio` and `grpcio-tools` avoids conflicts with packages such as TensorFlow
that require `protobuf <5`:

```bash
pip install -r requirements.txt
```

## Generating Code

After installing the dependencies, generate the Python gRPC code from the shared
`.proto` file by running the command below from the repository root:

```bash
python -m grpc_tools.protoc -I ./proto --python_out=./gui --grpc_python_out=./gui ./proto/helloworld.proto
```

## Running the Application

With the stubs generated and dependencies installed, start the GUI client:

```bash
python app.py
```
