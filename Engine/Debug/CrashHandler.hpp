#pragma once

namespace hx3d {

class CrashHandler {
public:
  CrashHandler();
  static void handlerFunction(int signum);
};

}
