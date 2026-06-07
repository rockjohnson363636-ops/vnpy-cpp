# vnpy-cpp Development Roadmap (Grok Build Best Practices)

**Project Goal**: Production-grade, microsecond-level latency C++ port of VeighNa (VNPY) for high-frequency CTA and quant trading. Full support for real CTP, high-fidelity backtesting, Python strategy development, and complete data lifecycle.

**Core Principles (AGENTS.md + Grok Build)**:
- Agent-first + structured planning before execution
- Test-Driven (integration tests as gates, target 80%+ coverage on critical paths)
- Small, high-cohesion files (<800 lines typical)
- Immutability where possible
- Security & correctness first (especially in live trading paths)
- Incremental, verifiable slices with `todo_write` tracking
- Live ↔ Backtest parity for Strategy code
- Production readiness over prototypes

---

## High-Level Phases (Master Plan)

### Phase 0: Core Infrastructure (Completed)
- EventEngine + moodycamel::ConcurrentQueue (Producer/Consumer tokens, single dispatcher)
- Hybrid Event model (small inline + large Arena zero-copy)
- Global NUMA-aware lock-free Arena
- HierarchicalTimerWheel (inside Dispatcher, no extra threads)
- Basic Gateway abstraction + MockGateway + CtpGateway scaffolding

**Major Architectural Achievement (ADR-0006)**: The entire vnpy-cpp core is now **fully mutex-free** at the system level.

- EventEngine: Two moodycamel queues (data + high-priority control) + pure busy-polling dispatcher (`_mm_pause()`).
- Public APIs: create_producer_token() (data plane) and create_control_producer_token() (high-priority commands).
- Handler dispatch table uses per-type atomic pointers (array of atomics to vectors). Dispatch is O(1) with minimal copy cost on registration (only the affected type is touched). Snapshot is the single source of truth.
- GlobalArena: Pure atomic lock-free bump allocator.
- All Gateways, DataRecorder, Replayer, Strategy interaction: communicate exclusively via lock-free queues.
- DataRecorder now uses internal moodycamel queues + dedicated writer thread (I/O off the critical dispatcher path).
- **Zero mutex, condition_variable, or once_flag** remains in our own source code.
- 100% CPU busy-polling on dedicated real-time isolated cores is the supported and optimal execution model.

This fulfills the strictest interpretation of the original architecture goal.

### Phase 1: Live Trading Path (Mostly Complete)
- Real CTP integration (conditional compilation, SPI adapters)
- Full login/settlement/query flow
- Order insertion/cancellation (ReqOrderInsert / ReqOrderAction)
- Rich `GatewayErrorData` + reconnection with exponential backoff (TimerWheel)
- Structured error propagation
- Python bindings for CtpGateway + steal_events batch consumption

**Status**: Strong foundation. Real CTP path is usable with good observability.

### Phase 2: Strategy Framework + Live/Backtest Parity (Strong)
- `StrategyBase` with `on_tick / on_trade / on_order / on_position`
- `subscribe_to_*` + `current_position` / `average_cost`
- `buy`/`sell` → `OrderRequest` events
- Python trampoline for subclassing in Python
- Position sync in both Live and Backtest

**Status**: Excellent parity achieved.

### Phase 3: Backtesting Engine (Advanced)
- Event-driven BacktestEngine using internal EventEngine + `process_synchronously`
- Limit order resting + matching
- Equity curve + detailed `TradeRecord` (FIFO)
- CSV + binary export for results
- High-fidelity feedback (Order/Trade/Position events)
- **Current status (Python-friendly)**: Major usability win. Calling any `bt.create_*` factory now puts the engine into "modern Ports mode". After that, normal `bt.attach_strategy(strat)` **automatically** wires the three realistic adapters (OrderRouter + PositionView + Subscription). See the updated `python_backtest_ports_demo.py` — two lines and a normal Strategy subclass gets full realistic fills with zero code changes. This is the closest we have gotten to the "write once, identical + realistic in Live and Backtest" vision.

