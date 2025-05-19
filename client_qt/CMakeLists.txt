cmake_minimum_required(VERSION 3.16)
project(client_qt LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Grpc Protobuf)

qt_standard_project_setup()

qt_add_executable(client_qt
    main.cpp
)

qt_add_protobuf(client_qt_proto
    PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../proto/imagestorage.proto
    OUT_VAR PROTO_SRCS
)

qt6_add_grpc(client_qt_grpc
    PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../proto/imagestorage.proto
    GENERATE_CLIENT
    OUT_VAR GRPC_SRCS
)

target_sources(client_qt PRIVATE
    ${PROTO_SRCS}
    ${GRPC_SRCS}
)

target_link_libraries(client_qt PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Grpc
    Qt6::Protobuf
)
