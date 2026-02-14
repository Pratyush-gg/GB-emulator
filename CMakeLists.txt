cmake_minimum_required(VERSION 3.28)
project(gb-emulator LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

# Fetch SFML
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG master
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

# Fetch ImGui
FetchContent_Declare(ImGui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG v1.91.5
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

# Fetch ImGui-SFML
set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml
        GIT_TAG master
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(ImGui-SFML)

# Add executable and sources
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE IMGUI_HAS_VIEWPORTS=1 IMGUI_HAS_DOCKING=1)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME} PUBLIC include)

# Copy SFML and dependencies
if(WIN32)
    # Copy OpenAL DLL
#    add_custom_command(
#            TARGET ${PROJECT_NAME}
#            COMMENT "Copy OpenAL DLL"
#            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
#            ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
#            $<TARGET_FILE_DIR:${PROJECT_NAME}>
#            VERBATIM
#    )

    # Copy all SFML DLLs (including system, graphics, etc.)
    file(GLOB SFML_DLLS "${SFML_BINARY_DIR}/bin/*.dll")
    foreach(dll ${SFML_DLLS})
        add_custom_command(
                TARGET ${PROJECT_NAME}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${dll}
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
                COMMENT "Copying ${dll} to the output directory"
        )
    endforeach()

    # Copy ImGui-SFML DLLs (if any)
    file(GLOB IMGUI_DLLS "${ImGui-SFML_BINARY_DIR}/bin/*.dll")
    foreach(dll ${IMGUI_DLLS})
        add_custom_command(
                TARGET ${PROJECT_NAME}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${dll}
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
                COMMENT "Copying ImGui-SFML DLLs"
        )
    endforeach()

endif()