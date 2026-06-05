vnpy-cpp

High-performance C++ port of VeighNa (VNPY) trading framework.

Features:
- ImGui native UI with docking, pro trader panels (order book, tape, watchlist, risk, launcher, etc.)
- CEF for TradingView Lightweight Charts with fusion (volume profile, patterns, TS overlays)
- Python strategy embedding with real on_tick via engine/Ports
- Backtesting with realistic fills, costs, Ports parity for py strategies
- Zero-mutex architecture, moodycamel queues, Ports & Adapters
- Fusion pattern detector (H&S, wedges, flags with vol)
- Bilingual (EN/ZH), premium UX (toasts, HUD, hotkeys)

See docs/ROADMAP.md, plans/, AGENTS.md for details.

Build: cmake -B build -S . -DVNPY_TERMINAL_USE_CEF=ON -DCEF_ROOT=... (or dummy)
Run: ./build/app/vnpy-terminal

Custom skill: .skillshare/skills/vnpy-backtest-launcher-demo/SKILL.md for launcher.

Auto skills/MCPs via skillshare.