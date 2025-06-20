cmake_minimum_required(VERSION 3.16)
project(grpc_server_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG)

if(NOT gRPC_FOUND)
    message(STATUS "gRPC not found, fetching v1.56.0...")
    include(FetchContent)
    FetchContent_Declare(
        grpc
        GIT_REPOSITORY https://github.com/grpc/grpc.git
        GIT_TAG v1.56.0
    )
    FetchContent_MakeAvailable(grpc)
endif()

# Set .proto file path
set(PROTO_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../proto")
set(PROTO_FILE "${PROTO_SRC_DIR}/helloworld.proto")

# 1) Automatically generate Protobuf code (.pb.cc/.pb.h)
#    - protobuf_generate_cpp() generates standard Protobuf message code only.
#    - Output file lists are stored in PROTO_SRCS, PROTO_HDRS.
protobuf_generate_cpp(
    PROTO_SRCS     # Output: .pb.cc files
    PROTO_HDRS     # Output: .pb.h files
    ${PROTO_FILE}
)

# 2) Automatically generate gRPC code (.grpc.pb.cc/.grpc.pb.h) using a custom command
#    - To use gRPC, call protoc again with --plugin=protoc-gen-grpc option.
set(GENERATED_GRPC_SRCS "${CMAKE_CURRENT_BINARY_DIR}/helloworld.grpc.pb.cc")
set(GENERATED_GRPC_HDRS "${CMAKE_CURRENT_BINARY_DIR}/helloworld.grpc.pb.h")

add_custom_command(
    OUTPUT "${GENERATED_GRPC_SRCS}" "${GENERATED_GRPC_HDRS}"
    COMMAND ${Protobuf_PROTOC_EXECUTABLE}
    ARGS
        --grpc_out=${CMAKE_CURRENT_BINARY_DIR}
        --plugin=protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>
        -I ${PROTO_SRC_DIR}
        ${PROTO_FILE}
    DEPENDS "${PROTO_FILE}"
    COMMENT "Generating gRPC service stubs from ${PROTO_FILE}"
)

# 3) Bundle Protobuf + gRPC code into a single library
#    - Later, link this in the server (main.cpp).
add_library(helloworld_proto
    ${PROTO_SRCS}
    ${GENERATED_GRPC_SRCS}
)
target_include_directories(helloworld_proto
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(helloworld_proto
    PUBLIC
        gRPC::grpc++
        protobuf::libprotobuf
)

# 4) Create server executable
add_executable(grpc_server_cpp
    main.cpp
)

# 5) Link the library to the server target
target_link_libraries(grpc_server_cpp
    PRIVATE
        helloworld_proto
)
