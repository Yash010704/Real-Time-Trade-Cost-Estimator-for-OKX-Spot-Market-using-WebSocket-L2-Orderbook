#include "websocket.hpp"
#include "models/slippage_model.hpp"
#include "models/fee_model.hpp"
#include "models/market_impact_model.hpp"
#include "models/maker_taker_model.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <chrono>

using json = nlohmann::json;

int main() {
    WebSocketClient ws;

    ws.connect("wss://ws.gomarket-cpp.goquant.io/ws/l2-orderbook/okx/BTC-USDT-SWAP");
    ws.on_message([](const std::string& msg) {
        auto start = std::chrono::high_resolution_clock::now();

        // Parse JSON
        auto j = json::parse(msg);
        double best_bid = std::stod(j["bids"][0][0].get<std::string>());
        double best_ask = std::stod(j["asks"][0][0].get<std::string>());
        double mid_price = (best_bid + best_ask) / 2.0;

        double quantity_usd = 100.0;
        double volatility = 0.02;  // Example
        std::string fee_tier = "standard";

        double slippage = estimate_slippage(mid_price, quantity_usd);
        double fee = estimate_fee(quantity_usd, fee_tier);
        double impact = estimate_market_impact(quantity_usd, volatility);
        double net_cost = slippage + fee + impact;
        double maker_taker_ratio = predict_maker_taker(mid_price, volatility, quantity_usd);

        auto end = std::chrono::high_resolution_clock::now();
        auto latency = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // Output results
        std::cout << "Mid Price: " << mid_price << "\n";
        std::cout << "Slippage: $" << slippage << "\n";
        std::cout << "Fee: $" << fee << "\n";
        std::cout << "Market Impact: $" << impact << "\n";
        std::cout << "Net Cost: $" << net_cost << "\n";
        std::cout << "Maker/Taker Proportion: " << maker_taker_ratio << "\n";
        std::cout << "Internal Latency: " << latency << " us\n\n";
    });

    ws.run();
    return 0;
}
