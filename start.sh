#!/bin/bash

# 1. Check for Python 3
if ! command -v python3 &> /dev/null; then
    echo "Error: python3 could not be found. Please install Python 3."
    exit 1
fi

# 2. Set up a Virtual Environment
echo "--- Setting up Virtual Environment (venv) ---"
if [ ! -d "venv" ]; then
    python3 -m venv venv
fi
source venv/bin/activate

# 3. Install/Update pip and dependencies
echo "--- Installing/Updating Python Dependencies ---"
pip install --upgrade pip --quiet
pip install -r requirements.txt --quiet

# 4. Run Tests
echo "--- Running Engine Tests ---"
python3 src/tests.py

# 5. Launch the dashboard
if [ $? -eq 0 ]; then
    echo "--- Launching Web Dashboard ---"
    echo "You can view the dashboard at: http://localhost:8501"
    streamlit run app.py
else
    echo "Tests failed. Dashboard launch cancelled."
fi
