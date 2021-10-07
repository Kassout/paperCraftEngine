cmake_minimum_required(VERSION 3.9)
project(paperCraftEngine) #nom de projet et langage utilisé

set(CMAKE_CXX_STANDARD 17) #version du langage
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra") #Affiche TOUS les warnings en mode debug

set(SDL2_PATH A:/__OUTILS/__SDL2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SDL2_PATH}/cmake") #chemin pour accéder au fichier cmake
#qui vont trouver les différents fichiers nécessaire pour utiliser SDL2

set(SDL2_IMAGE_INCLUDE_DIR "${SDL2_PATH}/include") #chemin spécifiant l'endroit où se situe vos .h pour
#SDL2_Image
set(SDL2_IMAGE_LIBRARY "${SDL2_PATH}/lib/libSDL2_image.dll.a") #chemin spécifiant l'endroit où se situe vos
#bibliothèques pour SDL2_Image

set(SDL2_TTF_INCLUDE_DIR "${SDL2_PATH}/include") #chemin spécifiant l'endroit où se situe vos .h pour
#SDL2_Ttf
set(SDL2_TTF_LIBRARY "${SDL2_PATH}/lib/libSDL2_ttf.dll.a") #chemin spécifiant l'endroit où se situe vos
#bibliothèques pour SDL2_Ttf

set(SDL2_MIXER_INCLUDE_DIR "${SDL2_PATH}/include") #chemin spécifiant l'endroit où se situe vos .h pour
#SDL2_mixer
set(SDL2_MIXER_LIBRARY "${SDL2_PATH}/lib/libSDL2_mixer.dll.a") #chemin spécifiant l'endroit où se situe vos
#bibliothèques pour SDL2_mixer

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

set(INCLUDES src/Game.h)
#set(SOURCES src/Main.cpp)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        )

add_executable(paperCraftEngine ${INCLUDES} ${SRC_FILES})

include_directories(${SDL2_PATH}/INCLUDE_FILES ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR}) #inclusion des dossier nécessaire pour le
#développement avec SDL2

target_include_directories(paperCraftEngine
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs
        )

target_link_libraries(paperCraftEngine ${CMAKE_CURRENT_SOURCE_DIR}/libs/lua/liblua53.a ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY}) #inclusion des bibliothèques nécessaire pour
#le développement avec SDL2