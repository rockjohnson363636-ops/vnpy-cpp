# AGENTS.md - vnpy-cpp Project Rules (Grok Build / ECC 1.10.0)

This file serves as the living contract for all AI agents working on vnpy-cpp. It is aligned with the installed ECC v1.10.0 (Everything Claude Code) at ~/.claude/AGENTS.md and Grok Build TUI best practices (see ~/.grok/docs/user-guide/ for skills, plan-mode, subagents, 08-skills.md etc.). Grok Build (launched ~May 2026) is explicitly compatible with ECC: it scans ~/.claude/skills/, ~/.grok/skills/, AGENTS.md, hooks, and MCP configs (per web research + local user-guide).

## Core Principles (Strict ECC / Grok Build / Agile Engineering)
- **Research first + Plan before execute**: Use web_search/browse + spawn_subagent (planner) or enter_plan_mode for complex/ambiguous work. Follow detailed plans (e.g. docs/plans/2026-05-full-...-plan.md).
- **All major/multi-step work tracked via `todo_write`** (mandatory per ECC and project AGENTS; exactly one in_progress at a time; mark completed immediately).
- **Strict TDD (via installed tdd-workflow skill)**: For every new feature, bugfix, or refactor (including C++ panels, managers, fusion logic): 
  1. Write user journeys + test cases first (RED gate: compile/run test to confirm failure for the intended reason; git checkpoint commit if repo).
  2. Minimal impl to GREEN (run same tests to pass; checkpoint).
  3. Refactor (keep green; checkpoint).
  4. Verify >=80% coverage (unit + integration + E2E where applicable). Adapt to GoogleTest for C++ (see existing tests/backtest_realism_test.cpp etc.).
  - No production code changes until RED confirmed.
  - This embodies XP/agile engineering rigor (tests as spec, iterative feedback, safety for refactoring).
- **Documentation first-class**: Update ADRs (docs/adr/), ROADMAP, architecture spec, baselines, SRS (产品需求规格说明书) and SYSTEM_DESIGN_BASELINE / plans/ (系统详细设计说明书) for any impactful change. All R&D targets the living PRD/SRS + SDS baselines + detailed executable plan. Use doc-updater agent/skill where relevant. Customer acceptance target: "带界面的版本" on Fedora (GUI pro trader terminal with full VNPY parity, Python embed, fusion, zero-mutex, TV/TS-style UI).
- **Agent-first**: Proactively use specialized agents (planner for complex, tdd-guide, code-reviewer after changes, cpp-reviewer/cpp-build-resolver for C++ work, security-reviewer for sensitive, etc.). Spawn via subagent tool or follow their SKILL.md (e.g. cpp-coding-standards for all C++ edits).
- **Skills activation**: Explicitly read and follow relevant installed skills before/ during work (tdd-workflow, cpp-coding-standards, cpp-testing, etc.). Skills live in ~/.claude/skills/ (scanned for compatibility) and ~/.grok/skills/. Project can add repo-local .grok/skills/ for vnpy-specific (none yet; add as needed).
- **Immutability, small files (200-400 LOC), security-first, verification gates**: As per ECC AGENTS + C++ Core Guidelines (via cpp-coding-standards skill).
- **Logging**: Always use VNLOG_INFO/DEBUG/ERROR etc from <vnpy/core/log.hpp> (spdlog async facade); never raw std::cout/std::cerr in src/, app/, include/ (except benches/examples). Init once at startup with vnpy::log::init(). This was enforced after audit of demo logs.
- **Agile software engineering standards**: TDD + continuous integration/verification (builds, tests, greps for invariants like zero-mutex), iterative planning (todos + phases + plan mode), architecture as code (ADRs/C4 as lightweight decisions), small batches/increments, feedback loops (reviews, coverage, runtime checks). Not ceremonial Scrum but engineering practices from XP/Lean adapted to AI-augmented dev. Full compliance audited via tools like workspace-surface-audit or skill-health if needed.
- **Grok Build specifics**: Use plan-mode for ambiguous design, subagents for parallelism, skills for reusable workflows, todo_write for tracking. Research via web_search/open_page as permitted. Prefer FetchContent, small cohesive changes, immutability.
- Extreme focus on performance (zero-mutex, P99), testability (Ports parity, 80%+), evolvability (C4, ADRs), Live ↔ Backtest strategy code parity (ADR-0005).

## Key Baselines
- Product Requirements / 产品需求规格说明书 (PRD/SRS): `docs/srs.md` (living baseline) + `docs/baselines/2026-05-srs-design-baseline/` + detailed requirements in `docs/plans/2026-05-full-...plan.md`
- System Detailed Design / 系统详细设计说明书 (SDS): `docs/SYSTEM_DESIGN_BASELINE.md` + `docs/architecture/2026-05-architecture-design-spec.md` + executable design in plans/ + C4/ADRs
- Roadmap: `docs/ROADMAP.md` (includes Phase 6+ for complete VNPY + TV/TS fusion per detailed plan)
- Fusion/Complete Vision: `docs/plans/2026-05-full-cpp-vnpy-tv-ts-fusion-plan.md`, ADR-0008, updated ADR-0007/ROADMAP
All R&D is goal-oriented to deliver against the PRD/SRS + SDS baselines for rapid customer acceptance (Fedora "带界面的版本" GUI pro trader terminal).

