cmake_minimum_required(VERSION 3.16)
project(client_qtwidget LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets Grpc Protobuf)

qt_standard_project_setup()

qt_add_executable(client_qtwidget
    main.cpp
)

add_library(client_qtwidget_proto STATIC)

qt_add_protobuf(client_qtwidget_proto
    PROTO_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/../../proto/helloworld.proto
)

qt_add_grpc(client_qtwidget_proto CLIENT
    PROTO_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/../../proto/helloworld.proto
)

target_link_libraries(client_qtwidget PRIVATE
    Qt6::Widgets
    Qt6::Grpc
    Qt6::Protobuf
    client_qtwidget_proto
)
