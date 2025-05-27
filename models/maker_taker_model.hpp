#pragma once

inline double estimate_market_impact(double qty_usd, double vol) {
    return 0.0008 * qty_usd * vol;  // simplified model
}
