cmake_minimum_required(VERSION 3.16)
project(SeaBattleSFML VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- MSVC UTF-8 FIX ---
if(MSVC)
    add_compile_options(/utf-8)
endif()

# --- Auto-detect SFML path (Desktop or Downloads) ---
if(EXISTS "C:/Users/User/Desktop/SFML-2.6.1/lib/cmake/SFML")
    set(SFML_DIR "C:/Users/User/Desktop/SFML-2.6.1/lib/cmake/SFML")
elseif(EXISTS "C:/Users/User/Downloads/SFML-2.6.1/lib/cmake/SFML")
    set(SFML_DIR "C:/Users/User/Downloads/SFML-2.6.1/lib/cmake/SFML")
else()
    message(FATAL_ERROR "SFML not found! Install SFML 2.6.1 to Desktop or Downloads.")
endif()

# Only graphics + window + system -- NO audio DLL needed!
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

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

target_include_directories(${PROJECT_NAME} PRIVATE include)

# Only 3 SFML libs -- NO sfml-audio!
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
