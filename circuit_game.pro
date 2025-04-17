QT       += core gui svg svgwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += $$PWD/box2d/

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
    # Box2D
    box2d/src/collision/b2_collision.cpp \
    box2d/src/collision/b2_distance.cpp \
    box2d/src/collision/b2_dynamic_tree.cpp \
    box2d/src/collision/b2_time_of_impact.cpp \
    box2d/src/common/b2_block_allocator.cpp \
    box2d/src/common/b2_draw.cpp \
    box2d/src/common/b2_math.cpp \
    box2d/src/common/b2_settings.cpp \
    box2d/src/common/b2_stack_allocator.cpp \
    box2d/src/common/b2_timer.cpp \
    box2d/src/dynamics/b2_body.cpp \
    box2d/src/dynamics/b2_chain_shape.cpp \
    box2d/src/dynamics/b2_contact_manager.cpp \
    box2d/src/dynamics/b2_fixture.cpp \
    box2d/src/dynamics/b2_island.cpp \
    box2d/src/dynamics/b2_world.cpp \
    box2d/src/dynamics/b2_world_callbacks.cpp \
    box2d/src/rope/b2_rope.cpp \
    box2d/src/particle/b2_particle.cpp \
    box2d/src/particle/b2_particle_group.cpp \
    box2d/src/particle/b2_particle_system.cpp \
    box2d/src/particle/b2_particle.cpp \
    box2d/src/joints/b2_distance_joint.cpp \
    box2d/src/joints/b2_friction_joint.cpp \
    box2d/src/joints/b2_gear_joint.cpp \
    box2d/src/joints/b2_motor_joint.cpp \
    box2d/src/joints/b2_mouse_joint.cpp \
    box2d/src/joints/b2_prismatic_joint.cpp \
    box2d/src/joints/b2_pulley_joint.cpp \
    box2d/src/joints/b2_revolute_joint.cpp \
    box2d/src/joints/b2_weld_joint.cpp \
    box2d/src/joints/b2_wheel_joint.cpp

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
