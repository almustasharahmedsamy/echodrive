# EchoDrive architecture

The repository is organized into small native C++ modules. `src/game.cpp` owns the accessible command loop and composes the subsystems. `src/voice.cpp` and `include/voice.hpp` provide the six-language voice selector and Windows SAPI bridge. `src/content.cpp` contains the 15 streets and 40 vehicle profiles. `src/traffic.cpp` contains the deterministic traffic-AI state machine. `src/weather.cpp` contains weather profiles and advisories. `src/route.cpp` tracks route progress, landmarks and distance. `src/vehicle_system.cpp` models customization, fuel, oil, battery and stations. `src/regions.cpp` contains the 27 Egyptian governorates and representative routes.

Assets are separated from source: runtime audio is under `assets/audio`, third-party code is under `third_party`, and product documentation is under `docs`. The Windows workflow stages the executable and the complete audio directory into one ZIP package.

The traffic system is now a deterministic gameplay AI foundation. It has cruising, following, yielding, lane-changing and emergency states, target-speed control, distance gaps, lane positions and automatic-driving reactions. It is not yet a production neural model, a full road-network planner or a certified autonomous-driving system. Those would require a visual world, collision geometry, perception data, scenario tests and a much larger QA cycle.

Language support is structured for six locales and Windows speech output. Arabic and English have the broadest current message coverage. A production release still needs native-reviewed translations for every gameplay message and verified Windows voice availability for French, Spanish, Russian and Japanese.
