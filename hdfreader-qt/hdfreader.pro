CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
SOURCES += \
    Hdfreader.cpp
HEADERS += \
    Hdfreader.h


#Add external static library "hdf5.lib":
DEFINES += H5_BUILT_AS_DYNAMIC_LIB
INCLUDEPATH += G:/HDF5/1.10.4/include
LIBS += -LG:/HDF5/1.10.4/lib/ -lszip -lzlib -lhdf5 -lhdf5_cpp




