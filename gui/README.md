# GUI gRPC Client Template

This directory contains a simple GUI application written in Python that communicates with the gRPC server.

## Prerequisites

- Python 3.11 or later
- `grpcio` and `grpcio-tools` packages

## Generating Code

Generate the Python gRPC code from the shared `.proto` file:

```bash
python -m grpc_tools.protoc -I proto --python_out=. --grpc_python_out=. proto/helloworld.proto
```

## Running the Application

After generating the code, install the required packages and run the client:

```bash
pip install -r requirements.txt
python app.py
```