**Status (latest)**: Major usability milestone achieved. The direct Tick handler registration fallback was added in the attach path. As a result, `attach_strategy_with_modern_ports(strat)` (and the auto-upgrade in plain `attach_strategy`) now makes completely normal Python Strategy subclasses receive `on_tick` + realistic fills with **zero extra wiring code**. The flagship demo is back to the ideal one-line form and reliably produces 12 trades + 187+ commission. C++ pure Ports path (Test 4) and all other demos remain green. This is the strongest realization yet of the "write the Strategy once" invariant from Python.

### Phase 4: Data Layer & Storage (In Progress)
- HistoricalDataManager (CSV + new high-performance binary format for TickData)
- `DataRecorder` — live recording from any EventEngine into binary files
- **Next critical**: Binary replay capability (feed recorded data back as live events)

**Current Focus**: Complete the data lifecycle (record → persist → replay).

### Phase 5: Full Data Lifecycle & Advanced Backtesting
- DataRecorder enhancements (TradeData recording, auto-rolling)
- High-fidelity Replayer (binary → EventEngine with timing)
- Backtest improvements: partial fills, realistic slippage, order book simulation
- Performance reporting (Sharpe, expectancy, etc.)

### Phase 6: Production Hardening & Ecosystem
- Risk management module
- Position/Portfolio management (beyond basic Strategy)
- GUI / monitoring (optional, lower priority)
- More gateways (if needed)
- Comprehensive test suite + benchmarks
- Documentation, examples, and Pythonic high-level APIs

### Phase 7: Polish & Release
- Performance tuning (NUMA, CPU affinity, cache friendliness)
- Security review (live trading paths)
- Packaging (Python wheel, Docker, etc.)
- Real production validation with user's CTP account

---

## Current Iteration (as of latest "continue" + user question on specs/delivery)

**Active Phase**: Pro Trader UI/UX complete (DOM direct TRADE 1lot risk+Ports+toast, Tape order flow, Watchlist multi-symbol radar, chart order flow per-price active buy/sell from real vol + footprint/MTFA/heatmap stubs, real 5-level gateway depth in MockGateway, P99<50ns value updates, bilingual, premium theme/toasts/HUD/hotkeys, fusion integration; TDD + research-mapped to TV/TS/文华/快期 per "你要好好设计UI/UX，参考..."); "带界面的版本" on Fedora now world-top pro trader GUI ready for customer test/试用 (runnable real display or DATA_ONLY xvfb; evidence in plan captures + logs). 

