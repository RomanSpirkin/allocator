
cmake_minimum_required(VERSION 3.10)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
project(allocator)

add_executable(allocator my_allocator.hpp my_vector.hpp v1.cpp)

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR "DEB")

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH ${PATCH_VERSION})

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)