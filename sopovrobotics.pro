TEMPLATE = app
TARGET = sopovrobotics

QT += core network websockets script
QT -= gui

CONFIG   += console
CONFIG   -= app_bundle
OBJECTS_DIR = tmp/
MOC_DIR = tmp/
RCC_DIR = tmp/
CONFIG += c++11 c++14

INCLUDEPATH += src/interfaces

SOURCES += \
	src/main.cpp \
	src/settings.cpp \
	src/controlserver.cpp \
	src/cmd_handlers/cmd_forward_handler.cpp \
	src/cmd_handlers/cmd_backward_handler.cpp \
	src/cmd_handlers/cmd_turnleft_handler.cpp \
	src/cmd_handlers/cmd_turnright_handler.cpp \
	src/cmd_handlers/cmd_stop_handler.cpp \
	src/cmd_handlers/cmd_comb_up_handler.cpp \
	src/cmd_handlers/cmd_comb_down_handler.cpp \
	src/cmd_handlers/cmd_settings_handler.cpp \
	src/cmd_handlers/cmd_update_settings_handler.cpp \
	src/cmd_handlers/create_cmd_handlers.cpp \

HEADERS += \
	src/interfaces/isettings.h \
	src/interfaces/icontrolserver.h \
	src/interfaces/icmdhandler.h \
	src/settings.h \
	src/controlserver.h \
	src/cmd_handlers/create_cmd_handlers.h \
	src/cmd_handlers/cmd_forward_handler.h \
	src/cmd_handlers/cmd_backward_handler.h \
	src/cmd_handlers/cmd_turnleft_handler.h \
	src/cmd_handlers/cmd_turnright_handler.h \
	src/cmd_handlers/cmd_stop_handler.h \
	src/cmd_handlers/cmd_comb_up_handler.h \
	src/cmd_handlers/cmd_comb_down_handler.h \
	src/cmd_handlers/cmd_settings_handler.h \
	src/cmd_handlers/cmd_update_settings_handler.h \
