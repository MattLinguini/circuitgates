QT       += core gui svg svgwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/model/circuit_game_model.cpp \
    src/model/input_output.cpp \
    src/model/logic_gate.cpp \
    main.cpp \
    src/model/wire.cpp \
    src/model/level.cpp \
    src/view/circuit_game_view.cpp \
    src/view/gameobjects.cpp \
    src/view/gamescene.cpp

HEADERS += \
    src/model/circuit_game_model.h \
    src/model/game_object.h \
    src/model/input_output.h \
    src/model/logic_gate.h \
    src/model/wire.h \
    src/model/level.h \
    src/view/circuit_game_view.h \
    src/view/gameobjects.h \
    src/view/gamescene.h

FORMS += \
    circuit_game_view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
