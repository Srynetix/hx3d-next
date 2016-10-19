#include <Engine/Debug/StackTraceHandler.hpp>
#include <Engine/Core/PlatformDetector.hpp>
#include <Engine/Debug/Logging.hpp>

#ifdef HX3D_WINDOWS
  #include <StackWalker.h>
#endif

namespace hx3d {
namespace Debug {

StackTraceHandler::StackTraceHandler() {}

#ifdef HX3D_WINDOWS
void StackTraceHandler::report() {
  class LocalStackWalker: public StackWalker
  {
  public:
    LocalStackWalker():
      StackWalker(RetrieveVerbose),
      m_logger(HX3D_LOGGER(kCore))
      {}

    virtual void OnOutput(LPCSTR p_szText) {
      m_logger.rawLog(Logger::kError, p_szText);
      StackWalker::OnOutput(p_szText);
    }

  private:
    const Logger& m_logger;
  };

  LocalStackWalker sw;
  sw.ShowCallstack();
}

#elif HX3D_LINUX
void StackTraceHandler::report() {
  const auto& logger = Log.getLogger(Logging::kCore);
  logger.info("Stack trace for Linux.");
}

#else
void StackTraceHandler::report() {
  const auto& logger = Log.getLogger(Logging::kCore);
  logger.warn("Stack trace not implemented for this platform.");
}
#endif

}
}
