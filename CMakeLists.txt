cmake_minimum_required(VERSION 3.2)

project(bulkmt VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Threads REQUIRED)

set(SOURCES src/main.cpp)
set(SOURCES_LIB_1 src/command.h)
set(SOURCES_LIB_2 src/observer.h)
set(SOURCES_LIB_3 src/metrics.h)
set(SOURCES_LIB_4 src/fibfac.h)

add_executable(bulkmt ${SOURCES} ${SOURCES_LIB_1} ${SOURCES_LIB_2} ${SOURCES_LIB_3} ${SOURCES_LIB_4})

set_target_properties(bulkmt PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    LINK_FLAGS "-fsanitize=thread"
)

target_link_libraries(bulkmt
    Threads::Threads
)

install(TARGETS bulkmt RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT jacksonrr3@yandex.ru)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)
