#pragma once

#ifdef _WIN64
  #define HX3D_WIN64
  #define HX3D_WINDOWS
  #define HX3D_DESKTOP
#elif _WIN32
  #define HX3D_WIN32
  #define HX3D_WINDOWS
  #define HX3D_DESKTOP
#elif __APPLE__
  #define HX3D_APPLE
#elif __linux
  #define HX3D_LINUX
  #define HX3D_DESKTOP
#elif __ANDROID__
  #define HX3D_ANDROID
  #define HX3D_NON_DESKTOP
#endif
