# EchoDrive — Ahmed Samy Studio

Native C++ accessible driving game foundation for blind and low-vision players.

## Milestone 0.4 — Traffic, Weather and Spatial Audio

- C++20 project with CMake.
- Arabic and English voice guidance through Windows SAPI.
- Spatial audio calculations with distance attenuation and left/right pan.
- Native `miniaudio` runtime for real OGG engine, road and weather loops.
- 15 street profiles and 25 vehicle profiles.
- Deterministic traffic simulation with six nearby vehicle types, distance alerts and automatic-driving reaction.
- Weather profiles: clear, rain, storm and thunder, strong wind, hot/humid, cold, snow, ice, desert, mountain and farm.
- Weather advisories report temperature, humidity, wind and slippery-road conditions in Arabic or English.
- One Windows ZIP package containing `echodrive.exe` and all runtime audio resources.

## Controls

- `1`: forward
- `2`: brake
- `3` / `4`: right / left
- `5` / `6`: faster / slower
- `a` / `m`: automatic / manual driving
- `s`: status
- `l` / `v`: list streets / vehicles
- `w`: cycle weather
- `t`: traffic report
- `r`: reset
- `q`: quit

## Build on Windows

Install Visual Studio 2022 with the Desktop C++ workload:

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\echodrive.exe
```

Run the executable from the extracted package folder so the adjacent `assets/audio` directory can be found. The source repository is private.

## Asset and scope note

The audio files are CC0 or CC0-derived assets documented in `assets/audio/ASSET_LICENSES.md` and `assets/audio/WEATHER_LICENSES.md`. The weather names describe simulation profiles; they do not claim that every sound was field-recorded in the named environment. The current traffic and weather systems are the gameplay foundation; a full visual 3D world, advanced physics and production-grade traffic AI remain later milestones.
