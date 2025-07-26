cmake_minimum_required(VERSION 3.20)
project(cpp_gravity)

# Set path to your SFML installation
set(SFML_PATH "C:/SFML")

# Configure include directories
include_directories(${SFML_PATH}/include)

# Configure library directories
link_directories(${SFML_PATH}/lib)

# Add your executable
add_executable(${PROJECT_NAME} main.cpp)

# Link required SFML libraries
target_link_libraries(${PROJECT_NAME}
        sfml-graphics
        sfml-window
        sfml-system
)

# Automatically copy DLLs to build directory after each build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_PATH}/bin/sfml-graphics-2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_PATH}/bin/sfml-window-2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_PATH}/bin/sfml-system-2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)