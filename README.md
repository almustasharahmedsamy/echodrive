# EchoDrive — Ahmed Samy Studio

Native C++ foundation for an accessible driving game for blind and low-vision players.

## Milestone 0.1

- C++20 source with portable core.
- Arabic and English command vocabulary.
- Windows SAPI speech hook when built on Windows.
- Manual and automatic driving state.
- Three prototype streets: Cairo, New York and Tokyo.
- Persistent settings.
- GitHub Actions workflow for Windows x64 build.

This is the first engineering foundation, not the finished AAA game. Future milestones add a real-time 3D renderer, vehicle physics, spatial audio, traffic AI, 15 authored streets, 25 vehicle types and a full accessible UI.

## Build on Windows

Install Visual Studio 2022 with Desktop C++ workload:

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\echodrive.exe
```

The Windows build links to Microsoft SAPI for speech output. The source repository is intended to remain private.
