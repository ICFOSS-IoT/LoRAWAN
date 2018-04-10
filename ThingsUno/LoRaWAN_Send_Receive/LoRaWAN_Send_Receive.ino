#include <TheThingsNetwork.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Set your AppEUI and AppKey
const char *devAddr = "********";
const char *nwkSKey = "********************************";
const char *appSKey = "********************************";

#define loraSerial Serial1
#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_IN865_867

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

void setup()
{
  loraSerial.begin(57600);
  debugSerial.begin(9600);

  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000)
    ;

  // Set callback for incoming messages
  ttn.onMessage(message);

  debugSerial.println("-- STATUS");
  ttn.showStatus();

  //  debugSerial.println("-- JOIN");
  //  ttn.join(appEui, appKey);
  debugSerial.println("-- PERSONALIZE");
  ttn.personalize(devAddr, nwkSKey, appSKey) ;
  pinMode(A5, OUTPUT);
  pinMode(4, OUTPUT);
  dht.begin();
}

void loop()
{
  debugSerial.println("-- LOOP");
  uint16_t humidity = dht.readHumidity(false) * 100;
  uint16_t temperature = dht.readTemperature(false) * 100;
  byte payload[4];
  payload[0] = highByte(temperature);
  payload[1] = lowByte(temperature);
  payload[2] = highByte(humidity);
  payload[3] = lowByte(humidity);

  debugSerial.print("Temperature: ");
  debugSerial.println(temperature);
  debugSerial.print("Humidity: ");
  debugSerial.println(humidity);
  ttn.sendBytes(payload, sizeof(payload));
  delay(20000);
  // Send single byte to poll for incoming messages
  ttn.poll();
  delay(20000);
}

void message(const uint8_t *payload, size_t size, port_t port)
{
  debugSerial.println("-- MESSAGE");
  debugSerial.print("Received " + String(size) + " bytes on port " + String(port) + ":");

  for (int i = 0; i < size; i++)
  {
    //debugSerial.println(payload[i]);
    debugSerial.print(" " + String(payload[i]));
    if (String(payload[i]) == "1") {
      digitalWrite(A5, HIGH);
    }
    else if (String(payload[i]) == "2") {
      digitalWrite(A5, LOW);
    }
    else if (String(payload[i]) == "3") {
      digitalWrite(4, HIGH);
    }
    else if (String(payload[i]) == "4") {
      digitalWrite(4, LOW);
    }

  }

  debugSerial.println();
}
