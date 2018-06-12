HEADERS += \
    automatamanager.h \
    state.h \
    automaton.h \
    utilities/sqlite3.h \
    utilities/rulebst.h \
    maincontroller.h \
    matrixcontroller.h \
    rulescontroller.h \
    qttools.h

SOURCES += \
    main.cpp \
    automaton.cpp \
    state.cpp \
    automatamanager.cpp \
    utilities/rulebst.cpp \
    utilities/sqlite3.c \
    maincontroller.cpp \
    matrixcontroller.cpp \
    rulescontroller.cpp

QT += widgets

RESOURCES += \
    application.qrc
