#pragma once
inline double estimate_fee(double qty_usd, const std::string& tier) {
    if (tier == "standard") return 0.001 * qty_usd;
    if (tier == "vip") return 0.0005 * qty_usd;
    return 0.001 * qty_usd;  // default
}
