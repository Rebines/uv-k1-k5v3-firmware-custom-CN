# AGENTS.md

## Project
- Bare-metal firmware for Quansheng UV-K1 / UV-K5 V3 (PY32F071, Cortex-M0+). This fork is the Chinese-localized F4HWN firmware; UV-K5 V1 (DP32G030) is a different MCU and is not supported.
- Linker limits: 118 KB flash from `0x08002800` (bootloader reserved) and 16 KB RAM (`Core/py32f071xb.ld`). The localized Fusion build uses ~111 KB flash / 12.2 KB RAM; check the linker report before adding features.

## Build and verification
- Compilation is normally done by the GitHub Actions workflow `Build Firmware` (`.github/workflows/main.yml`), not in the local workspace.
- The workflow triggers on push/PR to `main`, runs `./compile-firmware.sh Fusion`, and uploads artifact `f4hwn-fusion-cn-firmware` containing `f4hwn.fusion.bin` and `f4hwn.fusion.hex`.
- Download a run's artifact from the Actions page or with `gh run download <run-id> -n f4hwn-fusion-cn-firmware`.
- There are no unit tests or test target; a successful firmware build is the verification.
- Local reproduction: `./compile-firmware.sh Fusion` (Docker + Bash, ARM GCC 13.3.rel1; first run builds image `uvk1-uvk5v3`). The old `compile-with-docker.sh` only forwards to the new script.
- Presets: `Custom`, `Fusion`, `Transfer`, `FieldOps`, `Labs`, `Max`, `Fusion_`, `Service_`, `All`. `Fusion` is the default and the release build; `All` builds Fusion, Transfer, FieldOps, Labs and Max.
- Outputs are `build/<Preset>/<TARGET>.{elf,bin,hex,map}`. Fusion produces `build/Fusion/f4hwn.fusion.bin` and `.hex`.
- Direct CMake works only with `arm-none-eabi-gcc` on `PATH` (`cmake/gcc-arm-none-eabi.cmake`); GitHub Actions is the authoritative build.
- `compile-app.sh` builds the overlay apps under `App/apps/` for Labs; it is not needed for the Fusion release.

## Code layout
- Reset entry `Core/Src/main.c` calls `Main()` in `App/main.c`, which initializes hardware/settings and runs the `APP_Update` / `APP_TimeSlice10ms` / `APP_TimeSlice500ms` loop. `App/app/main.c` is the main-VFO screen, not the entry point.
- `App/app/` holds behavior/state; `App/ui/` holds rendering/strings. Menu IDs are in `App/ui/menu.h`, menu names/submenu strings/category view in `App/ui/menu.c`, key handling/value application in `App/app/menu.c`.
- Simple persistent byte settings are declared in `App/app/menu_settings.def` (included by `App/app/menu.c`); add new ones there and in the matching load/save code.
- `App/CMakeLists.txt` is the complete build source list; a new `.c` file does nothing until added there, normally via `enable_feature(FLAG ...)`. Preset defaults are in `CMakePresets.json`.
- `App/driver/bk4829.c` (sic) is the live BK4819 driver. `App/driver/bk4819.c`, `adc.c`, `aes.c`, `eeprom.c`, `flash.c`, and `spi.c` are unbuilt DP32-era leftovers; editing them has no effect. Live storage paths are `py25q16.c`, `eeprom_compat.c`, and `mb_flash.c` (Multiboot).
- `App/apps/` contains overlay applications used by Labs; do not wire them into the Fusion build by accident.

## Chinese UI / font
- The LCD renderer maps single bytes `0x80..0xFF` to Chinese glyphs; it does not decode UTF-8. UI strings must use `CN_C<codepoint>` macros (e.g. `CN_C4E2D` = 中). Raw Chinese in a string literal renders as garbage.
- **Hard cap: 128 glyphs.** The single-byte encoding uses the full `0x80..0xFF` range, so `FONT_CN_COUNT` must stay <= 128. The table is currently full; reuse/remove unused legacy glyphs instead of appending a 129th.
- Treat `App/font_cn.h` / `font_cn.c` as the glyph source of truth. Read the four rules at the top of `font_cn.h` and `tools/font-source/README.md` before adding or changing a glyph: extract from `tools/font-source/wenquanyi_11pt.pcf` via `pcf2bdf`, never render with PIL/another engine, and do not vertically center.
- Glyph indices are encoded in the `CN_Cxxxx` macros: changing an index requires updating its macro and every user. Never reorder or renumber glyphs casually.
- Main menu names and category names stay English; submenu values are Chinese. Main menu labels fit 6 characters (`name[7]` in `t_menu_item`); `\n` in submenu strings means a new display line.
- The side-function action picker renders labels with the big font because Chinese glyphs need two framebuffer rows.

## Persistence
- `App/settings.c` manually packs/unpacks settings into fixed PY25Q16 flash addresses; it is not a raw struct dump. Adding a setting means updating both the load and save paths; use `App/app/menu_settings.def` for simple byte settings.
- Changing `VERSION_STRING_2` triggers the boot-time migration/reset in `SETTINGS_InitEEPROM()`.
- Multiboot/Multiconfig banks live in external flash and are managed by `mb_flash.c` / `ui/multiboot.c`; do not treat them as ordinary EEPROM settings.
