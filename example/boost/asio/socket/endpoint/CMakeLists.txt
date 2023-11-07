cmake_minimum_required(VERSION 3.22)

project(Asio_Socket VERSION 1 LANGUAGES CXX)

add_executable(Asio_end_point endpoint.cpp endpoint_main.cpp)
target_link_libraries(Asio_end_point
    PUBLIC ${Asio_Socket_LIBS}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC glog::glog
    )
install(TARGETS Asio_end_point
    RUNTIME
    DESTINATION examples/cpp/boost/asio/socket/${BIN_INSTALL_DIR})