QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    TestSelectionWindow.cpp \
    account.cpp \
    createtestdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    testeditorwindow.cpp \
    testpasswindow.cpp \
    testresultswindow.cpp

HEADERS += \
    TestSelectionWindow.h \
    account.h \
    common.h \
    createtestdialog.h \
    mainwindow.h \
    menu.h \
    testeditorwindow.h \
    testpasswindow.h \
    testresultswindow.h

FORMS += \
    TestSelectionWindow.ui \
    account.ui \
    createtestdialog.ui \
    mainwindow.ui \
    menu.ui \
    testeditorwindow.ui \
    testpasswindow.ui \
    testresultswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Дополнительные пути к библиотекам
LIBS += -L$$[QT_INSTALL_LIBS]

# Добавление пути к include, если нужно
INCLUDEPATH += $$PWD

RESOURCES += \
    resources.qrc
