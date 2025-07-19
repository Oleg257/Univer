QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clients.cpp \
    main.cpp \
    mainwindow.cpp \
    materials.cpp \
    orderform.cpp \
    typeorderform.cpp

HEADERS += \
    clients.h \
    mainwindow.h \
    materials.h \
    orderform.h \
    typeorderform.h

FORMS += \
    mainwindow.ui \
    orderform.ui \
    typeorderform.ui

# Подключение файла ресурсов
RESOURCES += \
    resources.qrc

# Установка правил для деплоя
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Дополнительные пути к библиотекам
LIBS += -L$$[QT_INSTALL_LIBS]

# Добавление пути к include, если нужно
INCLUDEPATH += $$PWD
