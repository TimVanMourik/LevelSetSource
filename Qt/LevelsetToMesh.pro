#-------------------------------------------------
#
# Project created by QtCreator 2013-01-13T11:37:55
#
#-------------------------------------------------

QT +=               core

BASE_DIRECTORY =    ..

INCLUDE_DIRECTORY = $$BASE_DIRECTORY/include
SOURCE_DIRECTORY =  $$BASE_DIRECTORY/src

TARGET =            LevelsetToMesh

TEMPLATE =          app

OBJECTS_DIR =       ./obj/

MOC_DIR =           ./moc/

INCLUDEPATH +=      ../include \
                    ../include\MarchingCubes \
                    ../include\NifTI

SOURCES +=          LevelsetToMesh.cpp \
                    $$SOURCE_DIRECTORY/Volume.cpp \
                    $$SOURCE_DIRECTORY/Volume4D.cpp \
                    $$SOURCE_DIRECTORY/MarchingCubes/GLData.cpp \
                    $$SOURCE_DIRECTORY/MarchingCubes/BoundingBox.cpp \
                    $$SOURCE_DIRECTORY/MarchingCubes/HashTable.cpp \
                    $$SOURCE_DIRECTORY/MarchingCubes/MarchingCubes.cpp \
                    $$SOURCE_DIRECTORY/MarchingCubes/ObjFactory.cpp \
                    $$SOURCE_DIRECTORY/MarchingCubes/ImplicitObject.cpp \
                    $$SOURCE_DIRECTORY/MarchingCubes/Position.cpp \
                    $$SOURCE_DIRECTORY/MarchingCubes/VolumeField.cpp \
                    $$SOURCE_DIRECTORY/NifTI/nifti1_io.c \
                    $$SOURCE_DIRECTORY/NifTI/znzlib.c

HEADERS +=          $$INCLUDE_DIRECTORY/Volume.hpp \
                    $$INCLUDE_DIRECTORY/Volume4D.hpp \
                    $$INCLUDE_DIRECTORY/NifTI/nifti1.h \
                    $$INCLUDE_DIRECTORY/NifTI/nifti1_io.h \
                    $$INCLUDE_DIRECTORY/NifTI/znzlib.h \
                    $$INCLUDE_DIRECTORY/MarchingCubes/BoundingBox.hpp \
                    $$INCLUDE_DIRECTORY/MarchingCubes/GLData.hpp \
                    $$INCLUDE_DIRECTORY/MarchingCubes/HashTable.hpp \
                    $$INCLUDE_DIRECTORY/MarchingCubes/MarchingCubes.hpp \
                    $$INCLUDE_DIRECTORY/MarchingCubes/MarchingCubeTables.hpp \
                    $$INCLUDE_DIRECTORY/MarchingCubes/ObjFactory.hpp \
                    $$INCLUDE_DIRECTORY/MarchingCubes/ImplicitObject.hpp \
                    $$INCLUDE_DIRECTORY/MarchingCubes/Position.hpp \
                    $$INCLUDE_DIRECTORY/MarchingCubes/VolumeField.hpp


#LIBS +=             -L"lib" -llapack-linux64 \
#                    -L"lib" -lblas-linux64 \
#                    -lgfortran

#linux-g++:{
#    DEFINES += LINUX
#    LIBS +=         -L"lib" -llapack-linux64 \
#                    -L"lib" -lblas-linux64 #\
#                    #-lgfortran
#}

#linux-g++-64:{
#    DEFINES += LINUX
#    LIBS +=         -L"lib" -llapack-linux64 \
#                    -L"lib" -lblas-linux64 #\
#                    #-lgfortran
#}

#win32:{
#    DEFINES += WIN32
#    LIBS +=         -L"lib" -llapack-win64 \
#                    -L"lib" -lblas-win64 \
#                    -lgfortran
#}

#macx:{
#    DEFINES +=      DARWIN
##    LIBS +=         -L"lib" -llapack-mac64 \
##                    -L"lib" -lblas-mac64 \
##                    -lgfortran
#}

QMAKE_CXXFLAGS +=   -std=c++11
