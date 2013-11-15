TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Calckit/calckit.cpp \
    Main/main.cpp \
    Numeric-lib/num_core.cpp \
    Numeric-lib/num.cpp \
    Variable-lib/var_base.cpp

HEADERS += \
    Calckit/calckit.hpp \
    Main/main.hpp \
    Numeric-lib/num_core.hpp \
    Numeric-lib/num.hpp \
    Variable-lib/var_base.hpp

