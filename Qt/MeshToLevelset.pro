#-------------------------------------------------
#
# Project created by QtCreator 2013-01-13T11:37:55
#
#-------------------------------------------------

QT +=               core gui widgets

BASE_DIRECTORY =    ..

INCLUDE_DIRECTORY = $$BASE_DIRECTORY/include
SOURCE_DIRECTORY = $$BASE_DIRECTORY/src

TARGET =            tvm_obj2sdf

TEMPLATE =          app

OBJECTS_DIR =       ./obj/

MOC_DIR =           ./moc/

INCLUDEPATH +=      ../include \
                    ../include\LevelSet \
                    ../include\NifTI

SOURCES +=          ObjToSdf.cpp \
                    $$SOURCE_DIRECTORY/LevelSet/makelevelset3.cpp \
                    $$SOURCE_DIRECTORY/NifTI/nifti1_io.c \
                    $$SOURCE_DIRECTORY/NifTI/znzlib.c \
                    $$SOURCE_DIRECTORY/SignedDistanceFieldFactory.cpp \
                    $$SOURCE_DIRECTORY/Matrix.cpp \
                    $$SOURCE_DIRECTORY/Matrix44.cpp \
                    $$SOURCE_DIRECTORY/SignedDistanceField.cpp \
                    $$SOURCE_DIRECTORY/Volume.cpp

HEADERS +=          $$INCLUDE_DIRECTORY/LevelSet/makelevelset3.hpp \
                    $$INCLUDE_DIRECTORY/LevelSet/array1.hpp \
                    $$INCLUDE_DIRECTORY/LevelSet/array2.hpp \
                    $$INCLUDE_DIRECTORY/LevelSet/array3.hpp \
                    $$INCLUDE_DIRECTORY/LevelSet/hashtable.hpp \
                    $$INCLUDE_DIRECTORY/LevelSet/hashgrid.hpp \
                    $$INCLUDE_DIRECTORY/LevelSet/util.hpp \
                    $$INCLUDE_DIRECTORY/LevelSet/vec.hpp \
                    $$INCLUDE_DIRECTORY/SignedDistanceFieldFactory.hpp \
                    $$INCLUDE_DIRECTORY/NifTI/nifti1.h \
                    $$INCLUDE_DIRECTORY/NifTI/nifti1_io.h \
                    $$INCLUDE_DIRECTORY/NifTI/znzlib.h \
                    $$INCLUDE_DIRECTORY/Matrix.hpp \
                    $$INCLUDE_DIRECTORY/Matrix44.hpp \
                    $$INCLUDE_DIRECTORY/SignedDistanceField.hpp \
                    $$INCLUDE_DIRECTORY/CurvatureKernel.hpp \
                    $$INCLUDE_DIRECTORY/Volume.hpp

#LIBS +=             -L"lib" -llapack-linux64 \
#                    -L"lib" -lblas-linux64 \
#                    -lgfortran

linux-g++:{
    DEFINES += LINUX
    LIBS +=         -L"lib" -llapack-linux64 \
                    -L"lib" -lblas-linux64 #\
                    #-lgfortran
}

linux-g++-64:{
    DEFINES += LINUX
    LIBS +=         -L"lib" -llapack-linux64 \
                    -L"lib" -lblas-linux64 #\
                    #-lgfortran
}

win32:{
    DEFINES += WIN32
    LIBS +=         -L"lib" -llapack-win64 \
                    -L"lib" -lblas-win64 \
                    -lgfortran
}

macx:{
    DEFINES +=      DARWIN
#    LIBS +=         -L"lib" -llapack-mac64 \
#                    -L"lib" -lblas-mac64 \
#                    -lgfortran
}

