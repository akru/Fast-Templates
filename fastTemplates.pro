QT += core gui xml

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

INCLUDEPATH += /usr/include/QxtCore
INCLUDEPATH += /usr/include/QxtGui

LIBS  += -lQxtGui -lQxtCore
