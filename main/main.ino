#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SENSOR_PIN A0   // ADC pin for soil moisture sensor
#define SDA_PIN    D2   // SDA pin for I2C communication
#define SCL_PIN    D1   // SCL pin for I2C communication
#define OLED_RESET -1    // Reset pin (or -1 if not used)

// Initialize I2C for OLED display
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize I2C
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize OLED display
  if(!display.begin()) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.display();  // Clear the display buffer
  display.display();  // Display the content
  delay(2000);        // Pause for 2 seconds
}

void loop() {
  Serial.println("Entro");

  // Read soil moisture
  float moisture = readSoilMoisture();

  // Display on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Soil Moisture:");
  display.setCursor(0, 20);
  display.print(moisture);
  display.println("%");
  display.display();

  // Wait for a moment before the next reading
  delay(5000);
}

float readSoilMoisture() {
  // Read analog value from soil moisture sensor
  int sensorValue = analogRead(SENSOR_PIN);

  // Map the analog value to a percentage (adjust as needed based on sensor characteristics)
  float moisturePercentage = map(sensorValue, 0, 1023, 0, 100);
  moisturePercentage = constrain(moisturePercentage, 0, 100);  // Ensure the value is between 0 and 100

  return moisturePercentage;
}
