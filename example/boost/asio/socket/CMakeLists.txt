set(Asio_Socket_LIBS ${Boost_LIBRARIES} boost_thread boost_coroutine boost_context CACHE INTERNAL "")

add_subdirectory(endpoint)
add_subdirectory(iooperation)
add_subdirectory(SyncClient)
add_subdirectory(SyncServer)
add_subdirectory(AsyncServer01)
add_subdirectory(AsyncServer02)
add_subdirectory(AsyncServer03)