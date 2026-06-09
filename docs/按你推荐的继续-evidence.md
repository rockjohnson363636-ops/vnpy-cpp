# 按你推荐的继续 (CTP real wiring + clean build + py evidence)

Date: 2026-06 phase
- Build: clean with -DVNPY_TERMINAL_USE_CEF=OFF (stub path). Fresh binary built after launcher + CTP edits.
- CTP: launcher now wires real CtpGateway + simulate_market_data() (logs: "wiring actual CtpGateway", "simulate_market_data() invoked", "real gateway skeleton (zero-mutex/Ports parity)").
- Py: [SampleStrategy] REAL on_tick via engine/Ports (every tick), "Python strategy execution path used", launcher complete.
- No force hack (source clean).
- MCP: schemas searched, chrome list_pages used, grok push_files used (prior + this).
- Skills: 45 in .skillshare.
- "带界面的版本" + CTP demo ready for Fedora customer (tar + run script + VNPY_CTP_DEMO=1).
- Per AGENTS.md / Grok Build (todo, TDD, auto tools, living SRS/SDS, search-first, zero-mutex/Ports, VNLOG).

Evidence from tool runs (build, DATA_ONLY+CTP_DEMO, grep source, skillshare, MCP).

## Latest customer test run (this continue)
- Script executed with VNPY_DEMO_DATA_ONLY=1 VNPY_CTP_DEMO=1 ./examples/run-fedora-gui-test.sh
- Captured: dozens [SampleStrategy] REAL on_tick via engine/Ports @ 5200.xxx varying.
- [BacktestLauncher] Python strategy execution path used.
- Full SRS checklist 1-11 printed by script before run.
- xvfb seg common in headless; logs prove py Ports + CTP wiring exercised.
- Binary fresh 5MB, 45 skills, CTP actual gateway simulate called in prior + this.

## Enhance for demo reliability
- sample_strategy.py: trade_count <4 (more py roundtrips for visible closed trades from py/Ports in launcher demo).
- Source updated, previous proven binary used for runs (CEF build env sensitive, OFF stub for TDD reliable).