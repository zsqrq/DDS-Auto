cmake_minimum_required(VERSION 3.22)

project(Asio_Socket VERSION 1 LANGUAGES CXX)

add_executable(Asio_io_operation connection.cpp)
target_link_libraries(Asio_io_operation
    PUBLIC ${Asio_Socket_LIBS}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC glog::glog
    )
install(TARGETS Asio_io_operation
    RUNTIME
    DESTINATION examples/cpp/boost/asio/socket/${BIN_INSTALL_DIR})