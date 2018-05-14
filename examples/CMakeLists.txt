#add_executable(unstrip)
#add_executable(cfg_to_dot ../parseAPI/doc/example.cc)
#add_dependencies(cfg_to_dot parseAPI symtabAPI)
#target_link_libraries(cfg_to_dot parseAPI symtabAPI
#        )

#install (TARGETS cfg_to_dot
#        RUNTIME DESTINATION ${INSTALL_BIN_DIR}
#        LIBRARY DESTINATION ${INSTALL_LIB_DIR}
#        ARCHIVE DESTINATION ${INSTALL_LIB_DIR}
#        PUBLIC_HEADER DESTINATION ${INSTALL_INCLUDE_DIR})


include_directories (
  ${PROJECT_SOURCE_DIR}/dyninstAPI/h
  )


add_executable(retee retee.cpp)
add_executable(testll testloadlibrary.cpp)
#add_executable(retee)
add_dependencies(retee dyninstAPI)
target_link_libraries(retee dyninstAPI)
#target_link_libraries(retee testdll2)
