# oll.fx GD Toolkit

Geode mod source for Geometry Dash **2.2091**, targeting Windows x64 and Android arm64.

## Current implementation status

- Floating `oll.fx` launcher and compact practice panel: implemented in source.
- Bounded PlayLayer speed multiplier (0.25x–2.0x): implemented in source.
- Noclip / no-death, hitboxes, instant completion, free-fly, icon unlocks, FPS and physics controls: not implemented yet; these require additional version-specific hooks and testing.
- The panel uses Geode/Cocos nodes with an ImGui-like compact style; Dear ImGui is not bundled.

## Compatibility

Targets Geometry Dash 2.2091 and Geode `v6.0.0-beta.2`. This is an initial source scaffold; binaries are produced only if GitHub Actions completes successfully.

## Build locally

Install the matching Geode SDK and CLI, then run `geode build -p win` or `geode build -p android64`.

Test gameplay modifications in offline practice sessions. The speed hook scales the delta passed to `PlayLayer::update`; it does not alter every physics subsystem.
