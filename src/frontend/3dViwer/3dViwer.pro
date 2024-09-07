QT       += core gui openglwidgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../backend/affine_strategy/affine_transformations.cpp \
    ../../backend/affine_strategy/viwer_affine_strategy.cpp \
    ../../backend/controller/viwer_controller.cpp \
    ../../backend/model/affinne_model.cpp \
    ../../backend/model/normalization.cpp \
    ../../backend/model/viwer_model.cpp \
    ../../backend/viwer_command/viwer_command.cpp \
    ../../backend/viwer_facade/viwer_facade.cpp \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../../backend/affine_strategy/viwer_affine_strategy.h \
    ../../backend/controller/viwer_controller.h \
    ../../backend/data/data.h \
    ../../backend/model/affinne_model.h \
    ../../backend/model/normalization.h \
    ../../backend/model/viwer_model.h \
    ../../backend/viwer_command/viwer_command.h \
    ../../backend/viwer_facade/viwer_facade.h \
    ../gif_lib/gif.h \
    glwidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
