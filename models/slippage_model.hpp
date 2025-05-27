#pragma once
inline double estimate_slippage(double price, double qty_usd) {
    return 0.0005 * qty_usd;  // example: 0.05% slippage
}
