#include <Arduino.h>
#include <DS1621.h>

DS1621 thermometer;

static void reportStatus(const char *operation, DS1621::Status status)
{
  if (status != DS1621::OK)
  {
    Serial.print(operation);
    Serial.print(" failed: ");
    Serial.println(thermometer.statusMessage(status));
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
  }

  DS1621::Status status = thermometer.begin();
  reportStatus("Thermometer begin", status);
}

void loop() {
  DS1621::Status status = thermometer.startConversion();
  reportStatus("Start conversion", status);

  if (status == DS1621::OK)
  {
    delay(750);

    float temperatureC = 0.0f;
    status = thermometer.readTemperatureC(temperatureC);
    if (status == DS1621::OK)
    {
      Serial.print("Temperature: ");
      Serial.print(temperatureC, 2);
      Serial.println(" C");
    }
    else
    {
      reportStatus("Read temperature", status);
    }
  }

  delay(1000);
}