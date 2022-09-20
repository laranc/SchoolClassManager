QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addstudentwindow.cpp \
    detailswindow.cpp \
    editdetailswindow.cpp \
    main.cpp \
    dialog.cpp \
    removestudentwindow.cpp \
    rollwindow.cpp

HEADERS += \
    addstudentwindow.hpp \
    detailswindow.hpp \
    dialog.hpp \
    editdetailswindow.hpp \
    removestudentwindow.hpp \
    rollwindow.hpp

FORMS += \
    addstudentwindow.ui \
    detailswindow.ui \
    dialog.ui \
    editdetailswindow.ui \
    removestudentwindow.ui \
    rollwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    class_roll \
    classes (copy) \
    classes \
    student_details \
    student_notes \
    student_timetable
