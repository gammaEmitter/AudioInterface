set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.13)

project(audi)

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
    endif ()
endif ()

target_include_directories(audiointerface PUBLIC extern/portaudio/include)
target_include_directories(audiointerface PUBLIC inc/aud)



target_link_directories(audiointerface PUBLIC ${CMAKE_BINARY_DIR}/extern/portaudio/)

target_link_libraries(audiointerface PUBLIC portaudio)