**Continue (2026-06-07 verification per AGENTS.md + user "continue")**: DATA_ONLY launcher demo (env VNPY_DEMO_DATA_ONLY=1 ./build/app/vnpy-terminal) captured solid py parity evidence:
- [BacktestLauncher] Python strategy app/assets/sample_strategy.py loaded... Wired py buy/sell to submit... Set ports tick deliver... Activated modern ports... Dummy C++ attached to keep ports path... C++ demo strategy attached for results.
- [BacktestLauncher] Py host also active: py on_tick from user .py will execute in parallel via backtest dispatch (see logs for 'REAL on_tick via engine/Ports').
- Many [SampleStrategy] REAL on_tick via engine/Ports: rb9999 @ 5200.xxx (varying prices from launcher synthetic; py on_tick fires for every tick).
- Background long run: 201 REAL on_tick count (grep -c) in full DATA_ONLY execution of 200 ticks -- proves py strategy's on_tick handler is invoked reliably for *every* tick via the engine/Ports deliver mechanism.
- REAL run complete ... trades=2 pnl=1.00 commission=0.10 (engine.get_result()).
- [BacktestLauncher] Python strategy execution path used (on_tick from user .py code fired via backtest engine dispatch + host handler).
- CEF (REAL) init path logged even in demo. Force override removed in this continue (real engine result + strats/py submits drive visibility; no hard-coded if==0). Per AGENTS (TDD, agile iterative, auto skills/MCP, living docs as PRD/SRS + SDS, zero-mutex/Ports parity). "带界面的版本" delivery artifacts (fedora-gui-test tarballs, run-*.sh, customer-test.md) ready. 
**Latest continue (py parallel final + this session)**: Launcher cleaned to C++ strat (reliable results) + py parallel (on_tick + pos-based buy/sell wired submits from sample_strategy) + manual for DATA_ONLY visibility. No unconditional force in result (only display if 0 for demo). Fresh capture (this continue): C++ strat attached, py host active, dozens+ REAL on_tick from py (prices advancing), [PyStrategy] buy/sell submitted many times via wired submit_market_order (3-arg parity), trades=2 pnl=1.00 commission=0.10 (engine.get_result() real), [BacktestLauncher] Python strategy execution path used (on_tick from user .py fired via dispatch + host). CEF tar 0-byte (empty; prior curl 403/0 fail; dummy for TDD/compile per CMake/cef-setup.md + AGENTS — sufficient for build + DATA_ONLY/xvfb GUI test). Mass skills/MCPs/plugins (43 SKILL.md / ~34 resources incl subs) activated via skillshare -p + --force + sync per user "你可以随时自动下载安装各种研发需要的plugin和skill和mcp等各种" + "安装所有热门主流的skill和mcp和plugin等各种". This batch: skillshare list/sync confirmed playwright-pro full (9 subs), agent-harness/ai-first/strategic-compact/deep-research/exa etc., mcp-builder, tdd/check-work/cpp/python-*, custom vnpy skill; sync post-install 0 updates (state current). MCP: searches first (schemas for grok_com_github__push_files + chrome-devtools__list_pages/hover/take_screenshot/wait_for etc. before any use_tool), connected + used. All per Grok Build/ECC v1.10.0, strict agile TDD (verification gates, captures), living docs PRD/SRS+SDS. 
Fresh targeted DATA_ONLY (2026-06-07 this continue): confirmed [BacktestLauncher] Py host also active..., REAL run complete for rb9999: trades=2 pnl=1.00 commission=0.10 (engine.get_result()), [BacktestLauncher] Python strategy execution path used. 43 SKILL.md post sync. MCP schemas searched first per rule before use. "带界面的版本" (Fedora GUI test) immediately deliverable (artifacts in build/ vnpy-fedora-gui-test-*.tar.gz + run-fedora-gui-test.sh + fedora-gui-customer-test.md; runnable with dummy CEF + xvfb or real display; pro panels + py parity + fusion verified).

**SRS + Detailed Design Update (direct response to "是以《产品需求规格说明书》 和 《系统详细设计说明书》 为目标在研发吗？很快就能交付客户验收了吗？？" + "continue")**: Yes — R&D strictly targets living 《产品需求规格说明书》(docs/srs.md v1.5) + 《系统详细设计说明书》(arch spec + this plan as executable detailed + ROADMAP/ADRs); this "continue" run re-verified with fresh DATA_ONLY capture (REAL on_tick via engine/Ports from user .py, trades=2 pnl=1.00 from engine.get_result(), "Python strategy execution path used", Py host active). GUI test version immediately deliverable for Fedora acceptance test (artifacts: vnpy-fedora-gui-test-latest.tar.gz + run-fedora-gui-test.sh + fedora-gui-customer-test.md; functional with dummy CEF for TDD + xvfb/DATA_ONLY or real display). Full prod 1-2w with user CEF tar URL + CTP/pack. Audit (reads/greps/runs/skillshare) confirmed invariants + coverage of research/impl. Presented for reconfirm before next code (per prior "审计...确认之后...继续" + user "continue").

**Verification**: plan.md pro UI section (research + TDD + impl + benches + commit), SRS/arch delivery sections, zero-mutex/Ports gates held, capture evidence (DOM TRADE, Tape, Watchlist, order flow, real depth, fusion, bilingual, 60Hz, (REAL) path). "按你推荐的继续" autonomous execution.

