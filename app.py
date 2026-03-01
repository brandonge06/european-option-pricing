import streamlit as st
import subprocess
import os
import pandas as pd
import plotly.express as px

st.set_page_config(page_title="CRR Option Dashboard", page_icon="📈", layout="wide")

st.title("💰 European Option Pricing Engine (CRR)")

# --- Sidebar Inputs ---
st.sidebar.header("📊 Option Parameters")
option_type = st.sidebar.selectbox("Option Type", ["Call", "Put"])
spot = st.sidebar.number_input("Spot Price (S)", value=100.0, step=1.0)
strike = st.sidebar.number_input("Strike Price (K)", value=105.0, step=1.0)
time = st.sidebar.slider("Time to Maturity (Years)", 0.1, 5.0, 1.0)
rate = st.sidebar.slider("Risk-Free Rate (r)", 0.0, 0.20, 0.05)
vol = st.sidebar.slider("Volatility (σ)", 0.01, 1.0, 0.20)
steps = st.sidebar.number_input("Binomial Steps (n)", value=1000, step=100)

PRICER_PATH = "./bin/pricer"
type_char = "c" if option_type == "Call" else "p"

# --- Run the Pricing Calculation ---
def run_pricer(s, k, t, r, v, n, tc):
    if not os.path.exists(PRICER_PATH):
        return None
    cmd = [PRICER_PATH, str(s), str(k), str(t), str(r), str(v), str(n), tc]
    try:
        result = subprocess.check_output(cmd).decode().strip()
        return float(result)
    except:
        return None

# --- Main Dashboard ---
col1, col2 = st.columns([1, 2])

with col1:
    st.subheader("Price Result")
    price = run_pricer(spot, strike, time, rate, vol, steps, type_char)
    if price is not None:
        st.metric(label=f"Theoretical {option_type} Price", value=f"${price:.4f}")
    else:
        st.error("C Engine Error. Run 'make' first.")

with col2:
    st.subheader(f"Sensitivity: {option_type} Price vs. Spot Price")
    # Generate range of spot prices for plotting
    spots = [spot * (0.5 + 0.05 * i) for i in range(21)]
    prices = [run_pricer(s, strike, time, rate, vol, steps, type_char) for s in spots]
    
    df = pd.DataFrame({"Spot Price": spots, "Option Price": prices})
    fig = px.line(df, x="Spot Price", y="Option Price", 
                 title=f"Payoff Curve (K={strike})",
                 labels={"Spot Price": "Underlying Asset Price", "Option Price": "Option Premium"})
    st.plotly_chart(fig, use_container_width=True)

st.divider()
st.markdown("""
### 🏗️ Technical Architecture
- **Backend:** Pure C using the **Cox-Ross-Rubinstein** Binomial Model.
- **Optimization:** $O(n)$ space complexity using a 1D in-place array update.
- **Frontend:** Streamlit + Plotly for interactive visualization.
""")
