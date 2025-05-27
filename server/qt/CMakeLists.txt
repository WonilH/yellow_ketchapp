cmake_minimum_required(VERSION 3.16)
project(grpc_server_qt LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Grpc Protobuf)

qt_standard_project_setup()

add_executable(grpc_server_qt
    main.cpp
)

add_library(grpc_server_qt_proto STATIC)
qt_add_protobuf(grpc_server_qt_proto
    PROTO_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/../../proto/helloworld.proto
)

qt_add_grpc(grpc_server_qt_proto SERVER
    PROTO_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/../../proto/helloworld.proto
)

target_link_libraries(grpc_server_qt PRIVATE
    Qt6::Core
    Qt6::Grpc
    Qt6::Protobuf
    grpc_server_qt_proto
)
