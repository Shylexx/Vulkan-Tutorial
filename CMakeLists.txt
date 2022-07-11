cmake_minimum_required(VERSION 3.23)
project(VulkanTutorial VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(lib/glm)
add_subdirectory(lib/glfw)
find_package(Vulkan REQUIRED)

set(CMAKE_CXX_STANDARD 20)

set(HEADER_FILES

    # src/VulkanTutorial.h
)

set(SOURCE_FILES

    # src/LearnOpenGL.cpp
    src/main.cpp
)

add_executable(${PROJECT_NAME}
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src
    glfw
    glm
    ${VULKAN_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    glfw
    glm
    ${VULKAN_LIB_LIST}
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC GLFW_INCLUDE_NONE
)
