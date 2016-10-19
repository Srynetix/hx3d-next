#pragma once

namespace hx3d {
namespace Debug {

class CrashHandler {
public:
  CrashHandler();
  static void handlerFunction(int signum);
};

}
}
