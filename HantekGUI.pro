QT += charts

INCLUDEPATH += include widgets

HEADERS += \
    include/Helpers.h \
    include/MainWindow.h \
    include/HantekDataSource.h \
    include/TimeBaseControl.h \
    include/Marker.h \
    include/ScopeView.h \
    include/ChannelControl.h \
    widgets/ConstrainedSpinBox.h \
    widgets/SpinCombo.h

SOURCES += \
    src/main.cpp\
    src/Helpers.cpp \
    src/MainWindow.cpp \
    src/HantekDataSource.cpp \
    src/TimeBaseControl.cpp \
    src/Marker.cpp \
    src/ScopeView.cpp \
    src/ChannelControl.cpp \
    widgets/ConstrainedSpinBox.cpp \
    widgets/SpinCombo.cpp

# target.path = $$[QT_INSTALL_EXAMPLES]/charts/audio
# INSTALLS += target

# FORMS +=