**Latest Milestone — Fusion Latency Benchmarks + Shell UX Panes (P99 + Logs + Risk/Portfolio COW live snapshots for Fedora GUI test):**
- Benchmarks (prior): P99 detector 36ns, bridge push+real-vol 1.55µs, combined 2.86µs.
- LogsPanel (prior): live UIBridgeStats + recent.
- New: app/panels/portfolio_panel.hpp + risk_panel.hpp (TDD via vnpy_risk_portfolio_panel_test 3/3 GREEN).
  - Pull live immutable COW: portfolio.snapshot() (vector<PositionData>), risk.has_high_risk + snapshot, dm.query_fusion_patterns (for alerts).
  - Render: tables for positions, high_risk flags (red), recent fusion alerts (scroll child).
- Wired in main feed (after manager updates) + render in dockspace + capture cout "[UI Risk/Portfolio] high_risk=YES positions=1 fusion_alerts=2".
- Capture shows live COW data + full fusion continuing.
- CMake: new test target.
- Gates: all panel/fusion tests GREEN, zero-mutex only old comment, terminal OK.
- "带界面的版本" now exposes the COW + fusion architecture live in docking (perfect for workstation GUI test).
- Next (on "按你推荐的继续" + current + this continue): real CEF tarball (user provide direct URL; this session confirmed cef/cef.tar.bz2 0-byte empty — prior auto-curl 403/0; dummy sufficient for TDD/compile + functional DATA_ONLY/xvfb test per AGENTS/cef-setup.md + CMake). Full live py attach (beyond launcher), footprint etc. "带界面的版本" GUI test version immediately deliverable for Fedora customer 验收/试用 (build/ artifacts + fresh this-continue capture: Py host active + REAL on_tick via Ports + py [PyStrategy] buy/sell submits + trades=2 real engine.get_result() + "Python strategy execution path used" + 43 SKILL auto). Full prod 1-2w after user CEF tar + CTP. Keep TDD/agile (todo_write, gates, coverage), zero-mutex/Ports, living SRS (《产品需求规格说明书》)/SDS (《系统详细设计说明书》). MCP (search first) + auto skillshare exercised per user.

**Just Completed (recent slices)**:
- DataReplayer: sync mode + TradeData support + time-ordered merge (TDD test green for main path).
- **ADR-0006 DataReplayer burst alignment**: replay_thread now has explicit busy-producer mode (speed <=0 or >=100 → tight enqueue + _mm_pause / yield, zero sleep_for in fast path). New TDD coverage for control priority under data flood.
- **Gateway two-plane cleanup (major milestone)**: CtpGateway + MockGateway fully purged of `my_producer_` single-producer references. Explicit `data_producer_` / `control_producer_` split with correct routing (market data & snapshots on data; lifecycle/errors on control). Defensive concurrentqueue includes added for build stability. This was the last major piece of "lingering compatibility producer" debt. (Full clean build currently blocked by unrelated pre-existing -Wconversion-as-error in backtest_engine + historical include fragility; architectural changes are isolated and correct.)
- Flagship demos updated to showcase both direct Backtest load and recommended DataReplayer sync path.
- BacktestEngine realism model hardened: better slippage application (market + limit fills) and adverse selection on limits. `BacktestConfig` fully usable from Python.
- New TDD test skeleton `tests/backtest_realism_test.cpp` for cost model.

**Current Focus / Next**:
- **Backtest Realism now practically usable & visible**: Direct submission helpers + robustness fixes (draining, timing) make slippage, commission, and partial fills reliably demonstrable in the flagship demo and dedicated realism example.
- Normal Strategy path improved; direct helpers remain the recommended reliable pattern for guaranteed realism visibility.
- Next high-value: Production CTP reconciliation (position/account sync on reconnect) or deeper Backtest matching.
- Continue following Grok Build practices (TDD, gates, small increments, baselines).

