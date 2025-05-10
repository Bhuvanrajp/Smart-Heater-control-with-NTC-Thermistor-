#include <LiquidCrystal_I2C.h>

#define TEMP_PIN 34    
#define HEATER_PIN 5   
#define BUZZER_PIN 18    

LiquidCrystal_I2C lcd(0x27, 16, 2);

enum State {
  IDLE,
  HEATING,
  STABILIZING,
  TARGET_REACHED,
  OVERHEAT
};

State currentState = IDLE;

const float minTemp = 25.0;
const float targetTemp = 30.0;
const float tempSensorMin = 0.0; 
const float tempSensorMax = 1023.0; 
const float voltageMax = 5.0;     

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

float readTemperature() {
  int sensorValue = analogRead(TEMP_PIN);
  float temperature = map(sensorValue, 0 , 4095.0, 800, -240) / 10.0; // Adjust based on your NTC sensor's characteristics
  return temperature;
}

void loop() {
  float temp = readTemperature();
  Serial.println(temp);

  switch (currentState) {
    case IDLE:
      digitalWrite(HEATER_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      if (temp < minTemp) currentState = HEATING;
      break;

    case HEATING:
      digitalWrite(HEATER_PIN, HIGH);
      digitalWrite(BUZZER_PIN, LOW);
      if (temp >= minTemp + 2) currentState = STABILIZING;
      break;

    case STABILIZING:
      digitalWrite(HEATER_PIN, HIGH);
      digitalWrite(BUZZER_PIN, LOW);
      if (temp >= targetTemp) currentState = TARGET_REACHED;
      break;

    case TARGET_REACHED:
      digitalWrite(HEATER_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      if (temp > targetTemp + 2) currentState = OVERHEAT;
      else if (temp < minTemp) currentState = HEATING;
      break;

    case OVERHEAT:
      digitalWrite(HEATER_PIN, LOW);
      digitalWrite(BUZZER_PIN, HIGH);
      if (temp <= targetTemp) currentState = TARGET_REACHED;
      break;
  }

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C   ");

  lcd.setCursor(0, 1);
  switch (currentState) {
    case IDLE: lcd.print("State: IDLE       "); break;
    case HEATING: lcd.print("State: HEATING    "); break;
    case STABILIZING: lcd.print("State: STABILIZNG "); break;
    case TARGET_REACHED: lcd.print("State: TARGET OK  "); break;
    case OVERHEAT: lcd.print("State: OVERHEAT!  "); break;
  }

  delay(1000);
}