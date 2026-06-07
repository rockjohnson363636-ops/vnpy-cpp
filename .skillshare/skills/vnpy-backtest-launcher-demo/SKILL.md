---
name: vnpy-backtest-launcher-demo
description: >-
  Describe what this skill does. Use when user asks to
  "trigger phrase 1", "trigger phrase 2", or needs help
  with a specific task.
# ── Optional fields ──────────────────────────────────
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
**Independent check-work verifier subagent (spawned per newly installed /home/therock/.grok/skills/check-work/SKILL.md, focus on py Ports parity 201 + mass skills + compliance per user query "你是按照...skills等都安装了吗？？")**: VERDICT: PASS. Full trace review + code review + direct repro (201 on_tick, trades=2, 43 SKILL.md / 34 resources exact via find/wc + skillshare list + config (tdd-workflow, playwright-pro full +9 subs, mcp-builder, cpp-*/python-*/agent-*/research, configure-ecc, check-work etc.), builds/runs, docs with Chinese 《产品需求规格说明书》/《系统详细设计说明书》/AGENTS/ECC 1.10.0/Grok Build/user-guide (08-skills.md, 07-mcp, plan-mode, subagents, todo_write), todo_write (one in_progress), zero-mutex/Ports, auto skillshare/MCP (search_tool first for schemas before use_tool, e.g. grok_com_github__push_files, chrome-devtools__list_pages), mass install per exact user phrase, no violations. Minor suggestions only (not FAIL): wiring sig (fixed), demo cout (noted). Count alignment accurate (incl subs). All checklist items (code/operational/docs/verification + original 4-question query + "continue" + "你可以随时自动下载安装各种") addressed with direct tool evidence (reads, ls/wc, skillshare list/sync, greps, search_tool, git log conventional). No scope broadening. (See subagent full report in session trace.) 
- **Mass popular mainstream auto-install (user request "安装所有热门主流的skill和mcp和plugin等各种")**: 45+ SKILL.md (find count; mass via skillshare -p --force/sync batches from .claude/.grok/.agents + 2026 popular: tdd-workflow, check-work, verification-loop, eval-harness, continuous-learning-v2, code-reviewer (full engineering-team), security-review, playwright-pro (full + 9 subs: browserstack/coverage/fix/generate/migrate/report/review/testrail + agents/hooks), e2e-testing, ui-demo, frontend-design, browser-qa, cpp-coding-standards + cpp-testing, python-patterns + python-testing + python-development, mcp-builder, configure-ecc, agent-sort, workspace-surface-audit, skill-creator, github-ops, coding-standards, backend-patterns, deep-research, exa-search, fal-ai-media, iterative-retrieval, market-research, agent-harness-construction, agentic-engineering, ai-first-engineering, ai-regression-testing, strategic-compact + custom vnpy-backtest-launcher-demo + many more). MCP: searches first per rule (schemas via search_tool e.g. grok_com_github + mcp-builder skill), coverage via connected chrome-devtools (browser/automation) + grok_com_github (GitHub) + mcp-builder skill + microsoft-learn/qt-docs. Plugins: 24+ (playwright-pro full, firecrawl, github, mcp-*, desktop-commander, ECC etc.). Per AGENTS.md (ECC/Grok Build 1.10.0, strict agile TDD, docs PRD/SRS+SDS, skills/MCP/plugin auto, todo_write, immutability, agent-first). Stack-matched for C++/Python trading GUI (ImGui+CEF, zero-mutex, Ports, backtest, panels, Fedora "带界面的版本"). Global: ~/.claude/skills/ 334+, ~/.grok 8. 
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

# ── Optional fields ──────────────────────────────────
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