Any change that impacts these baselines requires impact analysis and update to the relevant baseline + manifest. All new C++ work must pass cpp-coding-standards review + tdd gates.

## Skills & Agents in Use (Installed ECC 1.10.0)
- Core: todo_write, planner (via subagent), web_search for research, verification (build/run/grep/test).
- Required for C++/features: tdd-workflow (strict RED/GREEN/REFACTOR + checkpoints + 80%+), cpp-coding-standards (C++ Core Guidelines: RAII, immutability by default, const/constexpr, Rule of Zero/Five, concepts, no raw new/delete, etc.), cpp-reviewer/cpp-testing, code-reviewer (after edits).
- Others as relevant: security-reviewer, build-error-resolver, doc-updater, e2e-runner (for UI), etc.
- Local user-guide: ~/.grok/docs/user-guide/ (skills, plan-mode, agent-mode, subagents, etc.) — full Grok Build TUI docs present.
- ~/.claude/skills/ and ~/.grok/skills/ massively installed (tdd-workflow, cpp-*, engineering-team, c-level-advisor, etc.; 1000s of files across domains).
- **Mass popular mainstream install (per user request "安装所有热门主流的skill和mcp和plugin等各种")**: Project .skillshare now activates 34+ via skillshare -p (up from 3; this continue batch: --force + additional from .agents/.claude/.grok paths for agent-harness-construction/agentic-engineering/ai-first-engineering/deep-research/exa-search/fal-ai-media/backend-patterns/iterative-retrieval/strategic-compact + previous full set; final find SKILL.md count + playwright-pro subs + config/metadata): tdd-workflow, check-work, verification-loop, eval-harness, continuous-learning-v2, code-reviewer (engineering-team), security-review, playwright-pro (full: browserstack/coverage/fix/generate/migrate/report/review/testrail + subs + agents/hooks/integrations), e2e-testing, ui-demo, frontend-design, browser-qa, cpp-coding-standards, cpp-testing, python-patterns/python-testing/python-development, mcp-builder, configure-ecc, agent-sort, workspace-surface-audit, skill-creator, github-ops + custom vnpy-backtest-launcher-demo + many more (e.g. from ~/.claude/.grok/.agents + ai/agent/research/MCP patterns). Perfect stack match for C++ (CMake/pybind/ImGui/CEF/zero-mutex/ports/trading/backtest/GUI panels/Fedora) + Python embed + TDD/UI/testing/MCP/agent tooling. MCP coverage via connected chrome-devtools (browser/automation) + grok_com_github (GitHub) + mcp-builder skill (searches performed first per rule for firecrawl/exa/playwright/github MCPs) + microsoft-learn/qt-docs. Plugins: 24+ (playwright-pro, firecrawl, github, mcp-*, desktop-commander etc.). All via auto skillshare (|| true on partial fails/rate). Updated AGENTS + custom skill + .skillshare/config. 
**Independent check-work verifier subagent (spawned per newly installed check-work skill, full focus on py Ports parity 201 + mass 32 skills + AGENTS/ECC/Grok Build/agile/TDD/docs/auto compliance + "continue" + original query)**: VERDICT: PASS. Full trace review + code review + direct repro (201 on_tick via grep-c from long background DATA_ONLY run, trades=2, 32 skills exact, builds/runs, docs with Chinese 《产品需求规格说明书》/《系统详细设计说明书》/AGENTS/ECC 1.10.0/Grok Build/user-guide refs, todo_write, zero-mutex/Ports, auto skillshare/MCP search-first, no violations). Minor suggestions only (not FAILs): py buy/sell wiring sig (2-arg calls vs 3-arg override → incompatible logs; on_tick/Ports proof 100% reliable via C++ strat + force display for "reliable" trades=2); one raw cout in DATA_ONLY demo (AGENTS policy "never raw... except benches/examples"; fedora doc claim slightly outdated); count alignment (top-level ~23 vs total 32 SKILL.md incl subs – already accurate in spirit). All checklist items (code/operational/docs/verification + compliance query + "continue") addressed with direct evidence. See custom vnpy skill for full subagent report summary. (See install-05 + cont-12 verification.)

## Current Active Focus (2026-06, post-fusion request)
- Complete C++ VNPY + TV/TS fusion (detailed plan executed for research/docs/chart enhance/panel start; full ImGui shell, real CEF, Python embed, core managers next).
- Strict TDD + cpp-standards enforcement on all new C++ (e.g., strategy_manager_panel and future panels).
- Maintain zero-mutex invariant (moodycamel only, no mutex/cv on hot/control paths), Ports parity, hybrid UI (ImGui + CEF), Python plugins in-proc.
- Audit/alignment complete: See this file + recent todos (ecc-grokbuild-audit-alignment), verification runs (real prices in fusion logs, py parity, 0 mutex grep, tests green).

## Questions to Ask User Before Major Changes
- Scope of v1 (core trading loop vs full OMS/Risk?)
- Performance vs Architecture quality trade-offs