# NTC Thermistor Temperature Sensor based Project

This project shows how to interface an **NTC thermistor** with an ESP32 using a simple voltage divider circuit. The analog readings are converted into temperature values and displayed on the Serial Monitor. Simulated on Wokwi.

## 🧰 Components

- ESP32
- NTC Thermistor
- 10kΩ Resistor
- Jumper wires
- Breadboard

## 🔗 Simulation Link

Try it on Wokwi:  
https://wokwi.com/projects/430583777158914049

## 🚀 Getting Started

1. Open `sketch.ino` in the Arduino IDE.
2. No additional libraries are required.
3. Upload the sketch to your board.
4. Use Serial Monitor to view temperature readings.

## 🖼 Diagram

See the circuit layout in `diagram.json`.

## 📝 Notes

This project uses analogRead and a basic voltage divider formula. You may need to calibrate the readings depending on your thermistor's beta value.
