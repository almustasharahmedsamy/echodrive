# EchoDrive — Ahmed Samy Studio

EchoDrive is an accessible native C++ driving simulation foundation for blind and low-vision players. It combines Arabic-first voice guidance, spatial OGG audio, route distance, traffic, weather, vehicle customization, stations and an expandable regional data model.

## Version 0.6

The project supports six selectable voice/UI languages: Arabic, English, French, Spanish, Russian and Japanese. The language selector is available through `F8` or the `language` command. Windows SAPI is used for speech output; the current message catalog has full Arabic/English coverage and the language framework is ready for adding complete translated catalogs.

Vehicles can now be customized by color, engine profile and brake profile. The vehicle service model tracks petrol, diesel/gas-compatible fuel, oil and electric battery values. Stations include fuel, gas, EV charging and service-centre profiles. `F5` or `Insert` opens the station action, and `F6` customizes the current car. `F7` or `Tab` selects the next car from the 25-car catalog.

The control layer supports arrow keys, Z/E forward, X brake, C/V steering, B/I faster, N/O slower, A automatic, M manual, S/U status, D/Y map, F controls, G horn, H/CapsLock engine, J/W weather, K/T traffic, L streets, P/Escape pause, R reset and Q quit. Function keys are mapped to F1 status, F2 map, F3 weather, F4 traffic, F5 stations, F6 customization, F7 next car, F8 language, F9 controls, F10 pause, F11 reset and F12 Egypt regions. Enter reports status; Delete selects the next car.

Egyptian regional data now includes all 27 governorates with representative cities, routes and approximate coordinates for accessible route descriptions. These are lightweight in-game route profiles, not a replacement for licensed street-level map tiles. The graphical mouse front-end is reserved for the next desktop UI layer; the current console build remains fully keyboard-driven.

## Build and run

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\echodrive.exe
```

The Windows ZIP is self-contained as a folder package: run `echodrive.exe` beside `assets/audio`. Audio licenses are documented in `assets/audio/ASSET_LICENSES.md` and `assets/audio/WEATHER_LICENSES.md`.

## License

Source code is MIT licensed. Third-party and audio assets retain their own licenses; see the asset notices before redistribution.
