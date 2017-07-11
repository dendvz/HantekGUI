QT += charts

INCLUDEPATH += include

HEADERS += \
    include/Helpers.h \
    include/MainWindow.h \
    include/HantekDataSource.h \
    include/TimeBaseControl.h \
    include/Marker.h \
    include/ScopeView.h \
    include/ChannelControl.h \
    include/ChannelScaleSpinBox.h

SOURCES += \
    src/main.cpp\
    src/MainWindow.cpp \
    src/HantekDataSource.cpp \
    src/TimeBaseControl.cpp \
    src/Marker.cpp \
    src/ScopeView.cpp \
    src/ChannelControl.cpp \
    src/ChannelScaleSpinBox.cpp

# target.path = $$[QT_INSTALL_EXAMPLES]/charts/audio
# INSTALLS += target

# FORMS +=
