#include <MCP39F521.h>
#include <Wire.h>

#define SLOW_DOWN_FACTOR 3

int led = 13;

UpbeatLabs_MCP39F521 MCP39F521 = UpbeatLabs_MCP39F521();

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  MCP39F521.begin();
}

void loop() {
  UpbeatLabs_MCP39F521_Data data;
  UpbeatLabs_MCP39F521_FormattedData fData;

  int readMCPretval = MCP39F521.read(&data, NULL);
  if (readMCPretval == UpbeatLabs_MCP39F521::SUCCESS) {
    // Print stuff out
    Serial.write("\x1B" "c"); // Clear the screen on a regular terminal
    MCP39F521.convertRawData(&data, &fData);
    printMCP39F521Data(&fData);
  } else {
    Serial.print("Error returned! "); Serial.println(readMCPretval);
  }

  delay(1000);
}

void zcd() {
  static int state = HIGH;
  static int numInterrupts = 0;
  digitalWrite(led, state);
  numInterrupts++;
  numInterrupts = numInterrupts % SLOW_DOWN_FACTOR;
  if (numInterrupts == (SLOW_DOWN_FACTOR - 1)) {
    state = !state;
  }
}

void printMCP39F521Data(UpbeatLabs_MCP39F521_FormattedData *data)
{
  Serial.print(F("Voltage = ")); Serial.println(data->voltageRMS, 4);
  Serial.print(F("Current = ")); Serial.println(data->currentRMS, 4);
  Serial.print(F("Line Frequency = ")); Serial.println(data->lineFrequency, 4);
  Serial.print("Analog Input Voltage = "); Serial.println(data->analogInputVoltage, 4);
  Serial.print(F("Power Factor = ")); Serial.println(data->powerFactor, 4);
  Serial.print(F("Active Power = ")); Serial.println(data->activePower, 4);
  Serial.print(F("Reactive Power = ")); Serial.println(data->reactivePower, 4);
  Serial.print(F("Apparent Power = ")); Serial.println(data->apparentPower, 4);
}
