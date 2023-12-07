cmake_minimum_required(VERSION 3.22)

project(Asio_async_client04 VERSION 1 LANGUAGES CXX)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCS_)
add_executable(Asio_async_client04 ${SRCS_})
#add_executable(Asio_AsyncServer02 AsyncServer_Main02.cpp)
target_link_libraries(Asio_async_client04
    PUBLIC ${Asio_Socket_LIBS}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC glog::glog
    )
install(TARGETS Asio_async_client04
    RUNTIME
    DESTINATION examples/cpp/boost/asio/socket/AsyncServer04/${BIN_INSTALL_DIR})