#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define TOKEN "BBUS-W9zmpcKC8zXkW1J8NKmAjKQuMkkWd1"
#define WIFISSID "vivo T2x 5G"
#define PASSWORD "123456789"
#define ID_IN "65f13d1b12ae03315df0a014"
#define ID_OUT "65f13df65be8f02ff45eec2b"
#define ID_NOW "65f13df65be8f02ff45eec2b"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define IR_SENSOR_IN 2   // Replace with your actual pin for the infrared sensor for IN
#define IR_SENSOR_OUT 32 // Replace with your actual pin for the infrared sensor for OUT
#define relay 18
#define LED_PIN 13       // Pin for the LED
int lastInStatus = LOW;   // Previous status of the IN sensor
int lastOutStatus = LOW;  // Previous status of the OUT sensor
int countin = 0; 
int countout = 0;
void sendValueToUbidots(const char *variableId, double value)
{
  WiFiClient client;
  if (client.connect("things.ubidots.com", 80))
  {
    String data = "POST /api/v1.6/devices/your-device-label HTTP/1.1";
    data += "\nContent-Type: application/json";
    data += "\nX-Auth-Token: " + String(TOKEN);
    data += "\nConnection: close";
    data += "\nHost: things.ubidots.com";
    // Convert double to string and get the length
    String valueStr = String(value);
    int contentLength = valueStr.length();
    data += "\nContent-Length: ";
    data += contentLength;
    data += "\n\n{\"";
    data += variableId;
    data += "\":";
    data += valueStr; // Use the string representation of the double value
    data += "}";
    client.print(data);
    delay(500);
  }
  client.stop();
}
void setup()
{
  Serial.begin(115200);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  pinMode(LED_PIN, OUTPUT); // Initialize LED pin as output
  pinMode(IR_SENSOR_IN, INPUT);
  pinMode(IR_SENSOR_OUT, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
  Serial.println("Visitor Counter Demo");
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15, 20);
  display.println("   Lights off");
  display.setCursor(15, 40);
  display.println("No current visitor");
  display.display();
  delay(3000);
}
void loop()
{
  int inStatus = digitalRead(IR_SENSOR_IN);
  int outStatus = digitalRead(IR_SENSOR_OUT);
  if (inStatus != lastInStatus)
  {
    if (inStatus == HIGH)
    {
      countin++;
    }
    lastInStatus = inStatus;
  }
  if (outStatus != lastOutStatus)
  {
    if (outStatus == HIGH && countout < countin) // Ensure countout doesn't exceed countin
    {
      countout++;
    }
    lastOutStatus = outStatus;
  }
  int now = countin - countout;
  if (now <= 0)
  {
    digitalWrite(relay, HIGH);
    digitalWrite(LED_PIN, LOW); // Turn off LED when no visitors
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(15, 20);
    display.println("   Lights off");
    display.setCursor(15, 40);
    display.println("No current visitor");
    display.display();
  }
  else
  {
    digitalWrite(relay, LOW);
    digitalWrite(LED_PIN, HIGH); // Turn on LED when there are visitors
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(15, 20);
    display.print("Current Visitor: ");
    display.println(now);

    // Display IN and OUT counts only when there are visitors
    display.setTextSize(1);
    display.setCursor(15, 40);
    display.print("IN: ");
    display.print(countin);
    display.setCursor(80, 40);
    display.print("OUT: ");
    display.print(countout);
    display.display();
  }

  Serial.print("Current Visitor: ");
  Serial.println(now);

  // Send data to Ubidots
  sendValueToUbidots(ID_IN, countin);
  sendValueToUbidots(ID_OUT, countout);
  sendValueToUbidots(ID_NOW, now);

  delay(1000);
}