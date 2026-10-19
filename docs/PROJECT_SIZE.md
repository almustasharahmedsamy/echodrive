# Current project size

Measured in the Sandbox workspace on 2026-10-19 after the 0.7 source additions: approximately 185 files, 335 lines across the C++ headers and source files as counted by the project audit, and 9.3 MB of audio assets. These numbers are repository size indicators, not a production-game estimate. The Windows package is larger because it includes the executable and runtime audio directory.

After the 0.7 additions, rerun the repository audit command from the project root to obtain the exact current values:

```bash
find . -path './.git' -prune -o -type f -print | wc -l
find include src -type f \( -name '*.cpp' -o -name '*.hpp' \) -print0 | xargs -0 cat | wc -l
du -sh assets/audio
```
