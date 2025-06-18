# Arduino_to_Website_Communication  
### Frontend ↔ FastAPI Backend (Uvicorn) ↔ Arduino

This project establishes real-time communication between a web frontend, a FastAPI backend (served via **Uvicorn**), and an **Arduino** device over a serial connection. It enables you to send commands from a browser to the Arduino and receive responses back.

---

## Project Structure

```

.
├── Frontend.html                       # Single-page frontend (HTML, CSS, JavaScript)
├── Backend.py                          # FastAPI backend using Uvicorn
├── backend_coms\backend_coms.ino       # Arduino sketch
├── requirements.txt                    # Python dependencies
└── README.md                           # This file

```

---

## Features

- **Frontend**: Minimal UI to send commands and view Arduino responses.
- **Backend**: FastAPI app that bridges HTTP requests to the serial port.
- **Arduino**: Receives serial commands, processes them, and replies.

---

## Getting Started

### 1. Arduino Setup

- Load `arduino_code.ino` to your Arduino using the Arduino IDE.

---

### 2. Backend (FastAPI with Uvicorn)

#### Install Dependencies

```bash
pip install -r requirements.txt
```

#### Run the Backend Server

```bash
uvicorn backend:app --reload
```

* This starts the server at: `http://127.0.0.1:8000`
* Make sure to specify the correct serial port in `backend.py`

---

### 3. Frontend Setup

* Open `frontend.html` in a browser.
* This page will POST commands to the FastAPI server and display Arduino's response.

---

## How It Works

1. **User** inputs command in the web UI.
2. **Frontend** sends POST request to FastAPI at `/send`.
3. **Backend** writes the command to Arduino via `pyserial`.
4. **Arduino** processes and replies through serial.
5. **Backend** reads the response and sends it back to the frontend.
6. **Frontend** displays the response.

---

## Changes to be made in backend

```python

# Configure your serial port

ser = serial.Serial('COM3', 9600, timeout=1)  # Update as needed

```

---

## Troubleshooting

* **Serial Port Error**: Make sure the Arduino is connected and not used by another app (like the Arduino IDE).
* **CORS Blocked**: Use `Live Server` or enable CORS in FastAPI as shown above.
* **No Response**: Check `baud rate` and `timeout`, or add `Serial.flush()` to the Arduino code.

---

## License

MIT License © 2025


