cmake_minimum_required(VERSION 3.16)
project(client_qtquick LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Grpc Protobuf GrpcQuick ProtobufQuick ProtobufQtCoreTypes)

qt_standard_project_setup()

qt_add_executable(client_qtquick
    Main.cpp
)

qt_add_qml_module(client_qtquick
    URI ClientQtQuick
    VERSION 1.0
    QML_FILES
        Main.qml
)

add_library(client_qtquick_proto STATIC)
qt_add_protobuf(client_qtquick_proto    
    QML
    QML_URI ClientQtQuick.Proto
    PROTO_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/../proto/imagestorage.proto
    PROTO_INCLUDES
        $<TARGET_PROPERTY:Qt6::ProtobufQtCoreTypes,QT_PROTO_INCLUDES>
)

qt_add_grpc(client_qtquick_proto CLIENT
    PROTO_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/../proto/imagestorage.proto
    PROTO_INCLUDES
        $<TARGET_PROPERTY:Qt6::ProtobufQtCoreTypes,QT_PROTO_INCLUDES>
    QML
)

target_link_libraries(client_qtquick_proto PRIVATE
    Qt6::Protobuf
    Qt6::ProtobufQtCoreTypes
    Qt6::Grpc
)

target_link_libraries(client_qtquick PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::ProtobufQtCoreTypes
    client_qtquick_proto
)
