# Fedora Linux Workstation - "带界面的版本" Customer Acceptance Test Guide

**Target**: Deliver the pro trader hybrid UI/UX version (ImGui native panels + CEF TV LC chart with full TV/TS/文华/快期 fusion features) for immediate customer testing on Fedora.

**Status (post "按你推荐的继续" phase3 polish + CTP demo + MCP + CEF script + auto skills)**: 
- Phase3: Easy customer trial (tar + ./run-fedora-gui-test.sh supports VNPY_CTP_DEMO=1 for CTP flow logs + simulate readiness + py Ports; optional real CEF_TAR auto). MCP chrome (screenshot/eval/nav for GUI/chart verify), grok push + issue. 45+ skills. CEF instructions updated with "pick latest from index" (CDN live). CTP stub enhanced (detailed VNLOG in launcher for login/settle/MD/trader + Ports). Fresh DATA_ONLY + CTP_DEMO runs: py on_tick/trades=2/path used + CTP demo logs. "带界面的版本" + CTP demo immediately deliverable for Fedora 验收/试用 (extract, run script with envs, review SRS checklist). User provides real CEF tar + CTP creds for full post-signoff.
- Per AGENTS: todos tracked, verification (script/binary + greps), skills/MCP (search-first), living SRS/SDS, evidence captured. 

**Quick Start for Customer Trial (Fedora)**:
```bash
# Extract the deliverable tar (from release/ or examples/customer-deliverables/)
tar xzf vnpy-cpp-fedora-gui-test.tar.gz
cd vnpy-cpp-gui-test-*/

# Basic (DATA_ONLY or display)
./run-fedora-gui-test.sh

# With CTP demo readiness (logs + simulate path, no real creds/SDK needed)
VNPY_CTP_DEMO=1 ./run-fedora-gui-test.sh

# With real CEF for full TV LC charts/fusion (user provides tar >10MB from CDN)
export CEF_TAR=/path/to/your_cef_binary_XXX_linux64_minimal.tar.bz2
./run-fedora-gui-test.sh
```

Review vs SRS checklist (1-11 in script output or fedora md). Pass criteria: py Ports parity (REAL on_tick via engine/Ports, trades from engine.get_result(), "Python strategy execution path used"), pro panels (DOM/Tape/Watchlist/chart order flow/fusion), CTP demo logs (if env), zero-mutex/VNLOG, bilingual.

**Next after trial**: Provide real CEF tar URL + CTP creds (front, broker, user, password, app_id, auth_code) for full CTP integration test + signoff + packaging.