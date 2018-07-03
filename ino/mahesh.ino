#include <ESP8266WiFi.h>
#include <PubSubClient.h>


// built in LED to show activity
#define led 13

const char* ssid     = "FamilyJunction-T";
const char* password = "92883697";
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
String sensor_input;
char msg[50];

//String doSensorReading(String sType){
//  String returnString = "";
//  float h = dht.readHumidity();       //Read Humidity
//  float t = dht.readTemperature();    //Read Temperature
//  char cHumidity[7];                  //Create char for Humidity legnth 7
//  char cTemperature[8];               //Create char for Temperature legnth 8
//  String Humidity, Temperature;       //Define finale varable temperature and Humidity
//  dtostrf(h,6,1, cHumidity);          //Load raw humidity and chop to one decimal loading back into cHumidity
//  dtostrf(t,6,1, cTemperature);       //Load raw humidity and chop to one decimalloading back to cTemperature
//  Humidity = String(cHumidity); //Load cHumidity into its relevent char Humidity
//  Temperature = String(cTemperature);//Load cTemperature into its relevent char Temperature
//  //Responses from whats asked on IP address
//  if (sType == "")returnString = "Humidity: " + Humidity +" Temperature: " + Temperature;
//  if (sType == "Temperature")returnString = Temperature;
//  if (sType == "Humidity")returnString = Humidity;
//  return returnString;
//}

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level)
    digitalWrite(D7, HIGH);
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
    digitalWrite(D7, LOW);
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "maddy-1234567";
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("esp-test-check");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(D7, OUTPUT);
  digitalWrite(D7, HIGH);
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  reconnect();
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
//    sensor_input = doSensorReading("");
//    snprintf (msg, 75, "%s", sensor_input.c_str());
//    Serial.print("Publish message: ");
//    Serial.println(msg);
//    client.publish("sensor-data", msg);
  }
}
