cmake_minimum_required(VERSION 3.16)
project(client_qtwidget LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Grpc Protobuf ProtobufQtCoreTypes)

qt_standard_project_setup()

qt_add_executable(client_qtwidget
    main.cpp
)

add_library(client_qtwidget_proto STATIC)

qt_add_protobuf(client_qtwidget_proto
    PROTO_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/../proto/helloworld.proto
    PROTO_INCLUDES
        $<TARGET_PROPERTY:Qt6::ProtobufQtCoreTypes,QT_PROTO_INCLUDES>
)

qt_add_grpc(client_qtwidget_proto CLIENT
    PROTO_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/../proto/helloworld.proto
    PROTO_INCLUDES
        $<TARGET_PROPERTY:Qt6::ProtobufQtCoreTypes,QT_PROTO_INCLUDES>
)

target_link_libraries(client_qtwidget PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Grpc
    Qt6::Protobuf
    client_qtwidget_proto
)
