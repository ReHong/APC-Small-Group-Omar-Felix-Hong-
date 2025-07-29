QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Instructor.cpp \
    Student.cpp \
    User.cpp \
    addcourse.cpp \
    adduser.cpp \
    admin.cpp \
    main.cpp \
    mainwindow.cpp \
    removecourse.cpp \
    removeuser.cpp \
    sqlite3.c \
    studentcourse.cpp \
    swapinstr.cpp

HEADERS += \
    Instructor.h \
    Student.h \
    User.h \
    addcourse.h \
    adduser.h \
    admin.h \
    mainwindow.h \
    removecourse.h \
    removeuser.h \
    sqlite3.h \
    studentcourse.h \
    swapinstr.h

FORMS += \
    addcourse.ui \
    adduser.ui \
    admin.ui \
    mainwindow.ui \
    removecourse.ui \
    removeuser.ui \
    studentcourse.ui \
    swapinstr.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    assignment3.db
