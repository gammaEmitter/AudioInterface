set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.13)

project(audi)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)



include(add_git_submodule.cmake)
execute_process(COMMAND bash -c "cd ${CMAKE_CURRENT_SOURCE_DIR}/extern/portaudio && sudo ./configure --enable-shared")
add_submodule(extern/portaudio)
add_subdirectory(src)
if (UNIX) 
    if (APPLE) 
        target_link_libraries(audiointerface PRIVATE
            "-framework CoreAudio"
            "-framework AudioToolbox"
            "-framework AudioUnit"
            "-framework CoreFoundation"
            "-framework CoreServices"
        )
    else ()
        add_compile_options(-lrt -lm -lasound)
        target_link_libraries(audiointerface PRIVATE rt)
        target_link_libraries(audiointerface PRIVATE m)
        target_link_libraries(audiointerface PRIVATE asound)
    endif ()
endif ()

target_include_directories(audiointerface PUBLIC extern/portaudio/include)
target_include_directories(audiointerface PUBLIC inc/aud)
target_include_directories(audiointerface PUBLIC inc/tool)
#target_include_directories(audiocomponents PUBLIC extern/portaudio/include)
#target_include_directories(audiocomponents PUBLIC inc/aud)
#target_include_directories(audiocomponents PUBLIC inc/tool)
target_include_directories(tooling PUBLIC inc/aud)
target_include_directories(tooling PUBLIC inc/tool)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_RELEASE "-ffast-math")


target_link_directories(audiointerface PUBLIC ${CMAKE_BINARY_DIR}/extern/portaudio/)

target_link_libraries(audiointerface PUBLIC portaudio)
target_link_libraries(audiointerface PUBLIC tooling)
