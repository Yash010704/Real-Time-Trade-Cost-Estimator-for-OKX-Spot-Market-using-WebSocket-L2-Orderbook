# ⚡ Real-Time Trading Simulator (C++ | OKX)

This project is a real-time trading simulator developed in C++ as part of the GoQuant recruitment challenge. It connects to a WebSocket orderbook feed from OKX, processes live L2 market data, and computes key trading metrics including slippage, fees, market impact, and latency.

---

## 🚀 Features

- Real-time WebSocket connection to OKX (mocked endpoint for development)
- Models for:
  - **Slippage estimation** (linear model)
  - **Fee estimation** (tier-based model)
  - **Market impact** (Almgren-Chriss inspired)
  - **Maker/Taker proportion** (logistic regression)
- Internal latency calculation per tick
- Modular architecture for maintainability and testing
- CLI-based (headless) — no GUI required

---

---

## 📡 WebSocket Endpoint

> **NOTE:** Accessing OKX WebSocket data may require VPN due to regional restrictions.

- WebSocket URL: `wss://ws.gomarket-cpp.goquant.io/ws/l2-orderbook/okx/BTC-USDT-SWAP`
- Sample Response:
```json
{
  "timestamp": "2025-05-04T10:39:13Z",
  "exchange": "OKX",
  "symbol": "BTC-USDT-SWAP",
  "asks": [["95445.5", "9.06"]],
  "bids": [["95445.4", "1104.23"]]
}
📊 Model Summaries
Slippage Model
cpp
Copy
Edit
return 0.0005 * quantity_usd;
Fee Model
cpp
Copy
Edit
if (tier == "standard") return 0.001 * qty;
if (tier == "vip") return 0.0005 * qty;
Market Impact Model
cpp
Copy
Edit
return 0.0008 * qty_usd * volatility;
Maker/Taker Prediction
cpp
Copy
Edit
return 1 / (1 + exp(-(0.1 * price - 5 * volatility + 0.01 * qty)));

📈 Sample Output
yaml
Copy
Edit
Mid Price: 95445.45
Slippage: $0.05
Fee: $0.10
Market Impact: $0.16
Net Cost: $0.31
Maker/Taker Proportion: 0.85
Internal Latency: 145 us
🧠 Future Improvements
Replace mocked WebSocket data with full Boost.Beast implementation

Enhance market impact model using real-time volatility estimations

Add file logging and benchmarking

Integrate SQLite or in-memory store for analytics

📜 License
MIT License — feel free to fork, clone, and improve!

🙌 Acknowledgements
OKX API Docs

Almgren & Chriss Model Reference: LinkedIn Article

