cmake_minimum_required(VERSION 3.16)
project(Nona)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Optional: Auto-include vcpkg if available
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

# Output to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Find required packages
find_package(dpp CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Find OpenSSL (required for dpp)
find_package(OpenSSL REQUIRED)

# Source files
set(SOURCES
    src/index.cpp
    src/client.cpp
    src/cogs/delete_channels.cpp
    src/cogs/create_channels.cpp
    src/events/on_ready.cpp
    src/misc/time.cpp
)

# Header files
set(HEADERS
    src/client.h
    src/cogs/delete_channels.h
    src/cogs/create_channels.h
    src/events/on_ready.h
    src/misc/colours.h
    src/misc/time.h
)

# Build the executable
add_executable(Nona ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(Nona PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Link libraries
target_link_libraries(Nona PRIVATE 
    dpp::dpp 
    yaml-cpp 
    nlohmann_json::nlohmann_json
    OpenSSL::Crypto  # Link OpenSSL Crypto library
    OpenSSL::SSL     # Link OpenSSL SSL library
)