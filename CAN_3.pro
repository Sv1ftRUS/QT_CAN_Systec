QT += core gui
QT += serialport
QT += serialbus widgets #без этого КАН хидеры не подключаются
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    can_adapter.cpp \
    main.cpp \
    main_window.cpp \
    settings_window.cpp \
    systec_can.cpp \
    vul_can.cpp

HEADERS += \
    can_adapter.h \
    main_window.h \
    settings_window.h \
    systec_can.h \
    vul_can.h

FORMS += \
    main_window.ui \
    settings_window.ui

#win32:RC_FILE = file.rc #иконка приложенияwin32:RC_FILE = file.rc #иконка приложения

#LIBS +=-L"C:\Program Files (x86)\SYSTEC-electronic\USB-CANmodul Utility Disk\Examples\lib" -lUSBCAN32#подключаем библиотеку DLL
LIBS +=-L"C:\Program Files (x86)\SYSTEC-electronic\USB-CANmodul Utility Disk\lib.418" -lUSBCAN32#подключаем библиотеку DLL

#

#INCLUDEPATH += C:\Program Files (x86)\SYSTEC-electronic\USB-CANmodul Utility Disk\Examples\Include

#LIBS *="C:\Program Files (x86)\SYSTEC-electronic\USB-CANmodul Utility Disk\Examples\lib\USBCAN32.dll"# -lUSBCAN64#подключаем библиотеку DLL
#INCLUDEPATH *= "C:\Program Files (x86)\SYSTEC-electronic\USB-CANmodul Utility Disk\Examples\Include"#\Usbcan32.h"

#LIBS +="C:\Program Files (x86)\SYSTEC-electronic\USB-CANmodul Utility Disk\Examples\lib"# -lUSBCAN64#подключаем библиотеку DLL

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#это либа подключилась через диалоговое окно
#win32:CONFIG(release, debug|release): LIBS += -L'D:/Work/Systec/' -lUSBCAN32
#else:win32:CONFIG(debug, debug|release): LIBS += -L'D:/Work/Systec/' -lUSBCAN32
#else:unix: LIBS += -L'D:/Work/Полезная инфа/Systec/' -lUSBCAN32

#INCLUDEPATH += 'D:/Work/Systec'
#DEPENDPATH += 'D:/Work/Systec'


QT += axcontainer
#Qt += activeqt
#CONFIG += axcontainer
#QT       += core gui widgets axcontainer
QT += xml
