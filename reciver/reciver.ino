#include <ESP8266WiFi.h>
#include <espnow.h>

// Structure example to receive data
// Must match the sender structure exactly
typedef struct struct_message {
  int led_id;
  bool state;
  int count;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("led id: ");
  Serial.println(myData.led_id);
  Serial.print("state: ");
  Serial.println(myData.state);
  Serial.print("cnt: ");
  Serial.println(myData.count);
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Set ESP8266 role to slave (receiver)
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packet info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  // Leave empty
}