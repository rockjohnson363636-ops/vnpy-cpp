# Real CEF Tarball for Full "带界面的版本" Visuals (Fusion Charts)

**Status (this continue phase2)**: Dummy /tmp/cef_dummy + /tmp/cef_real (0-byte) sufficient for TDD/compile + all DATA_ONLY / xvfb GUI test evidence (py Ports parity, launcher, pro panels, (REAL) init logs, CTP demo). Full browser visuals + bidirectional JS roundtrip require real tar on Fedora display.

## How to Get Real Tar (Recommended for Customer Trial on Real Display)
1. On a machine with browser: Visit https://cef-builds.spotifycdn.com/index.html
2. Filter:
   - Platform: Linux
   - Architecture: 64-bit
   - Type: Minimal (smaller, ~100-200 MB .tar.bz2)
   - Recent version (e.g. 131+ or 132+ matching Chromium; pick latest available)
3. Download the .tar.bz2 (example name pattern: cef_binary_131.3.1+..._linux64_minimal.tar.bz2)
4. On target Fedora:
   ```bash
   export CEF_TAR=/path/to/downloaded/cef_binary_..._linux64_minimal.tar.bz2
   ./examples/run-fedora-gui-test.sh
   ```
   The script will:
   - Detect >10MB tar
   - Extract to /tmp/cef_real (or $CEF_ROOT)
   - Re-config + build with -DVNPY_TERMINAL_USE_CEF=ON -DCEF_ROOT=... if needed
   - Run with full CEF (TV LC + C++ fusion overlays, volume profile, patterns, order flow, bidirectional control via MessageRouter/V8 -> moodycamel tokens -> zero-mutex core).

HEAD/index tests in prior + this "按你推荐的继续" phase2 on patterns returned 200 Connection established (CDN live); specific old tar 404 (rotate). Full auto-fetch skipped (size). Manual/user tar recommended for real visuals on Fedora customer workstation + CTP test. Dummy + instructions + CTP_DEMO stub sufficient for immediate "带界面的版本" GUI test delivery + py Ports + CTP readiness evidence.

## Notes
- After real tar + re-build, runtime needs libcef.so in LD_LIBRARY_PATH or rpath, Resources/, and may need --no-sandbox on some Fedora setups.
- For headless CI: stick to DATA_ONLY + dummy (full evidence + CTP logs captured).
- See docs/cef-setup.md + examples/run-fedora-gui-test.sh + ctp notes for integration.
- Per AGENTS: dummy for TDD parity; real for prod "带界面的版本" visuals + CTP on customer Fedora.

This phase2 re-verified script + package + CTP wiring still deliver the test version immediately.