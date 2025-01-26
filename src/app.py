from flask import Flask, jsonify, render_template
import serial
import time

app = Flask(__name__)

# Store the latest GPS data
latest_data = {"lat": None, "lon": None}

# Serial port configuration

SERIAL_PORT = "/dev/cu.usbserial-0001"  # Replace with your actual port (e.g., "COM3" on Windows)
BAUD_RATE = 9600  # Adjust based on your GPS module's baud rate

# Serial connection setup
try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"Connected to {SERIAL_PORT} at {BAUD_RATE} baud.")
except serial.SerialException as e:
    print(f"Error: {e}")
    ser = None

# Function to read GPS data from the serial port
def read_serial():
    global latest_data
    if ser:
        line = ser.readline().decode('utf-8').strip()
        print(f"Raw data received: {line}")
        if line.startswith("Received data:"):  # Check if the data starts with the unwanted prefix
            # Remove the "Received data: " part and split the remaining string into latitude and longitude
            try:
                data = line.replace("Received data:", "").strip()  # Remove the prefix and any extra spaces
                lat, lon = data.split(",")  # Assuming the format is "latitude,longitude"
                latest_data['lat'] = float(lat)
                latest_data['lon'] = float(lon)
                print(f"Processed Data: Latitude={lat}, Longitude={lon}")  # Display the processed data
            except ValueError:
                print("Invalid data format received.")


@app.route('/')
def index():
    return render_template('index.html')

@app.route('/dashboard')
def dashboard():
    return render_template('dashboard.html')

@app.route('/get-latest-data', methods=['GET'])
def get_latest_data():
    # Call the serial reader before serving data
    read_serial()
    print(latest_data)  # Print the latest data to the terminal for debugging
    return jsonify(latest_data)

if __name__ == '__main__':
    print("Starting Flask app...")
    while True:
        read_serial()  # Continuously read serial data
        time.sleep(1)  # Adjust this delay as needed to avoid overloading
        try:
            app.run(host='0.0.0.0', port=5001, debug=False)
            break
        except KeyboardInterrupt:
            print("Shutting down...")
            if ser:
                ser.close()
            break
