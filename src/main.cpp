#include <Arduino.h>
#include <ESP8266WiFi.h>

extern "C" {
  #include <espnow.h>
  
}

uint8_t mac[] = {0x36, 0x33, 0x33, 0x33, 0x33, 0x33};
void initVariant() {
  wifi_set_macaddr(STATION_IF, &mac[0]);
}

byte cnt=0;
int pinAuxilio   = D0;
int pinMantente  = D5;
int pinTranquilo = D6;
int pinDetente   = D7;
int pinCuidado   = D8;

#define auxilio       (0)
#define mantente      (1) 
#define tranquilo     (2)
#define detente       (3)
#define cuidado       (4)



void setup()
{
  Serial.begin(115200);
  Serial.println("\r\nESP_Now MASTER CONTROLLER\r\n");

  pinMode(pinAuxilio, OUTPUT);
  pinMode(pinMantente, OUTPUT);
  pinMode(pinTranquilo, OUTPUT);
  pinMode(pinDetente, OUTPUT);
  pinMode(pinCuidado, OUTPUT);

 esp_now_init();
 esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    
    
  esp_now_register_recv_cb([](uint8_t *mac, uint8_t *data, uint8_t len)
  {
    Serial.print("\nMSG: ");
    Serial.write(data, len);

    if (strstr((char*)data, "auxilio") != NULL) {
      digitalWrite(pinAuxilio, !digitalRead(pinAuxilio));
    }
    else if (strstr((char*)data, "mantente") != NULL) {
      digitalWrite(pinMantente, !digitalRead(pinMantente));
    }
     else if (strstr((char*)data, "tranquilo") != NULL) {
      digitalWrite(pinTranquilo, !digitalRead(pinTranquilo));
    }
     else if (strstr((char*)data, "detente") != NULL) {
      digitalWrite(pinDetente, !digitalRead(pinDetente));
    }
     else if (strstr((char*)data, "cuidado") != NULL) {
      digitalWrite(pinCuidado, !digitalRead(pinCuidado));
    }
    
      
  });
  
}
 
    

void loop()
{
  
}