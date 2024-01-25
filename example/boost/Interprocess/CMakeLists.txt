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

add_executable(boost_intra_anonymous_semaphoreA comp_anonymous_semaphoreA.cpp)
target_link_libraries(boost_intra_anonymous_semaphoreA
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
install(TARGETS boost_intra_anonymous_semaphoreA
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_anonymous_semaphoreB comp_anonymous_semaphoreB.cpp)
target_link_libraries(boost_intra_anonymous_semaphoreB
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
install(TARGETS boost_intra_anonymous_semaphoreB
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_anonymous_upgradable_mutexA comp_anonymous_upgradable_mutexA.cpp)
target_link_libraries(boost_intra_anonymous_upgradable_mutexA
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
install(TARGETS boost_intra_anonymous_upgradable_mutexA
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_anonymous_upgradable_mutexB comp_anonymous_upgradable_mutexB.cpp)
target_link_libraries(boost_intra_anonymous_upgradable_mutexB
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
install(TARGETS boost_intra_anonymous_upgradable_mutexB
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_message_queueA comp_message_queueA.cpp)
target_link_libraries(boost_intra_message_queueA
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
install(TARGETS boost_intra_message_queueA
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_message_queueB comp_message_queueB.cpp)
target_link_libraries(boost_intra_message_queueB
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
install(TARGETS boost_intra_message_queueB
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_adaptive_pool doc_adaptive_pool.cpp)
target_link_libraries(boost_intra_adaptive_pool
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
install(TARGETS boost_intra_adaptive_pool
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_doc_allocator doc_allocator.cpp)
target_link_libraries(boost_intra_doc_allocator
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
install(TARGETS boost_intra_doc_allocator
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_anonymous_shared_memory doc_anonymous_shared_memory.cpp)
target_link_libraries(boost_intra_anonymous_shared_memory
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
install(TARGETS boost_intra_anonymous_shared_memory
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_doc_bufferstream doc_bufferstream.cpp)
target_link_libraries(boost_intra_doc_bufferstream
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
install(TARGETS boost_intra_doc_bufferstream
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_cached_adaptive_pool doc_cached_adaptive_pool.cpp)
target_link_libraries(boost_intra_cached_adaptive_pool
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
install(TARGETS boost_intra_cached_adaptive_pool
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_complex_map doc_complex_map.cpp)
target_link_libraries(boost_intra_complex_map
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
install(TARGETS boost_intra_complex_map
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_doc_cont doc_cont.cpp)
target_link_libraries(boost_intra_doc_cont
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
install(TARGETS boost_intra_doc_cont
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_doc_file_mapping doc_file_mapping.cpp)
target_link_libraries(boost_intra_doc_file_mapping
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
install(TARGETS boost_intra_doc_file_mapping
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_doc_instrusive doc_instrusive.cpp)
target_link_libraries(boost_intra_doc_instrusive
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
install(TARGETS boost_intra_doc_instrusive
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_doc_ipc_message doc_ipc_message.cpp)
target_link_libraries(boost_intra_doc_ipc_message
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
install(TARGETS boost_intra_doc_ipc_message
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_managed_aligned_allocation doc_managed_aligned_allocation.cpp)
target_link_libraries(boost_intra_managed_aligned_allocation
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
install(TARGETS boost_intra_managed_aligned_allocation
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_managed_allocation_command doc_managed_allocation_command.cpp)
target_link_libraries(boost_intra_managed_allocation_command
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
install(TARGETS boost_intra_managed_allocation_command
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_managed_construction_info doc_managed_construction_info.cpp)
target_link_libraries(boost_intra_managed_construction_info
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
install(TARGETS boost_intra_managed_construction_info
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_managed_copy_on_write doc_managed_copy_on_write.cpp)
target_link_libraries(boost_intra_managed_copy_on_write
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
install(TARGETS boost_intra_managed_copy_on_write
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_managed_external_buffer doc_managed_external_buffer.cpp)
target_link_libraries(boost_intra_managed_external_buffer
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
install(TARGETS boost_intra_managed_external_buffer
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_managed_grow doc_managed_grow.cpp)
target_link_libraries(boost_intra_managed_grow
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
install(TARGETS boost_intra_managed_grow
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_managed_heap_memory doc_managed_heap_memory.cpp)
target_link_libraries(boost_intra_managed_heap_memory
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
install(TARGETS boost_intra_managed_heap_memory
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})

add_executable(boost_intra_managed_mapped_file doc_managed_mapped_file.cpp)
target_link_libraries(boost_intra_managed_mapped_file
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
install(TARGETS boost_intra_managed_mapped_file
    RUNTIME
    DESTINATION examples/cpp/boost/Interprocess/${BIN_INSTALL_DIR})