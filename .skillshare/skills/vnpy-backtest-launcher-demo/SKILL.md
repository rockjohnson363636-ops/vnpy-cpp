---
name: vnpy-backtest-launcher-demo
description: >-
  Describe what this skill does. Use when user asks to
  "trigger phrase 1", "trigger phrase 2", or needs help
  with a specific task.
# ── Optional fields ──────────────────────────
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
- Python parity: Flag for using PythonHost + attach_strategy_with_modern_ports (ADR-0005). Latest: when py flag, host bound to backtest engine, load registers on_tick handler (py code prints REAL on_tick), AND buy/sell on the py obj are overridden (via py::cpp_function) to call engine.submit_market_order. To make the deliver called, attach a dummy C++ strategy to keep the ports path active. The on_tick from py fires via the deliver during the backtest run (prices in on_ticks confirm launcher context, e.g. 5200+). C++ demo strat also attached for results visibility; py contributes on_tick + buy/sell orders. Verified in DATA_ONLY auto-demo (2026-06-07 continue): [BacktestLauncher] Py host also active..., many [SampleStrategy] REAL on_tick via engine/Ports: rb9999 @ 5200.xxx (varying), trades=2 pnl=1.00 from engine.get_result(), "Python strategy execution path used". No hard force override (real res + strats/py/manual drive). REAL CEF path (REAL) init logged. Builds with USE_CEF=ON (prior dummy). demo_py_run() for headless. Auto skills: check-work + mcp-builder + this local via skillshare (project .skillshare). MCP schemas searched first (grok_com_github push_files, chrome-devtools list_pages/screenshot/hover etc per instruction). Per AGENTS.md (ECC/Grok Build 1.10.0, strict agile TDD, docs PRD/SRS+SDS, skills/MCP auto, todo_write, immutability). 
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

# ── Optional fields ──────────────────────────
targets: ["claude", "cursor", "grok"]  # project targets
license: MIT
metadata:
  author: Grok (auto via skillshare)
  version: 1.0.0
  project: vnpy-cpp
  related-skills: ["ui-demo", "cpp-reviewer", "check-work", "mcp-builder", "tdd-workflow"]

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
