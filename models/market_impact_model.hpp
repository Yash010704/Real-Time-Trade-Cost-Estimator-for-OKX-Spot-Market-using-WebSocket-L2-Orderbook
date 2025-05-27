#pragma once
inline double predict_maker_taker(double price, double vol, double qty_usd) {
    return 1.0 / (1.0 + exp(-(0.1 * price - 5 * vol + 0.01 * qty_usd)));  // logistic function
}
