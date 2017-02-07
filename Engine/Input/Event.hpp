#pragma once

namespace hx3d {
namespace Input {

struct Event {
  enum EventDevice {
    kKeyboard = 0,
    kMouse,
    kTouch,
    kWindow
  };

  enum EventKeyboardAction {
    kKeyPressed = 0,
    kKeyReleased
  };

  enum EventKey {
    kKeyArrowUp = 0,
    kKeyArrowDown,
    kKeyArrowLeft,
    kKeyArrowRight,
    kKeySpace,

    kKeyA,
    kKeyB,
    kKeyC,
    kKeyD,
    kKeyE,
    kKeyF,
    kKeyG,
    kKeyH,
    kKeyI,
    kKeyJ,
    kKeyK,
    kKeyL,
    kKeyM,
    kKeyN,
    kKeyO,
    kKeyP,
    kKeyQ,
    kKeyR,
    kKeyS,
    kKeyT,
    kKeyU,
    kKeyV,
    kKeyW,
    kKeyX,
    kKeyY,
    kKeyZ,

    kKeyUnknown
  };

  EventDevice device;
  EventKeyboardAction keyboardAction;
  EventKey key;
};

}
}
