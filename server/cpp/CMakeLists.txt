cmake_minimum_required(VERSION 3.16)
project(grpc_server_cpp LANGUAGES CXX)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GRPC REQUIRED grpc++)
pkg_check_modules(PROTOBUF REQUIRED protobuf)

include_directories(${GRPC_INCLUDE_DIRS} ${PROTOBUF_INCLUDE_DIRS})
link_directories(${GRPC_LIBRARY_DIRS} ${PROTOBUF_LIBRARY_DIRS})

add_executable(grpc_server_cpp
    main.cpp
    helloworld.pb.cc
    helloworld.grpc.pb.cc
)

target_link_libraries(grpc_server_cpp
    ${GRPC_LIBRARIES}
    ${PROTOBUF_LIBRARIES}
)
