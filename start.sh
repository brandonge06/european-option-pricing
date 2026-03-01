#!/bin/bash

# 1. Compile the C engine
echo "--- Compiling C Engine ---"
make clean && make

# 2. Check for Python 3
if ! command -v python3 &> /dev/null; then
    echo "Error: python3 could not be found. Please install Python 3."
    exit 1
fi

# 3. Set up a Virtual Environment
echo "--- Setting up Virtual Environment (venv) ---"
python3 -m venv venv
source venv/bin/activate

# 4. Install/Update pip and dependencies
echo "--- Installing Python Dependencies ---"
pip install --upgrade pip --quiet
pip install -r requirements.txt --quiet

# 5. Launch the dashboard
echo "--- Launching Web Dashboard ---"
echo "You can view the dashboard at: http://localhost:8501"
streamlit run app.py
