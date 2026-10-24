# Native UI and six-language support

EchoDrive 0.9 adds a native C++ keyboard-first interface in `ui.hpp`/`ui.cpp`. It renders a high-contrast frame, a compact command menu, localized prompts and a localized controls screen. The design is intentionally safe for screen readers and blind players: important actions remain available as text commands and keyboard shortcuts, while the audio guide announces the same state.

The `Localization` module contains six UI packs: Arabic, English, French, Spanish, Russian and Japanese. `F8` cycles the selected language. The selected language is saved in `echodrive.cfg`, so the next launch starts in the same language. Startup, street selection, vehicle selection, menu labels, controls, weather messages, traffic alerts, pause/resume, unknown-command feedback and exit messages use the six-language announcement path.

Windows speech output now converts UTF-8 text with `MultiByteToWideChar` before calling SAPI. This is important for Arabic, Cyrillic, Japanese and accented Latin characters. The runtime still depends on the operating system having an appropriate SAPI voice installed; when a specific voice is unavailable, SAPI may fall back to its configured default voice. The text UI and language data remain available regardless.

The interface is a native accessible text UI, not a finished GPU-rendered GUI. This is deliberate for the current blind-first prototype. The `DesktopUi` abstraction provides a clean next step for a Win32, SDL or Qt graphical layer without duplicating localization or gameplay logic.

## Commands

- `F8` or `language`: cycle Arabic, English, French, Spanish, Russian and Japanese.
- `F1` or `Enter`: announce the status.
- `F9` or `controls`: show localized keyboard help.
- `profile`, `mission`, `access`, `scenario`: announce localized feature summaries.
- Arrow keys and the existing Arabic/English command aliases continue to work.
