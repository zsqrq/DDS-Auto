cmake_minimum_required(VERSION 3.22)

project(BoostInterprocess VERSION 1 LANGUAGES CXX)

add_executable(boost_intra_anonymous_condA comp_anonymous_condA.cpp)
target_link_libraries(boost_intra_anonymous_condA
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
    PUBLIC boost_fiber
    PUBLIC boost_unit_test_framework
    PUBLIC glog::glog
)
install(TARGETS boost_intra_anonymous_condA
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_anonymous_condB comp_anonymous_condB.cpp)
target_link_libraries(boost_intra_anonymous_condB
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
    PUBLIC boost_fiber
    PUBLIC boost_unit_test_framework
    PUBLIC glog::glog
)
install(TARGETS boost_intra_anonymous_condB
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_anonymous_mutexA comp_doc_anonymous_mutexA.cpp)
target_link_libraries(boost_intra_anonymous_mutexA
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
    PUBLIC boost_fiber
    PUBLIC boost_unit_test_framework
    PUBLIC glog::glog
)
install(TARGETS boost_intra_anonymous_mutexA
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_anonymous_mutexB comp_doc_anonymous_mutexB.cpp)
target_link_libraries(boost_intra_anonymous_mutexB
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC fastrtps
    PUBLIC fastcdr
    PUBLIC boost_thread
    PUBLIC boost_coroutine
    PUBLIC boost_context
    PUBLIC boost_fiber
    PUBLIC boost_unit_test_framework
    PUBLIC glog::glog
)
install(TARGETS boost_intra_anonymous_mutexB
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})