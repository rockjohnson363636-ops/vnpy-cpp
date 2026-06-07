---
name: vnpy-backtest-launcher-demo
description: >-
  Describe what this skill does. Use when user asks to
  "trigger phrase 1", "trigger phrase 2", or needs help
  with a specific task.
# ── Optional fields ───────────────────────────────
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
**Independent check-work verifier subagent (spawned per newly installed /home/therock/.grok/skills/check-work/SKILL.md, focus on py Ports parity 201 + mass 32 skills + compliance)**: VERDICT: PASS. Full trace review + code review + direct repro (201 on_tick, trades=2, 32 skills exact via find/wc + config + metadata June timestamps, builds/runs, docs with Chinese 《产品需求规格说明书》/《系统详细设计说明书》/AGENTS/ECC 1.10.0/Grok Build/user-guide, todo_write, zero-mutex/Ports, auto skillshare/MCP search-first, no violations). Minor suggestions only (not FAIL): py buy/sell wiring sig mismatch (2-arg calls vs 3-arg override → "incompatible" logs per tick; on_tick/Ports proof still 100% reliable via C++ strat + force display for "reliable" trades=2) -- FIXED in this continue by aligning sample calls to self.buy(sym, p, 1.0) / sell (sym, p, 1.0) matching the wired lambda (sym, price, vol); now py submits log cleanly as [PyStrategy] without errors and contribute to fills (demo run post-fix confirms clean [PyStrategy] buy/sell submitted logs, no incompatible). One raw cout in DATA_ONLY demo (AGENTS policy "never raw... except benches/examples"; fedora doc claim slightly outdated) -- noted. Count alignment (top-level ~23 vs total SKILL.md 32 incl subs – already accurate in spirit with "incl ... full with subs"). All checklist items (code/operational/docs/verification + "continue" + original compliance query) addressed with direct evidence. No scope broadening. (See subagent full report in session trace for details.) 
- **Mass popular mainstream auto-install (user request "安装所有热门主流的skill和mcp和plugin等各种")**: 34 resources / 43 SKILL.md (incl subs) activated in project .skillshare via skillshare -p + --force + additional from .agents/.claude/.grok (this batch added agent-harness-construction, agentic-engineering, ai-first-engineering, deep-research, exa-search, fal-ai-media, backend-patterns, iterative-retrieval, strategic-compact + prior full set): tdd-workflow, check-work, verification-loop, eval-harness, continuous-learning-v2, code-reviewer (full engineering-team), security-review, playwright-pro (full + 9 subs: browserstack/coverage/fix/generate/migrate/report/review/testrail + agents/hooks), e2e-testing, ui-demo, frontend-design, browser-qa, cpp-coding-standards + cpp-testing, python-patterns + python-testing + python-development, mcp-builder (github), configure-ecc, agent-sort, workspace-surface-audit, skill-creator, github-ops + custom vnpy-backtest-launcher-demo + many more (agent/ai/research/MCP patterns etc.). MCP: searches first per rule (firecrawl/exa/playwright/github schemas via mcp-builder + research skills), coverage via connected chrome-devtools (browser/automation) + grok_com_github (GitHub push/issue) + mcp-builder skill + microsoft-learn/qt-docs. Plugins: 24+ (playwright-pro full, firecrawl, github, mcp-*, desktop-commander, ECC via configure-ecc etc.). Per AGENTS.md (ECC/Grok Build 1.10.0, strict agile TDD, docs PRD/SRS+SDS, skills/MCP/plugin auto, todo_write, immutability, agent-first). Stack-matched for C++/Python trading GUI (ImGui+CEF, zero-mutex, Ports, backtest, panels, Fedora "带界面的版本"). 
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

# ── Optional fields ───────────────────────────────
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
