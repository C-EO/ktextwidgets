add_library(KF6TextWidgets)
add_library(KF6::TextWidgets ALIAS KF6TextWidgets)

set_target_properties(KF6TextWidgets PROPERTIES
    VERSION     ${KTEXTWIDGETS_VERSION}
    SOVERSION   ${KTEXTWIDGETS_SOVERSION}
    EXPORT_NAME TextWidgets
)

target_sources(KF6TextWidgets PRIVATE
    dialogs/klinkdialog.cpp
    dialogs/klinkdialog_p.h
    findreplace/kfind.cpp
    findreplace/kfinddialog.cpp
    findreplace/kfinddialog.h
    findreplace/kfinddialog_p.h
    findreplace/kfind.h
    findreplace/kfind_p.h
    findreplace/kreplace.cpp
    findreplace/kreplacedialog.cpp
    findreplace/kreplacedialog.h
    findreplace/kreplace.h
    widgets/kpluralhandlingspinbox.cpp
    widgets/kpluralhandlingspinbox.h
    widgets/krichtextedit.cpp
    widgets/krichtextedit.h
    widgets/krichtextedit_p.h
    widgets/krichtextwidget.cpp
    widgets/krichtextwidget.h
    widgets/ktextedit.cpp
    widgets/ktextedit.h
    widgets/ktextedit_p.h
    widgets/nestedlisthelper.cpp
    widgets/nestedlisthelper_p.h

)

ecm_generate_export_header(KF6TextWidgets
    BASE_NAME KTextWidgets
    GROUP_BASE_NAME KF
    VERSION ${KF_VERSION}
    USE_VERSION_HEADER
    DEPRECATED_BASE_VERSION 0
    DEPRECATION_VERSIONS 6.6
    EXCLUDE_DEPRECATED_BEFORE_AND_AT ${EXCLUDE_DEPRECATED_BEFORE_AND_AT}
)

set(ktextwidgets_INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/dialogs
  ${CMAKE_CURRENT_SOURCE_DIR}/findreplace
  ${CMAKE_CURRENT_SOURCE_DIR}/widgets
)
target_include_directories(KF6TextWidgets PUBLIC "$<BUILD_INTERFACE:${ktextwidgets_INCLUDES}>"
)

target_include_directories(KF6TextWidgets INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/KTextWidgets>")

target_link_libraries(KF6TextWidgets
PUBLIC
  Qt6::Widgets
  KF6::SonnetUi
  KF6::I18n
PRIVATE
  KF6::SonnetCore
  KF6::WidgetsAddons
  KF6::Completion
  KF6::ConfigGui
)

if (Qt6TextToSpeech_FOUND)
    target_link_libraries(KF6TextWidgets
      PRIVATE
        Qt6::TextToSpeech)
endif()

ecm_generate_headers(KTextWidgets_HEADERS
  HEADER_NAMES
  KRichTextEdit
  KRichTextWidget
  KTextEdit
  KPluralHandlingSpinBox

  RELATIVE widgets
  REQUIRED_HEADERS KTextWidgets_HEADERS
)
ecm_generate_headers(KTextWidgets_HEADERS
  HEADER_NAMES
  KFind
  KFindDialog
  KReplace
  KReplaceDialog

  RELATIVE findreplace
  REQUIRED_HEADERS KTextWidgets_HEADERS
)

install(TARGETS KF6TextWidgets EXPORT KF6TextWidgetsTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/ktextwidgets_export.h
  ${KTextWidgets_HEADERS}
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/KTextWidgets COMPONENT Devel
)

if (BUILD_DESIGNERPLUGIN)
    add_subdirectory(designer)
endif()

ecm_generate_qdoc(KF6TextWidgets ktextwidgets.qdocconf)
