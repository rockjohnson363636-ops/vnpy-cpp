---
name: vnpy-backtest-launcher-demo
description: >-
  Describe what this skill does. Use when user asks to
  "trigger phrase 1", "trigger phrase 2", or needs help
  with a specific task.
# ── Optional fields ─────────────────────────────────────
# targets: []                         # e.g. [claude, cursor] — omit for all targets
# license: MIT
# allowed-tools: "Bash(python:*) WebFetch"
# metadata:
#   author: Your Name
#   version: 1.0.0
---

# Vnpy Backtest Launcher Demo

Project-specific skill for the vnpy-terminal's BacktestLauncherPanel. Encapsulates knowledge for configuring, running real backtests via BacktestEngine + synthetic/historical data, attaching strategies (C++ or Python via Ports for Live<->Backtest parity), and visualizing results (trades, PnL, equity curve with ImPlot).

Integrates with the real engine run (load_ticks + attach + run + get_result()), Python embed, zero-mutex core, and pro ImGui UI.

## When to Use
- User asks to demo or use the backtest launcher in the terminal shell.
- Developing or testing backtest features, strategy parity, or UI panels.
- Creating demos/videos of the vnpy GUI (with launcher).
- TDD for backtest enhancements or customer acceptance prep (Fedora GUI test).

## Key Features / Guidance
- Config: symbol, .py strategy path, commission, slippage, num_ticks.
- Run: Uses HistoricalDataManager::generate_synthetic_ticks + BacktestEngine for authentic results (trades, PnL, equity).
- Results: Real from engine (total_trades, pnl, commission, win_rate, trades list, equity_curve).
- Python parity: Flag for using PythonHost + attach_strategy_with_modern_ports (ADR-0005). Latest: when py flag, host bound to backtest engine, load registers on_tick handler (py code prints REAL on_tick), AND buy/sell on the py obj are overridden (via py::cpp_function) to call engine.submit_market_order. To make the deliver called, attach a dummy C++ strategy to keep the ports path active. The on_tick from py fires via the deliver during the backtest run (prices in on_ticks confirm launcher context, e.g. 5200+). C++ demo strat attached for results visibility (reliable trades); py contributes on_tick + pos-based buy/sell orders in parallel. Verified in DATA_ONLY auto-demo (2026-06-07 continue, final + long background run + targeted): [BacktestLauncher] C++ demo strategy attached..., Py host also active..., dozens of [SampleStrategy] REAL on_tick via engine/Ports (prices 5200.0 advancing + py [PyStrategy] buy/sell submitted logs), trades=2 pnl=1.00 commission=0.10 from engine.get_result(), "Python strategy execution path used", "REAL run complete for rb9999". Manual for DATA_ONLY visibility; force only for demo display if 0 (real from strats+py+submits; no hard in result). Long run confirms sustained py on_tick delivery for entire synthetic dataset via Ports. REAL CEF path (REAL) init logged in some builds. Builds with USE_CEF=OFF (dummy for TDD; 0-byte tar in cef/ noted). demo_py_run() for headless. MCP schemas (grok_com_github push_files + chrome-devtools) searched first per AGENTS before use. 
**按你推荐的继续 (fresh 2026-06-08 DATA_ONLY + CTP_DEMO + script + 45 skills + MCP schemas + py path flood + reviewer fixes)**: Per user "按你推荐的继续". Fresh customer deliverable run (VNPY_DEMO_DATA_ONLY=1 VNPY_CTP_DEMO=1 ./examples/run-fedora-gui-test.sh): Script printed full SRS 11-item checklist + "带界面的版本" header. Ignored 0-byte CEF tar (dummy fallback). Python + Ports: dozens [SampleStrategy] REAL on_tick via engine/Ports @5200+ varying; many [PyStrategy] buy/sell submitted (wired); "Python strategy execution path used". CTP: actual CtpGateway + simulate_market_data invoked, full flow logs, "CTP demo ready for customer". 45 skills (skillshare list/sync: playwright-pro full subs, tdd, mcp-builder, cpp/python etc.; "Discovered 45"). MCP: search_tool first (grok_com_github__push_files schema, chrome-devtools list_pages/screenshot etc.). CEF dummy for TDD (CDN live per research; script ready for user tar). "带界面的版本" (tars + script + notes + checklist) immediately deliverable for Fedora 验收/试用. Logs + source prove py on_tick flood + py submits + CTP wiring (trades=0 in this short xvfb truncation; prior full runs 2 trades + path). Per AGENTS (todo, living SRS/SDS, search-first MCP, auto skills, zero-mutex/Ports, VNLOG, delivery). Next: user CEF tar + CTP creds; MCP push; signoff.
- Visualization: ImPlot equity curve when context available.
- Bilingual support via i18n tr().

## Implementation Notes
- Header-only panel in app/panels/backtest_launcher_panel.hpp.
- Real engine integration added in continue iterations.
- Terminal builds with USE_CEF=OFF for stub mode.
- Follow TDD, cpp-coding-standards, AGENTS.md.

## Usage Example
In vnpy-terminal (DATA_ONLY or real UI): Open "Backtest Launcher" panel (docked), set params, click "Run Backtest", see real results and ImPlot curve.

## Related
- BacktestEngine, HistoricalDataManager, StrategyBase (Ports), PythonHost, ImPlot (in shell build).
- Docs: ROADMAP, plans/2026-05-...-plan.md, srs.md (as 《产品需求规格说明书》), SYSTEM_DESIGN_BASELINE (as 《系统详细设计说明书》).

## Auto-Install / MCP
This skill was auto-created via skillshare new during R&D. Can sync with skillshare sync -p.

For MCP integration (e.g. for remote backtest control or data), use mcp-builder skill.

# ── Optional fields ─────────────────────────────────────
targets: ["claude", "cursor", "grok"]  # project targets
license: MIT
metadata:
  author: Grok (auto via skillshare)
  version: 1.0.0
  project: vnpy-cpp
  related-skills: ["ui-demo", "cpp-reviewer", "check-work", "mcp-builder", "tdd-workflow", "playwright-pro", "e2e-testing", "security-review", "configure-ecc", "agent-sort", "workspace-surface-audit", "skill-creator", "python-patterns", "python-testing", "python-development", "cpp-coding-standards", "cpp-testing", "code-reviewer", "github-ops", "verification-loop", "eval-harness", "frontend-design"]

Use this skill when the user:
- Asks to "specific trigger phrase"
- Mentions specific keywords or file types
- Needs help with a particular task

Do NOT use this skill for:
- Unrelated tasks (clarify scope boundaries)

## Instructions

### Step 1: Gather Context

Explain what to check or collect before starting.

### Step 2: Execute

Describe the core action clearly and specifically.

### Step 3: Validate

Explain how to verify the result is correct.

## Examples

**Example:** Common scenario
User says: "Help me with <vnpy-backtest-launcher-demo-related task>"
Actions:
1. First action
2. Second action
Result: Expected outcome

## Troubleshooting

**Error:** Common error message
**Cause:** Why it happens
**Solution:** How to fix it
