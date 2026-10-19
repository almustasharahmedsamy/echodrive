# EchoDrive — Ahmed Samy Studio

Native C++ accessible driving game foundation for blind and low-vision players.

## Milestone 0.5 — Route Map, Distance and Expanded Controls

The Windows build now includes the 15-street content catalog, 25 vehicle catalog, spatial audio, traffic simulation, weather profiles, a route map with landmarks and distance tracking, and a unified keyboard control layer. The route reports travelled metres, remaining metres, speed limit context and the next landmark. The map is available as an accessible text/audio route view while the future visual 3D map remains a later renderer milestone.

The game accepts the arrow keys directly on Windows: Up accelerates, Down brakes, and Left/Right steer. It also accepts the requested letter shortcuts: `Z/E` forward, `X` brake, `C/V` left/right, `B/I` faster, `N/O` slower, `A` automatic, `M` manual, `S/U` status, `D/Y` map, `F` controls, `G` horn, `H` engine, `J/W` weather, `K/T` traffic, `L` streets, `P` pause, `R` reset and `Q` quit. Numeric commands and text words remain available in line-input builds.

The single Windows ZIP contains `echodrive.exe` and the adjacent `assets/audio` directory. Run the executable from the extracted folder. The source repository is private and the audio licenses are documented in `assets/audio/ASSET_LICENSES.md` and `assets/audio/WEATHER_LICENSES.md`.

## Build on Windows

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\echodrive.exe
```
