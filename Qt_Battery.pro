QT       += core gui
QT += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
include(./QXlsx/QXlsx.pri)
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    batterychoosedialog.cpp \
    chartdialog1.cpp \
    chartdialog2.cpp \
    main.cpp \
    dialog.cpp \
    tablemodel.cpp \
    viewdialog.cpp

HEADERS += \
    batterychoosedialog.h \
    chartdialog1.h \
    chartdialog2.h \
    dialog.h \
    tablemodel.h \
    viewdialog.h

FORMS += \
    batterychoosedialog.ui \
    chartdialog1.ui \
    chartdialog2.ui \
    dialog.ui \
    viewdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
