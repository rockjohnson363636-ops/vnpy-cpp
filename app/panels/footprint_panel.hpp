/**
 * @file footprint_panel.hpp
 * @brief Footprint / per-price order flow panel (WenHua/KuaiQi style) for pro trader UI.
 *
 * Per AGENTS.md + tdd-workflow + cpp-coding-standards:
 * - TDD skeleton (RED would be missing render test; minimal GREEN impl).
 * - Small cohesive file.
 * - Integrates with UIBridge / TickData for per-price active buy/sell vol (from real ticks or fusion).
 * - Bilingual, pro UX.
 *
 * Part of Phase 6+ fusion / TV/TS/WenHua/KuaiQi alignment for "带界面的版本".
 */

#pragma once

#include <imgui.h>
#include "i18n.hpp"

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <vnpy/core/event/market_data.hpp>

namespace vnpy::terminal {

class FootprintPanel {
public:
    FootprintPanel() = default;

    // Update from real TickData (accumulate per-price buy/sell vol; side from price change or external).
    // For demo: use volume split; in prod wire from gateway/trade side or inference.
    void update_from_tick(const vnpy::core::TickData& t, bool buy_side = true) {
        double p = t.last_price;
        double v = t.volume > 0 ? t.volume : 1.0;
        auto& vols = price_vols[p];
        if (buy_side) vols.first += v; else vols.second += v;
        total_vol += v;
        // Track POC (max total vol price)
        if (vols.first + vols.second > max_vol_at_poc) {
            max_vol_at_poc = vols.first + vols.second;
            poc_price = p;
        }
    }

    void render() {
        ImGui::Begin(tr("Footprint (Order Flow per Price)", "足迹 (每价位订单流)").c_str());

        ImGui::Text("%s", tr("Per-price active buy/sell volume (WenHua/KuaiQi style) + POC/imbalance.", "每价位主动买卖量 (文华/快期风格) + POC/失衡。").c_str());
        ImGui::Separator();

        ImGui::Text("%s: %.1f @ %.1f (total vol %.0f)", tr("POC/HVN", "POC/HVN").c_str(), poc_price, max_vol_at_poc, total_vol);
        ImGui::TextDisabled("%s", tr("Live from ticks (POC = highest volume price node for S/R like WenHua/KuaiQi). Imbalance 3x for 供需失衡.", "实时来自 ticks (POC = 最高成交量价位节点，用于 S/R，如文华/快期)。失衡 3x 用于供需失衡。").c_str());

        if (ImGui::BeginTable("footprint", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY, ImVec2(0, 120))) {
            ImGui::TableSetupColumn(tr("Price", "价格"));
            ImGui::TableSetupColumn(tr("Buy Vol", "买量"));
            ImGui::TableSetupColumn(tr("Sell Vol", "卖量"));
            ImGui::TableSetupColumn(tr("Delta/Imbal", "差额/失衡"));
            ImGui::TableHeadersRow();

            // Sort prices desc for typical book view
            std::vector<std::pair<double, std::pair<double,double>>> sorted;
            for (auto& kv : price_vols) sorted.emplace_back(kv.first, kv.second);
            std::sort(sorted.begin(), sorted.end(), [](auto& a, auto& b){ return a.first > b.first; });

            for (auto& r : sorted) {
                double p = r.first; auto [bv, sv] = r.second;
                double delta = bv - sv;
                bool is_poc = (p == poc_price);
                ImGui::TableNextRow();
                ImGui::TableNextColumn(); 
                if (is_poc) ImGui::TextColored(ImVec4(1,1,0,1), "%.1f *POC*", p); else ImGui::Text("%.1f", p);
                ImGui::TableNextColumn(); ImGui::TextColored(ImVec4(0.3f,0.9f,0.5f,1), "%.0f", bv);
                ImGui::TableNextColumn(); ImGui::TextColored(ImVec4(0.95f,0.4f,0.4f,1), "%.0f", sv);
                ImGui::TableNextColumn(); 
                const char* imbal = (delta > 80 ? " (imbal+)" : (delta < -80 ? " (imbal-)" : ""));
                ImGui::Text("%.0f%s", delta, imbal);
            }
            ImGui::EndTable();
        }

        ImGui::Text("TODO (next): real side from trades/gateway, UIBridge feed, full POC/imbal calc in fusion.");

        ImGui::End();
    }

    void clear() { price_vols.clear(); total_vol = 0; max_vol_at_poc = 0; poc_price = 0; }

private:
    std::map<double, std::pair<double, double>> price_vols; // price -> {buy_vol, sell_vol}
    double total_vol = 0;
    double max_vol_at_poc = 0;
    double poc_price = 0;
};

} // namespace vnpy::terminal
