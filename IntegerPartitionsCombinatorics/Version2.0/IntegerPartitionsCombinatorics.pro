TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    IntegerPartitions.cpp \
    main.cpp

HEADERS += \
    IntegerPartitions.hpp \
    PartitionTypes.hpp \
    IPsFunctions.hpp \
    BGT.hpp \
    BAT.hpp
