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

add_executable(Data_transmission_to_main Data_transmission_to_main.cpp)
target_link_libraries(Data_transmission_to_main
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
)
install(TARGETS Data_transmission_to_main
RUNTIME 
DESTINATION examples/cpp/boost/croutine2/${BIN_INSTALL_DIR})

add_executable(Data_transmission_to_coroutine Data_transmission_to_coroutine.cpp)
target_link_libraries(Data_transmission_to_coroutine
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
)
install(TARGETS Data_transmission_to_coroutine
RUNTIME 
DESTINATION examples/cpp/boost/croutine2/${BIN_INSTALL_DIR})

add_executable(Coroutine_iter Coroutine_iter.cpp)
target_link_libraries(Coroutine_iter
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
)
install(TARGETS Coroutine_iter
RUNTIME 
DESTINATION examples/cpp/boost/croutine2/${BIN_INSTALL_DIR})

add_executable(Recursive_descent_parsing Recursive_descent_parsing.cpp)
target_link_libraries(Recursive_descent_parsing
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
)
install(TARGETS Recursive_descent_parsing
RUNTIME 
DESTINATION examples/cpp/boost/croutine2/${BIN_INSTALL_DIR})