#include <Engine/Debug/CrashHandler.hpp>
#include <Engine/Debug/Logging.hpp>

#include <csignal>

namespace hx3d {

CrashHandler::CrashHandler() {
  // Define signals

  signal(SIGABRT, handlerFunction);
  signal(SIGSEGV, handlerFunction);
  signal(SIGILL, handlerFunction);
  signal(SIGFPE, handlerFunction);
}

void CrashHandler::handlerFunction(int signum) {
  const Logger& logger = Log.getLogger(Logging::kCore);

  const char* name = nullptr;
  switch (signum)
  {
    case SIGABRT: name = "SIGABRT";  break;
    case SIGSEGV: name = "SIGSEGV";  break;
    case SIGILL:  name = "SIGILL";   break;
    case SIGFPE:  name = "SIGFPE";   break;
  }

  if (name)
    logger.critical("Caught signal %d (%s)", signum, name);
  else
    logger.critical("Caught signal %d", signum);

  exit(signum);
}

}
