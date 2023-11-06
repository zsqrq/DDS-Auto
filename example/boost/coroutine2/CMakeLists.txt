cmake_minimum_required(VERSION 3.22)

project(DemoCroutine2 VERSION 1 LANGUAGES CXX)

add_executable(Fibo_test Fibo_test.cpp)
target_link_libraries(Fibo_test
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
)
install(TARGETS Fibo_test
RUNTIME 
DESTINATION examples/cpp/boost/croutine2/${BIN_INSTALL_DIR})