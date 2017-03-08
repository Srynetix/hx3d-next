#include <Engine/Input/InputSystem.hpp>

#include <algorithm>
#include <SDL.h>

#define REG_KEY(sdl_key, hx_key) case sdl_key: key = Event::##hx_key; break;

namespace hx3d {
namespace Input {

InputSystem::InputSystem() {
}

void InputSystem::registerHandler(InputHandler* p_handler) {
  p_handler->p_system = this;
  m_handlers.push_back(p_handler);
}

void InputSystem::removeHandler(InputHandler* p_handler) {
  auto res = std::find(m_handlers.begin(), m_handlers.end(), p_handler);
  if (res == m_handlers.end())
    return;

  p_handler->p_system = nullptr;
  m_handlers.erase(res);
}

bool InputSystem::poll() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    Event nevent;

    if (event.type == SDL_QUIT) {
      return false;
    }

    else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
      Event::EventKey key = Event::kKeyUnknown;
      nevent.device = Event::kKeyboard;

      switch (event.key.keysym.sym) {
        // Arrows
        REG_KEY(SDLK_LEFT,    kKeyArrowLeft);
        REG_KEY(SDLK_RIGHT,   kKeyArrowRight);
        REG_KEY(SDLK_UP,      kKeyArrowUp);
        REG_KEY(SDLK_DOWN,    kKeyArrowDown);
        REG_KEY(SDLK_SPACE,   kKeySpace);

        // Letters
        REG_KEY(SDLK_a,   kKeyA);
        REG_KEY(SDLK_b,   kKeyB);
        REG_KEY(SDLK_c,   kKeyC);
        REG_KEY(SDLK_d,   kKeyD);
        REG_KEY(SDLK_e,   kKeyE);
        REG_KEY(SDLK_f,   kKeyF);
        REG_KEY(SDLK_g,   kKeyG);
        REG_KEY(SDLK_h,   kKeyH);
        REG_KEY(SDLK_i,   kKeyI);
        REG_KEY(SDLK_j,   kKeyJ);
        REG_KEY(SDLK_k,   kKeyK);
        REG_KEY(SDLK_l,   kKeyL);
        REG_KEY(SDLK_m,   kKeyM);
        REG_KEY(SDLK_n,   kKeyN);
        REG_KEY(SDLK_o,   kKeyO);
        REG_KEY(SDLK_p,   kKeyP);
        REG_KEY(SDLK_q,   kKeyQ);
        REG_KEY(SDLK_r,   kKeyR);
        REG_KEY(SDLK_s,   kKeyS);
        REG_KEY(SDLK_t,   kKeyT);
        REG_KEY(SDLK_u,   kKeyU);
        REG_KEY(SDLK_v,   kKeyV);
        REG_KEY(SDLK_w,   kKeyW);
        REG_KEY(SDLK_x,   kKeyX);
        REG_KEY(SDLK_y,   kKeyY);
        REG_KEY(SDLK_z,   kKeyZ);

        default:
          nevent.key = Event::kKeyUnknown;
      }

      nevent.key = key;

      if (event.type == SDL_KEYDOWN) {
        nevent.keyboardAction = Event::kKeyPressed;
        m_keysState[nevent.key] = true;
        for (auto& h: m_handlers)
          h->onKeyPress(nevent);

      } else if (event.type == SDL_KEYUP) {
        nevent.keyboardAction = Event::kKeyReleased;
        m_keysState[nevent.key] = false;
        for (auto& h: m_handlers)
          h->onKeyRelease(nevent);
      }
    }
  }

  return true;
}

}
}

#undef REG_KEY
