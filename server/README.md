# Go gRPC Server Template

This directory contains a minimal gRPC server written in Go.

## Prerequisites

- Go 1.21 or later
- Protocol Buffers compiler (`protoc`)
- `protoc-gen-go` and `protoc-gen-go-grpc` plugins installed
- This repository already includes a `go.mod` file, so you can skip running
  `go mod init`.

## Setup

Initialize the Go module and fetch the gRPC package (run these once):

```bash
go mod init server       # if not already done
go get google.golang.org/grpc
```

## Generating Code

Run the following command from this directory to generate Go code from the shared
`.proto` file:

```bash
protoc -I ../proto --go_out=proto --go-grpc_out=proto ../proto/helloworld.proto
```

## Running the Server

After generating the code, build and run the server:

```bash
go run .
```

The server listens on `:50051` by default and implements a simple `Greeter` service.
