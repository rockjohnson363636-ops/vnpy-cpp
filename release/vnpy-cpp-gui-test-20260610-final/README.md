vnpy-cpp "带界面的版本" GUI Test Release 20260610-final (phase2 "按你推荐的继续" update)
- Binary: vnpy-terminal (pre-built; ImGui + dummy CEF for TDD/compile; real CEF via user tar from index)
- Run: ./run-fedora-gui-test.sh (DATA_ONLY/xvfb or real display; supports VNPY_CTP_DEMO=1)
- Py strategy: sample_strategy.py (REAL on_tick via Ports, py-driven trades)
- CEF: see cef-real-tar-instructions.md (download Linux x64 Minimal from https://cef-builds.spotifycdn.com/index.html, export CEF_TAR=...; script auto for full visuals)
- CTP: see ctp-customer-integration-notes.md (VNPY_CTP_DEMO stub enhanced in launcher with flow logs + simulate readiness; provide real creds + SDK for live after GUI test)
- Evidence: py Ports parity (on_tick via engine/Ports, trades=2 from get_result(), path used) + CTP demo logs when env set. MCP chrome/grok used post-schema-search.
Per AGENTS.md (ECC 1.10.0, TDD, zero-mutex/Ports, SRS/SDS, auto skills/MCP, search-first).
Next: user real CEF tar + CTP creds (front/broker/user/pass/app/auth) for full login/settle + signoff + packaging. GUI test version + CTP demo path ready for Fedora 验收.