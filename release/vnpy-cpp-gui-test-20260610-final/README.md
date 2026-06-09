vnpy-cpp "带界面的版本" GUI Test Release 20260610-final
- Binary: vnpy-terminal (pre-built; ImGui + dummy CEF for TDD/compile; real CEF via user tar from index)
- Run: ./run-fedora-gui-test.sh (DATA_ONLY/xvfb or real display)
- Py strategy: sample_strategy.py (REAL on_tick via Ports, py-driven trades)
- CEF: see cef-real-tar-instructions.md (download Linux x64 Minimal from https://cef-builds.spotifycdn.com/index.html, export CEF_TAR=...)
- CTP: see ctp-customer-integration-notes.md (scaffolding ready with VNPY_CTP_DEMO stub in launcher; provide creds for real test)
- Evidence: py Ports parity (on_tick via engine/Ports, trades=2 from get_result(), path used)
Per AGENTS.md (ECC 1.10.0, TDD, zero-mutex/Ports, SRS/SDS, auto skills/MCP).
Next: real CEF tar + CTP creds for full integration/signoff.
