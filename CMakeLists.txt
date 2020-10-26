cmake_minimum_required(VERSION 3.17)
project(Proyecto_OS_1 C)

set(CMAKE_C_STANDARD 99)
LINK_DIRECTORIES(allegro/lib)
INCLUDE_DIRECTORIES(allegro/include)
add_executable(Proyecto_OS_1 main.c interface/interface.c BasicStructures/process_structure.h BasicStructures/process_structure.c BasicStructures/interval_structure.c BasicStructures/interval_structure.h interface/interface.c ThreadManagement/process_admin.h ThreadManagement/process_admin.c interface/interface.h)
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

# Add other flags to the compiler
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})
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
TARGET_LINK_LIBRARIES(Proyecto_OS_1 ${GTK3_LIBRARIES})