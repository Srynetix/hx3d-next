project(hx3d-ui)

set(SOURCES
  Widget.cpp
  Panel.cpp
  Button.cpp
  Label.cpp
  TextBox.cpp
  UITransform.cpp

  Layouts/Layout.cpp
  Layouts/BoxLayout.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
