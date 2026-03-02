# European Option Pricing Engine

A high-performance financial engineering tool for pricing European Options using the **Cox-Ross-Rubinstein (CRR) Binomial Tree model**, implemented in **Python** with **NumPy** for optimized vectorized calculations.

---

## 🏗️ Project Architecture
- **Engine:** Python using **NumPy** for vectorized binomial calculations.
- **Optimization:** $O(n)$ space complexity via in-place array updates.
- **Frontend:** Streamlit + Plotly for interactive visualization.
- **Performance:** Leverages NumPy's underlying C-based array operations for fast simulation results.

---

## 🔬 Mathematical Foundation

The CRR model provides a discrete-time approximation of the Black-Scholes continuous-time model. It assumes that at each discrete time step, the asset price can either move **Up** ($u$) or **Down** ($d$).

| Variable | Description | Contribution to Model |
| :--- | :--- | :--- |
| `spot` ($S_0$) | **Current Asset Price** | The starting point of the binomial tree. |
| `strike` ($K$) | **Exercise Price** | Used to calculate the payoff: $\max(S_T - K, 0)$ for calls. |
| `time` ($T$) | **Years to Maturity** | Determines the total horizontal distance of the tree. |
| `rate` ($r$) | **Risk-Free Rate** | The discounting factor for backward induction. |
| `volatility` ($\sigma$) | **Asset Volatility** | Determines the magnitude of 'up' and 'down' moves ($u, d$). |
| `steps` ($n$) | **Binomial Steps** | The number of time intervals. More steps = higher precision. |

---

## 🚀 Running the Project

To run the interactive web interface (requires Python 3.9+):

```bash
cd european-option-pricing
bash start.sh
```

### 🧪 Run Tests (Manually)
To run the `unittest` suite directly:
```bash
export PYTHONPATH=$PYTHONPATH:.
python3 src/tests.py
```

---

### 📝 Author
Built as a professional financial engineering tool.
