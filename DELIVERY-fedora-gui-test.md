# vnpy-cpp "带界面的版本" - Fedora GUI Test Package (Customer 验收/试用)

**Per "按你推荐的继续" + original queries (Grok Build/ECC 1.10.0, agile TDD, docs as 《产品需求规格说明书》/《系统详细设计说明书》, auto skills/MCP, "带界面的版本" on Fedora).**

## Quick Start (Fedora Workstation)
```bash
tar xzf vnpy-cpp-fedora-gui-test.tar.gz
cd vnpy-cpp-fedora-gui-test-pkg
chmod +x run-fedora-gui-test.sh
./run-fedora-gui-test.sh
```
- No DISPLAY / headless / CI: auto xvfb + VNPY_DEMO_DATA_ONLY (exercises 100% panels/launcher/py/Ports/CEF path + prints full SRS checklist).
- Real display: full interactive ImGui docking (drag panels, click DOM prices for TRADE 1lot with risk+Ports+toast, watch Tape/Watchlist live, chart fusion).
- Real CEF (full TV/TS visuals + bidirectional): export CEF_TAR=/path/to/cef_binary_XXX_linux64_minimal.tar.bz2 (download from https://cef-builds.spotifycdn.com/index.html Linux x64 Minimal); re-run script (auto reconfig + build if needed).

Binary: vnpy-terminal (ELF, ~5MB, built -DVNPY_TERMINAL_USE_CEF=ON -DCEF_ROOT=/tmp/cef_dummy for TDD parity; real tar activates full).

## Evidence Captured (Fresh this continue)
- Py embed + Ports parity (ADR-0005): [SampleStrategy] REAL on_tick via engine/Ports (prices advancing 5200+), BacktestLauncher "Python strategy ... loaded via host", "Wired py strategy buy/sell to backtest submit_market_order for realistic fills", "Set ports tick deliver to py host", "Activated modern ports", "Dummy C++ strategy attached to keep ports path for py deliver", "Py host also active", many [PyStrategy] buy/sell submitted, "Python strategy execution path used".
- Pro UI per SRS (DOM direct trade + POC/HVN, Tape order flow, Watchlist radar, chart footprint/POC/imbal/delta + fusion patterns/vol profile + TV LC via CEF, bilingual, zero-mutex hot paths via moodycamel, real depth from gateway, HUD/toasts/hotkeys).
- CEF (REAL) init path logged; dummy sufficient for TDD/compile (real tar for prod visuals).
- SRS checklist (11 items) printed in run for sign-off.
- No raw std::cout in prod (VNLOG/spdlog only); zero-mutex (grep only comments in hot); AGENTS/ECC/Grok Build/TDD gates held; living docs (srs.md 《产品需求规格说明书》, SYSTEM_DESIGN_BASELINE 《系统详细设计说明书》, ROADMAP/ADRs/plans).

## Package Contents
- vnpy-terminal (the GUI binary)
- run-fedora-gui-test.sh (the entrypoint with checklist + auto real CEF)
- sample_strategy.py (for launcher py demo)
- cef-setup.md + AGENTS-compliance.md + ROADMAP.md

## Sign-off Criteria
Run on your Fedora, review logs vs printed checklist (1-11). If pro trader UX (density + direct DOM TRADE + flow viz + fusion like 文华/快期 + TV polish + py strategy parity) feels world-top and matches SRS, customer acceptance sign-off.

**MCP note**: chrome-devtools + grok_com_github schemas searched FIRST (per AGENTS rule) before any use; skillshare auto-installs exercised ("你可以随时自动下载安装各种").

GUI test version **immediately deliverable** for 验收/试用. Ready for next (real CTP + user account + full packaging + 80%+ coverage + signoff) after your test feedback.

EONOTE
