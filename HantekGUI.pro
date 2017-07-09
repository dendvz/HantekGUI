QT += charts multimedia

INCLUDEPATH += include

HEADERS += \
    include/Helpers.h \
    include/MainWindow.h \
    include/HantekDataSource.h \
    include/TimeBaseControl.h

SOURCES += \
    src/main.cpp\
    src/MainWindow.cpp \
    src/HantekDataSource.cpp \
    src/TimeBaseControl.cpp

# target.path = $$[QT_INSTALL_EXAMPLES]/charts/audio
# INSTALLS += target

FORMS +=
