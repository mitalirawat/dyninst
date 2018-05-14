#set (PLATFORM i386-unknown-nt4.0)
set (PLATFORM $ENV{PLATFORM})
message(STATUS "-- Input platform: ${PLATFORM}")
set (VALID_PLATFORMS
    i386-unknown-nt4.0
    amd64-windows-6.1.7601
    amd64-windows
    X64-windows
    )

if (NOT PLATFORM)
set (INVALID_PLATFORM true)
else()
list (FIND VALID_PLATFORMS ${PLATFORM} PLATFORM_FOUND)
  if (PLATFORM_FOUND EQUAL -1)
  set (INVALID_PLATFORM true)
  endif()
endif()
message(STATUS "cmake variables are " ${CMAKE_SIZEOF_VOID_P} ${CMAKE_HOST_SYSTEM_PROCESSOR} ${CMAKE_HOST_SYSTEM_NAME} ${CMAKE_HOST_SYSTEM})

string(TOLOWER ${CMAKE_HOST_SYSTEM_PROCESSOR} host_system_processor_lc)
string(TOLOWER ${CMAKE_HOST_SYSTEM_NAME} host_system_name_lc)
set (SYSPLATFORM ${host_system_processor_lc}-${host_system_name_lc})
#format amd64-windows
set (PLATFORM ${host_system_processor_lc}-${host_system_name_lc})
#message(STATUS "platform value in platform_windows is " ${PLATFORM})

list (FIND VALID_PLATFORMS ${PLATFORM} PLATFORM_FOUND)

if (PLATFORM_FOUND EQUAL -1)
message (FATAL_ERROR "Error: unknown platform ${PLATFORM}; please set the PLATFORM environment variable to one of the following options: ${VALID_PLATFORMS}")
endif()


