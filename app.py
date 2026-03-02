import streamlit as st
import pandas as pd
import plotly.express as px
from src.option_pricing import calculate_european_option_price

st.set_page_config(page_title="CRR Option Dashboard (Python)", page_icon="🐍", layout="wide")

st.title("🐍 European Option Pricing Engine (Pure Python)")

# --- Sidebar Inputs ---
st.sidebar.header("📊 Option Parameters")
option_type = st.sidebar.selectbox("Option Type", ["Call", "Put"])
spot = st.sidebar.number_input("Spot Price (S)", value=100.0, step=1.0)
strike = st.sidebar.number_input("Strike Price (K)", value=105.0, step=1.0)
time = st.sidebar.slider("Time to Maturity (Years)", 0.1, 5.0, 1.0)
rate = st.sidebar.slider("Risk-Free Rate (r)", 0.0, 0.20, 0.05)
vol = st.sidebar.slider("Volatility (σ)", 0.01, 1.0, 0.20)
steps = st.sidebar.number_input("Binomial Steps (n)", value=1000, min_value=1, step=100)

type_char = "c" if option_type == "Call" else "p"

# --- Main Dashboard ---
col1, col2 = st.columns([1, 2])

with col1:
    st.subheader("Price Result")
    # Call the native Python engine
    price = calculate_european_option_price(spot, strike, time, rate, vol, int(steps), type_char)
    
    if price >= 0:
        st.metric(label=f"Theoretical {option_type} Price", value=f"${price:.4f}")
    else:
        st.error("Error in calculation parameters.")

with col2:
    st.subheader(f"Sensitivity: {option_type} Price vs. Spot Price")
    # Generate range of spot prices for plotting
    spots = [spot * (0.5 + 0.05 * i) for i in range(21)]
    prices = [calculate_european_option_price(s, strike, time, rate, vol, int(steps), type_char) for s in spots]
    
    df = pd.DataFrame({"Spot Price": spots, "Option Price": prices})
    fig = px.line(df, x="Spot Price", y="Option Price", 
                 title=f"Payoff Curve (K={strike})",
                 labels={"Spot Price": "Underlying Asset Price", "Option Price": "Option Premium"})
    st.plotly_chart(fig, use_container_width=True)

st.divider()
st.markdown("""
### 🏗️ Technical Architecture (Updated to Pure Python)
- **Engine:** Pure Python using **NumPy** for vectorized binomial calculations.
- **Optimization:** $O(n)$ space complexity via in-place array updates.
- **Performance:** Replaces the C backend with high-performance vectorized Python, eliminating compilation steps.
- **Frontend:** Streamlit + Plotly for interactive visualization.
""")
