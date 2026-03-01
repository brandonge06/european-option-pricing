# 💰 European Option Pricing Engine (CRR)

A high-performance financial engineering tool for pricing European Options using the **Cox-Ross-Rubinstein (CRR) Binomial Tree model**.

---

## 🔬 Mathematical Foundation

The CRR model provides a discrete-time approximation of the Black-Scholes continuous-time model. It assumes that at each discrete time step, the asset price can either move **Up** (u) or **Down** (d).

### 📊 Model Variables & Parameters

| Variable | Description | Contribution to Model |
| :--- | :--- | :--- |
| `spot` ($S_0$) | **Current Asset Price** | The starting point of the binomial tree. |
| `strike` ($K$) | **Exercise Price** | Used to calculate the payoff: $\max(S_T - K, 0)$ for calls. |
| `time` ($T$) | **Years to Maturity** | Determines the total horizontal distance of the tree. |
| `rate` ($r$) | **Risk-Free Rate** | The discounting factor for backward induction. |
| `volatility` ($\sigma$) | **Asset Volatility** | Determines the magnitude of 'up' and 'down' moves ($u, d$). |
| `steps` ($n$) | **Binomial Steps** | The number of time intervals. More steps = higher precision. |
| `dt` ($\Delta t$) | **Time Increment** | $\Delta t = T / n$. The duration of each binomial step. |
| `u`, `d` | **Price Factors** | $u = e^{\sigma \sqrt{\Delta t}}$, $d = 1/u$. Defines price movement. |
| `p` | **Risk-Neutral Prob.** | $p = \frac{e^{r\Delta t} - d}{u - d}$. The probability of an up move. |

---

## 🚀 Efficiency & Space Optimization

Traditional binomial tree models store the entire tree structure in a 2D matrix, requiring **$O(n^2)$** memory.

This implementation uses **Dynamic Programming with 1D Array Optimization**:
1.  **Memory:** We only allocate an array of size $(n+1)$.
2.  **In-place Updates:** During backward induction (stepping from maturity back to time zero), we overwrite the array with the new discounted expected values.
3.  **Complexity:** This reduces space complexity to **$O(n)$**, making it significantly more efficient for large numbers of steps (e.g., $n=10,000+$).

---

## 🛠️ Project Structure

- **`include/option_pricing.h`**: Struct definitions and function signatures.
- **`src/option_pricing.c`**: Core engine implementation (C).
- **`src/main.c`**: Command-line interface for the pricer.
- **`app.py`**: Streamlit-based interactive web dashboard with Plotly visualization.
- **`start.sh`**: Automated setup and launch script.

---

## 🏃 Getting Started

### 🖥️ CLI Mode (Developers)
```bash
make clean && make
./bin/pricer 100.0 105.0 1.0 0.05 0.2 1000 c
```

### 🌐 Web Dashboard (User Friendly)
```bash
bash start.sh
```
This script will:
1. Compile the C backend.
2. Set up a Python virtual environment.
3. Install Streamlit and Plotly.
4. Launch the dashboard in your browser.

---

### 📝 Author
Built as a high-performance C project with a modern Python interface.
