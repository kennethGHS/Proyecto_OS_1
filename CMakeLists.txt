cmake_minimum_required(VERSION 3.17)
project(Proyecto_OS_1 C)

set(CMAKE_C_STANDARD 99)
LINK_DIRECTORIES(allegro/lib)
INCLUDE_DIRECTORIES(allegro/include)
add_executable(Proyecto_OS_1 main.c BasicStructures/process_structure.h BasicStructures/process_structure.c BasicStructures/interval_structure.c BasicStructures/interval_structure.h interface/interface.c)

TARGET_LINK_LIBRARIES(Proyecto_OS_1  allegro_acodec
        allegro_audio
        allegro_color
        allegro_dialog
        allegro_image
        allegro_main
        allegro_memfile
        allegro_physfs
        allegro_primitives
        allegro_ttf
        allegro_font
        allegro)
file(GLOB LIBRARIES "allegro/lib/*.dll.a")
message("LIBRARIES = ${LIBRARIES}")
TARGET_LINK_LIBRARIES(Proyecto_OS_1  ${LIBRARIES})