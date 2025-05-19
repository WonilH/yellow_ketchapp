# Go gRPC Server Template

This directory contains a minimal gRPC server written in Go.

## Prerequisites

- Go 1.21 or later
- Protocol Buffers compiler (`protoc`)
- `protoc-gen-go` and `protoc-gen-go-grpc` plugins installed
- This repository already includes a `go.mod` file, so you can skip running
  `go mod init`.

## Generating Code

Run the following command from this directory to generate Go code from the `.proto` file:

```bash
protoc --go_out=. --go-grpc_out=. proto/helloworld.proto
```

## Running the Server

After generating the code, build and run the server:

```bash
go run .
```

The server listens on `:50051` by default and implements a simple `Greeter` service.
