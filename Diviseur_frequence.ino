#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <U8g2lib.h>
//Tout d'abord, connectez les broches de l'écran OLED aux broches appropriées 
// Vous devrez connecter les broches VCC et GND de l'écran OLE

#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_RST 16
U8G2_SSD1306_128X64_NONAME_F_SW_I2C display(U8G2_R0, OLED_SCL, OLED_SDA, OLED_RST);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Afficher le message 
  display.clearBuffer();
  display.setFont(u8g2_font_helvR10_tf);
  display.setCursor(0, 20);
  display.print("Message: ");
  display.setCursor(0, 40);
  display.write(payload, length);
  display.sendBuffer();
}

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("binome4")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic","hello world");
      // ... and resubscribe
      client.subscribe("binome_4");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);

  // Initialize the OLED display
  display.begin();

  
  client.setServer("test.mosquitto.org", 1883);
  client.setCallback(callback);

   WiFi.begin("PlanetCampus - Prive 000359", "2D9S3B9g2h32Y");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
