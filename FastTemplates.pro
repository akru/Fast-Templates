QT     += core gui xml

QXT    += core gui
CONFIG += qxt

TEMPLATE = app

TARGET = fastt

SOURCES += \
    main.cpp \
    fast_templates.cpp \
    user_interface.cpp \
    copy_action.cpp

HEADERS += \
    fast_templates.h \
    user_interface.h \
    template_model.h \
    copy_action.h

RESOURCES += \
    resources.qrc
