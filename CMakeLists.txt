cmake_minimum_required(VERSION 3.0.0)
project(bomberman)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -g -g3 ")

enable_testing()

set(SRC_DIR
    ./src/
)

set(SRCS
    ${SRC_DIR}Bomb/Bomb.cpp
    ${SRC_DIR}Character/Character.cpp
    ${SRC_DIR}Character/Player.cpp
    ${SRC_DIR}Character/PlayerIA.cpp
    ${SRC_DIR}Event/EventManager.cpp
    ${SRC_DIR}Event/GameEvent.cpp
    ${SRC_DIR}Game/Game.cpp
    ${SRC_DIR}Map/Map.cpp
    ${SRC_DIR}Menu/MainMenu.cpp
    ${SRC_DIR}Menu/CharacterMenu.cpp
    ${SRC_DIR}Menu/EscMenu.cpp
    ${SRC_DIR}Menu/EndMenu.cpp
    ${SRC_DIR}Menu/HowMenu.cpp
    ${SRC_DIR}Menu/CreditMenu.cpp
    ${SRC_DIR}Menu/SettingsMenu.cpp
    ${SRC_DIR}Music/Music.cpp
    ${SRC_DIR}Window/Window.cpp
    ${SRC_DIR}Core/Core.cpp
    ${SRC_DIR}Particles/Particles.cpp
    ${SRC_DIR}Time/Time.cpp
    ${SRC_DIR}Main.cpp
)

set(H_DIR
    ./include/
)

include_directories(
    ./lib/irrklang/includes
    ./lib/irrlicht/includes
    ${H_DIR}
)


if(UNIX)

set(CMAKE_SKIP_BUILD_RPATH_FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "$ENV{HOME}/bomberman")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(IRRKLANG_LIBRARY
-L./lib/irrklang/linux
-lIrrklang
)

set(IRRLICHT_LIBRARY
-L./lib/irrlicht/linux
-lIrrlicht
-lGL
-lGLU
-lXext
-lX11
-lXxf86vm
)

link_directories(${CMAKE_SOURCE_DIR}/lib/irrklang/linux ${CMAKE_SOURCE_DIR}/lib/irrlicht/linux)

add_executable(bomberman ${SRCS} ${HEADERS})

target_link_libraries(bomberman
    ${IRRKLANG_LIBRARY}
    ${IRRLICHT_LIBRARY}
)

install(TARGETS bomberman DESTINATION "$ENV{HOME}/bomberman")
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/lib/irrklang/linux/libIrrklang.so" DESTINATION "$ENV{HOME}/bomberman")

elseif(WIN32)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(Irrklang STATIC IMPORTED)
add_library(Irrlicht STATIC IMPORTED)

set_property(TARGET Irrklang PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/irrklang/windows/libIrrklang.a)
set_property(TARGET Irrlicht PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/irrlicht/windows/Irrlicht.lib)

link_directories(${CMAKE_SOURCE_DIR}/lib/irrklang/windows ${CMAKE_SOURCE_DIR}/lib/irrlicht/windows)

add_executable(bomberman ${SRCS} ${HEADERS})

target_link_libraries(bomberman
    Irrklang
    Irrlicht
)

endif(UNIX)