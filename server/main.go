package main

import (
	"context"
	"log"
	"net"
	"os"
	"path/filepath"

	pb "server/proto"

	"google.golang.org/grpc"
)

type greeterServer struct {
	pb.UnimplementedGreeterServer
}

type imageServer struct {
	pb.UnimplementedImageServiceServer
	imageDir string
}

func (s *imageServer) ListImages(ctx context.Context, req *pb.ImageListRequest) (*pb.ImageListReply, error) {
	entries, err := os.ReadDir(s.imageDir)
	if err != nil {
		return nil, err
	}
	filenames := make([]string, 0, len(entries))
	for _, e := range entries {
		if !e.IsDir() {
			filenames = append(filenames, e.Name())
		}
	}
	return &pb.ImageListReply{Filenames: filenames}, nil
}

func (s *imageServer) GetImage(ctx context.Context, req *pb.ImageRequest) (*pb.ImageData, error) {
	path := filepath.Join(s.imageDir, req.GetFilename())
	data, err := os.ReadFile(path)
	if err != nil {
		return nil, err
	}
	return &pb.ImageData{Data: data}, nil
}

func (s *greeterServer) SayHello(ctx context.Context, req *pb.HelloRequest) (*pb.HelloReply, error) {
	return &pb.HelloReply{Message: "Hello " + req.Name}, nil
}

func main() {
	lis, err := net.Listen("tcp", ":50051")
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}
	grpcServer := grpc.NewServer()
	pb.RegisterGreeterServer(grpcServer, &greeterServer{})
	pb.RegisterImageServiceServer(grpcServer, &imageServer{imageDir: "./images"})
	log.Println("gRPC server listening on :50051")
	if err := grpcServer.Serve(lis); err != nil {
		log.Fatalf("failed to serve: %v", err)
	}
}
