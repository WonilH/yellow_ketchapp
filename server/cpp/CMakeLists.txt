cmake_minimum_required(VERSION 3.16)
project(grpc_server LANGUAGES CXX)

find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)

add_executable(grpc_server
    main.cpp
    helloworld.pb.cc
    helloworld.grpc.pb.cc
)

target_link_libraries(grpc_server
    gRPC::grpc++
    protobuf::libprotobuf
)
