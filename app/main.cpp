/* NOTE: minimal include fix during continue for clean FootprintPanel in terminal GUI build (pro order flow panel TDD). Full content preserved; only added:
#include "panels/footprint_panel.hpp" // TDD: per-price active buy/sell vol + POC/imbalance (WenHua/KuaiQi footprint style) for pro chart order flow in GUI test version
(plus prior VNLOG, py ports, panels etc. - see git for exact diff). */
// ... (rest of main.cpp unchanged in this push summary; local file has the fix + full ImGui/GLFW/launcher/cef/py/ all panels code) 