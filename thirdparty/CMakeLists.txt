install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/fast-dds/lib/
    DESTINATION lib
    FILES_MATCHING PATTERN "*.so*")
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cyclone-dds/lib/
    DESTINATION lib
    FILES_MATCHING PATTERN "*.so*")
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Boost/lib/
    DESTINATION lib
    FILES_MATCHING PATTERN "*.so*" PATTERN "*.a*")
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/glog/lib/
    DESTINATION lib
    FILES_MATCHING PATTERN "*.so*" PATTERN "*.a*")
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/lib/
    DESTINATION lib
    FILES_MATCHING PATTERN "*.so*" PATTERN "*.a*")
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/JsonCpp/lib/
    DESTINATION lib
    FILES_MATCHING PATTERN "*.so*" PATTERN "*.a*")