from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
import serial
import time
import json

app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # Allow all for development
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Update COM port as needed (e.g., /dev/ttyUSB0 on Linux/Mac)
ser = serial.Serial("COM8", 9600)
time.sleep(2)

def send_command(cmd: str):
    ser.write((cmd + "\n").encode())
    response = ser.readline().decode().strip()
    return response

@app.post("/led/{led_id}/{state}")
def control_led(led_id: int, state: str):
    return {"result": send_command(f"led{led_id}_{state}")}

@app.post("/buzzer/{state}")
def control_buzzer(state: str):
    return {"result": send_command(f"buzzer_{state}")}

@app.get("/ultrasonic")
def get_distance():
    return {"distance_cm": send_command("ultrasonic?")}

@app.get("/ldr")
def get_ldr():
    return {"ldr_value": send_command("ldr?")}

@app.get("/sensors")
def get_all_sensor_data():
    line = send_command("get_data")
    try:
        return json.loads(line)
    except json.JSONDecodeError:
        return {"error": "Invalid JSON from Arduino", "raw": line}
