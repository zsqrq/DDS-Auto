macro(generate_protos src_dir)

  if(NOT PROTOBUF_PROTOC_EXECUTABLE)
    message(WARNING "Protobuf compiler is not found.")
    set(PROTOBUF_PROTOC_EXECUTABLE "${CMAKE_SOURCE_DIR}/thirdparty/protobuf/bin/protoc")
  endif()

  file(GLOB PROTO_FILES "${src_dir}/*.proto")
  message(WARNING "Protobuf files is ${PROTO_FILES}")
  add_custom_target(proto_messages ALL)
  foreach(PROTO_FILE ${PROTO_FILES})
    get_filename_component(PROTO_NAME ${PROTO_FILE} NAME_WE)

    set(GENERATED_PROTO_SRC ${CMAKE_CURRENT_SOURCE_DIR}/${PROTO_NAME}.pb.cc)
    set(GENERATED_PROTO_HDR ${CMAKE_CURRENT_SOURCE_DIR}/${PROTO_NAME}.pb.h)

    add_custom_command(TARGET proto_messages PRE_BUILD
        COMMAND protoc --cpp_out "${src_dir}" --proto_path "${src_dir}"  "${PROTO_FILE}"
        COMMENT "Generating ${GENERATED_PROTO_SRC} and ${GENERATED_PROTO_HDR}"
        )

    list(APPEND GENERATED_SRCS "${GENERATED_PROTO_SRC}")
    list(APPEND GENERATED_HDRS "${GENERATED_PROTO_HDR}")
  endforeach()

  set(GENERATED_SRCS ${GENERATED_SRCS} PARENT_SCOPE)
  set(GENERATED_HDRS ${GENERATED_HDRS} PARENT_SCOPE)
endmacro()