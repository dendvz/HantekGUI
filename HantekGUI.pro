QT += charts multimedia

INCLUDEPATH += include

HEADERS += \
    include/HantekDataSource.h \
    include/MainWindow.h \
    include/Helpers.h

SOURCES += \
    src/main.cpp\
    src/HantekDataSource.cpp \
    src/MainWindow.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/charts/audio
INSTALLS += target

FORMS +=
