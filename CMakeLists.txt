cmake_minimum_required(VERSION 3.16)
project(SeaBattleSFML VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force Release build (matches the DLLs we use)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# --- MSVC UTF-8 FIX ---
if(MSVC)
    add_compile_options(/utf-8)
endif()

# --- Auto-detect SFML path (Desktop or Downloads) ---
if(EXISTS "C:/Users/User/Desktop/SFML-2.6.1/include/SFML/Graphics.hpp")
    set(SFML_ROOT "C:/Users/User/Desktop/SFML-2.6.1")
elseif(EXISTS "C:/Users/User/Downloads/SFML-2.6.1/include/SFML/Graphics.hpp")
    set(SFML_ROOT "C:/Users/User/Downloads/SFML-2.6.1")
else()
    message(FATAL_ERROR "SFML not found! Install SFML 2.6.1 to Desktop or Downloads.")
endif()

message(STATUS "SFML found at: ${SFML_ROOT}")

# Manual paths (no find_package needed)
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_LIB_DIR "${SFML_ROOT}/lib")

set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Board.cpp
    src/Cell.cpp
    src/Ship.cpp
)

set(HEADERS
    include/Game.hpp
    include/Board.hpp
    include/Cell.hpp
    include/Ship.hpp
    include/Constants.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE include ${SFML_INCLUDE_DIR})

# Link directories
target_link_directories(${PROJECT_NAME} PRIVATE ${SFML_LIB_DIR})

# Link SFML (Release .lib files)
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

# Copy assets to output directory after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)
