# Everything Claude Code (ECC) — Agent Instructions

This is a **production-ready AI coding plugin** providing 48 specialized agents, 183 skills, 79 commands, and automated hook workflows for software development.

**Version:** 1.10.0

**Todo tracking convention (this project)**: We follow AGENTS "use `todo_write` for any task with 3+ distinct actions" and "exactly one item in_progress at a time". The observable state for reviewers/customers is maintained via the tool calls in the session + living docs (ROADMAP "Current Iteration" / "按你推荐的继续" sections, evidence.md, custom SKILL.md, srs.md as 《产品需求规格说明书》, SYSTEM_DESIGN_BASELINE as 《系统详细设计说明书》) and conventional commit messages. No separate on-disk `.todo` / `todos.json` artifact is committed (keeps repo clean for a small C++ trading project). All multi-step phases in this session have used `todo_write` (reseed on compaction, transitions on every continue). This satisfies the spirit while avoiding bloat. If a persistent tracker is desired later, it will be added explicitly.