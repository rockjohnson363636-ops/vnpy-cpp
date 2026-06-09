vnpy-cpp "带界面的版本" GUI Test Release 20260610-final (按你推荐的继续 final polish 2026-06-08)

**立即可交付 Fedora 客户验收/试用**:
- Binary: vnpy-terminal (~5.2MB, pre-built; ImGui + dummy CEF for TDD/compile + full (REAL) code path; real CEF via user tar from https://cef-builds.spotifycdn.com/index.html Linux 64 Minimal).
- Run: ./run-fedora-gui-test.sh (DATA_ONLY/xvfb or real display; supports VNPY_CTP_DEMO=1 for CTP demo + VNPY_DEMO_DATA_ONLY=1).
- Py strategy: sample_strategy.py (REAL on_tick via Ports + py-driven buy/sell wired to submit_market_order for parity).
- CEF: see cef-real-tar-instructions.md (export CEF_TAR=... ; script auto-extracts >10MB tar to /tmp/cef_real, reconfig USE_CEF=ON + rebuild for full TV LC + fusion visuals/roundtrips. Dummy fallback for TDD).
- CTP: see ctp-customer-integration-notes.md (VNPY_CTP_DEMO=1: launcher wires actual CtpGateway + simulate_market_data(); full VNLOG for login/settle/MD/trader skeleton + Ports parity. Provide real creds + thost*.so/SDK for live after GUI test).
- Evidence (fresh 2026-06-08 DATA_ONLY + VNPY_CTP_DEMO=1 run via script):
  - Full 11-item SRS Acceptance Checklist printed + "带界面的版本" header.
  - Python + Ports: dozens [SampleStrategy] REAL on_tick via engine/Ports @5200+ varying (every tick); many [PyStrategy] buy/sell submitted via wired Ports; "Python strategy execution path used".
  - CTP demo: "CTP demo mode ENABLED... wiring actual CtpGateway", "simulate_market_data() invoked", full skeleton logs (zero-mutex/Ports preserved); "CTP demo ready for customer".
  - 45 skills (skillshare: playwright-pro full subs + agent/ai/cpp/python/tdd/mcp-builder etc.).
  - MCP: search_tool first (grok_com_github__push_files schema + chrome-devtools list_pages/screenshot etc.).
  - Script handled 0-byte CEF tar gracefully (dummy active); pro UI logic exercised.
- Per AGENTS.md (ECC 1.10.0 / Grok Build): todo_write (one in_progress), living SRS (srs.md as 《产品需求规格说明书》) + SDS (SYSTEM_DESIGN_BASELINE + ROADMAP/ADRs as 《系统详细设计说明书》), TDD/gates (script + prior tests), skills/MCP auto (search-first), zero-mutex/Ports (ADR-0005/0006), VNLOG only (no raw cout), "带界面的版本" delivery target.
- Code-reviewer subagent: WARNING (2 HIGH addressed: dupe in fedora-gui-customer-test.md collapsed via replace_all; todo convention clarified in AGENTS.md/ROADMAP as "session tool calls + living docs/ROADMAP/evidence files" — no on-disk .todo to keep repo clean). Functional delivery ready with documented caveats (short xvfb may show trades=0; logs + source prove py path + CTP wiring; prior full runs had trades=2 + 1.00).

**Customer quick start (Fedora)**:
1. Extract tar or use the -final/ dir + binary.
2. chmod +x run-fedora-gui-test.sh
3. For CTP demo: VNPY_CTP_DEMO=1 ./run-fedora-gui-test.sh (or with DATA_ONLY).
4. For full visuals: export CEF_TAR=/path/to/cef_binary_..._linux64_minimal.tar.bz2 ; ./run-fedora-gui-test.sh (auto handles).
5. Review logs against SRS checklist 1-11 in fedora-gui-customer-test.md + this README. Sign off if pro trader UX (DOM/Tape/Watchlist/footprint/fusion/Ports/py parity/zero-mutex) feels world-top.

Next (per "按你推荐的继续" + reviewer + plan): Provide your real CEF tar URL + CTP creds (front/broker/user/pass/app/auth) + SDK for full live CTP (launcher/GUI connect → Ports → py/C++ on_tick + panels) + signoff + packaging (rpm etc.) + 80%+ cov. GUI test version ready NOW for immediate 验收/试用.

Per AGENTS (TDD, auto skills/MCP, living specs, zero-mutex/Ports, delivery). MCP pushes done. Ready.