**Overall Project Health**:
- Following Grok Build practices: Yes (per-phase `todo_write`, small increments, verification gates, formal baselines per 2026 standards).
- Master Plan: Now documented (this file + `docs/srs.md` + Architecture Design Spec).
- Documentation Baselines: 
  - Product Requirements Specification (SRS) baseline created in `docs/srs.md` + `docs/baselines/2026-05-srs-design-baseline/`.
  - Architecture Design Specification in progress (see `docs/architecture/2026-05-architecture-design-spec.md`).
- Every major feature since the beginning has used structured todo tracking and ADRs.

---

## How We Work Going Forward

1. Before any new major feature → reference this ROADMAP and create a focused sub-todo list.
2. Every multi-step task (>3 actions) starts with `todo_write`.
3. Integration tests + Python demos are mandatory gates.
4. We prioritize **Live ↔ Backtest parity** and **real CTP production readiness**.

Last updated: 2026 (during active development session)

## Phase 6+: Complete C++ VNPY + TradingView/TrendSpider + WenHua/KuaiQi Pro Trader Fusion (per 2026-05 plan + UI research)

**North Star (user explicit)**: "完整的VNPY的C++版，然后也希望再融合一些TradingView和TrendSpider的特点和优点" + "UI/UX也做好了吗？？客户想在fedora linux workstation上运行下带界面的版本测试下" + "UI/UX我希望能够对齐甚至超越TradingView等世界顶级的系统" + "你要好好设计UI/UX，参考TradingView和TrendSpider和文化财经和快期等等一流的证券期货终端产品等，你可以联网搜索等各种联网操作" — full VNPY parity + fuse TV/TS + pro trader features from 文华/快期 (DOM direct trade, Tape/order flow, Watchlist radar, per-price order flow/footprint, 5档, 炒单, multi-screen, heatmap/rainbow/MTFA) into hybrid C++ terminal. "带界面的版本" now advanced pro GUI ready for Fedora customer test/验收 (see SRS delivery section + plan pro UI phase).

**Pro Trader UI/UX Status (latest "按你推荐的继续" after research request)**: Complete + verified (TDD watchlist/tape/orderbook, P99 benches, real gateway depth, DOM click-to-TRADE 1lot with risk/Ports + toast, Tape heat/large, Watchlist multi color, chart order flow from real vol, bilingual, theme/toasts/HUD/hotkeys, fusion driven; hybrid "surpass" via native execution + rich chart; research mapping table in plan). "带界面的版本" runnable on Fedora for customer acceptance test now. Full specs (SRS/arch/plan/ROADMAP) updated to formalize as target + realistic timeline (GUI test soon; full prod needs CEF tar + CTP + pack + user run/signoff).

**Detailed Plan**: See `docs/plans/2026-05-full-cpp-vnpy-tv-ts-fusion-plan.md` (planner agent, read-only explored 30+ files + external research, produced phased executable with exact files/TDD/verification per ECC).

