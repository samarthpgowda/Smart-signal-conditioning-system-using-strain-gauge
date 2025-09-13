const int loadCellPin = A0;        // Analog pin connected to AD620 output
float calibrationFactor = 0.005;   // Set this based on your calibration
float offset = 0;                  // Will be set at startup for zero weight

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Initializing...");

  // Auto-zeroing (tare) at startup
  float sum = 0;
  for (int i = 0; i < 100; i++) {
    sum += analogRead(loadCellPin);
    delay(10);
  }
  offset = sum / 100.0;

  Serial.print("Zero offset (ADC units): ");
  Serial.println(offset);
  Serial.println("Ready to measure weight...");
}

void loop() {
  int rawValue = analogRead(loadCellPin);
  float voltage = (rawValue / 1023.0) * 5.0; // Convert ADC to voltage (0–5V)
  float adjustedValue = rawValue - offset;

  // Convert to weight in kilograms
  float weightKg = adjustedValue * calibrationFactor;

  // Print voltage and weight
  Serial.print("Voltage: ");
  Serial.print(voltage, 3); // 3 decimal places
  Serial.print(" V | ");

  if (weightKg > 0.05) {
    Serial.print("Weight: ");
    Serial.print(weightKg, 2); // 2 decimal places
    Serial.println(" kg");
  } else {
    Serial.println("No weight detected");
  }

  delay(500);
}
