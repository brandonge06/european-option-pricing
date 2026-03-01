# 💰 European Option Pricing Engine (CRR)

A high-performance financial engineering tool for pricing European Options using the **Cox-Ross-Rubinstein (CRR) Binomial Tree model**.

---

## 🛠️ Project Features
- **$O(n)$ Space Complexity**: Memory-optimized 1D array implementation.
- **Thread-Safe & Reentrant**: Pure functional C implementation with no global state.
- **Abstracted Interface**: Clean separation of option parameters and pricing logic.
- **Interactive UI**: Modern Streamlit dashboard with real-time visualizations.
- **Test Suite**: Automated unit tests for accuracy verification.

---

## 🔬 Mathematical Foundation
The CRR model provides a discrete-time approximation of the Black-Scholes continuous-time model. It assumes that at each discrete time step, the asset price can either move **Up** ($u$) or **Down** ($d$).

| Variable | Description | Contribution to Model |
| :--- | :--- | :--- |
| `spot` ($S_0$) | **Current Asset Price** | The starting point of the binomial tree. |
| `strike` ($K$) | **Exercise Price** | Used to calculate the payoff. |
| `time` ($T$) | **Years to Maturity** | Determines the horizontal distance of the tree. |
| `rate` ($r$) | **Risk-Free Rate** | The discounting factor for backward induction. |
| `volatility` ($\sigma$) | **Asset Volatility** | Determines the magnitude of 'up' and 'down' moves ($u, d$). |
| `steps` ($n$) | **Binomial Steps** | The number of time intervals. |

---

## 🏃 Getting Started

### 🖥️ CLI Mode
```bash
make clean && make
./bin/pricer 100.0 100.0 1.0 0.05 0.2 1000 c
```

### 🧪 Run Tests
```bash
make test
```

### 🌐 Web Dashboard
```bash
bash start.sh
```

---

## 🔒 Thread Safety & Reentrancy
The core engine (`calculate_european_option_price`) is designed for high-concurrency environments:
1. **No Shared State**: Does not use static variables, global locks, or external files.
2. **Local Memory Allocation**: All heap memory (`malloc`) is local to the function call and is `free`d before return.
3. **Immutable Input**: Uses `const OptionParams*` to prevent accidental modification of parameters.

### 📝 Author
Built as a professional C financial engineering tool.
