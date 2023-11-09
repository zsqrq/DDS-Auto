cmake_minimum_required(VERSION 3.22)

project(Asio_AsyncServer01 VERSION 1 LANGUAGES CXX)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCS_)
add_executable(Asio_AsyncServer01 ${SRCS_})
target_link_libraries(Asio_AsyncServer01
    PUBLIC ${Asio_Socket_LIBS}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC glog::glog
    )
install(TARGETS Asio_AsyncServer01
    RUNTIME
    DESTINATION examples/cpp/boost/asio/socket/${BIN_INSTALL_DIR})