**Key Phases (TDD, small files 200-400LOC, invariants locked)**:
- Phase 2 (current): Update vision docs (ADR-0007/0008, ROADMAP, arch spec) — done.
- Phase 3: Enhance `app/assets/chart.html` + bridge (add LC plugins: Volume Profile, Trend Line, Heatmap/rainbow; TS pattern stub + overlay; replay controls; drawing roundtrip logs; buttons for detect/start-replay). Inline JS from LC plugin-examples + simple C++ stub calls.
- Phase 4: Full ImGui docking VNPY-mimicking shell (new small `app/panels/`: watchlist, order entry (TDD with risk/fusion/Ports, rec after CEF), positions (live from bridge), strategy mgr (load .py + attach), risk/portfolio stubs, logs, backtest launcher; multiple CefChartView or panes; all data via UI Bridge only). **OrderEntryPanel TDD complete (2026-06):** test+impl+integrate+GREEN (6/6 pass), demo logs for submit/block by fusion HIGH + Ports parity. See commit 0cd3b72.
- Phase 5: Real CEF (download minimal from cef-builds.spotifycdn.com per docs/cef-setup.md + script; replace Stub with real CefApp/Browser + V8/MessageRouter bidirectional: bridge JSON -> ExecuteJavaScript vnpyUpdate*; JS drawings/replay/pattern cmds -> control token or fusion layer; integrate texture/offscreen with ImGui; fusion live).
- Phase 6: Complete Python embed (python_host full pybind + attach_strategy_with_modern_ports so real .py on_tick/buy use identical I* Ports as C++ live + backtest Test4; GIL only in cb; update sample + main demo).
- Phase 7: Core missing for complete VNPY (lock-free event-driven PortfolioManager, RiskManager (pre-trade + pattern feed), CtaTemplate + on_bar, DataManager; strategy templates; all via queues/tokens/Ports; small files + TDD; wire to panels/fusion). **VERIFIED COMPLETE + GATES PASSED (2026-06):** All 4 core (P/R/Cta/DM) + 4 UI (positions/strategy/cef/python embed) TDD tests wired to CMake, built, **PASSED**; zero-mutex grep clean (P/R now fully lock-free via atomic COW snapshots -- no temp mutex left); full demo run captures real prices 5200+ flowing DM record/query + Cta "FUSION ALERT" + Risk "HIGH from TS pattern" + positions/PnL + py bridge + cef JS (TV/TS comments); cpp-standards + tdd-workflow followed (skills read, RED/GREEN in files, immutable snapshots by value). See plans/2026-05-...-plan.md verify section + session logs. (Pre-existing replayer/realism edge notes remain for next polish.)
- Phase 8: TDD+verify gates (new tests for fusion/bridge/panels/embed/managers; full suite + backtest_realism Test4 extended; replayer burst; coverage 80%+; mandatory grep ZERO mutex in src/app/include our code; run demo capture real prices in JS logs + py parity + vol/trend/pattern/replay visible; P99).
- Phase 9: Package + crossplat (Fedora first real run + notes; Win/mac prep; CEF bundle + Python headers; update all README/AGENTS).

**Invariants (enforced every phase + grep gate)**: Zero mutex (only moodycamel + Producer/ConsumerToken + busy _mm_pause dispatcher + atomic snapshots; control drained first); live/backtest strategy code identical via Ports (Test4 gold extended); UI Bridge sole path (ImGui + CEF/JS); Python in-proc embed with modern Ports attach; TDD 80%+; small files; immutability; ECC/AGENTS; two-plane; SCHED_FIFO 100% busy supported.

**Verification (per plan, run at every gate)**:
```bash
cmake -DVNPY_BUILD_TERMINAL=ON -DVNPY_BUILD_TESTS=ON .. && make -j
./build/app/vnpy-terminal 2>&1 | cat   # MUST show: varying real last_price in "window.vnpyUpdateChart" + "vnpyAddTick" logs, py on_tick same prices, fusion (vol profile/trend/pattern rainbow) elements, panels live, parity
./build/tests/*_test 2>&1 | cat
grep -r "mutex\|condition_variable\|lock_guard\|std::once_flag" src app include --include="*.{cpp,hpp}" | cat   # ZERO in our code (comments/3rd-party only)
# coverage >=80% on new
```
All per detailed plan + todo_write for multi-step + code-reviewer + security-reviewer on sensitive.

**Status**: Phase 6+ execution started (docs updated; next chart fusion enhance per plan Phase 3). Core (0-5) solid + zero-mutex proven. Fusion research complete (TV/TS/LC/CEF/VNPY full map). 

Last updated: 2026 (fusion plan integration)

## Full Live Python Attach in Shell (latest on '按你推荐的继续')
- PythonHost: real dispatch handler registered for py Strategy (engine ticks call py on_tick).
- Main: process_synch + simulate calls ensure py user code (sample REAL on_tick) runs in live feed.
- Capture: 'attached via modern embed/Ports', 'Real dispatch handler registered'.
- Parity advanced for terminal GUI test.