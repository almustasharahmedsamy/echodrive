# EchoDrive — Ahmed Samy Studio

Native C++ accessible driving game foundation for blind and low-vision players.

## Milestone 0.2 — Spatial Audio + Content Catalog

- Spatial audio core with listener position, heading, distance attenuation and left/right pan.
- 15 complete authored street profiles inspired by Egypt, the US, Britain, Russia, China, Japan, India, France, Spain, Italy, Germany, the UAE, Saudi Arabia, Canada and Australia.
- 25 vehicle profiles with categories, top speed and engine tone metadata.
- Arabic and English content labels.
- Windows SAPI speech hook.
- Manual/automatic driving state and persistent settings.
- Windows x64 GitHub Actions build.

The spatial audio module currently provides the deterministic 3D positioning/mix layer; the next audio milestone connects it to streamed engine, traffic and ambience samples through a native audio backend.

## Build on Windows

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\echodrive.exe
```

The source repository is private. This milestone is an engineering build, not the final AAA visual game.
