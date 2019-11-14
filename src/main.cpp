#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>

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

Ticker tk1,tk2;

void test()
{
  Serial.println("testing...");
}

void apagar(int pin)
{
  digitalWrite(pin,LOW);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("\n\nESP_Now MASTER CONTROLLER\r\n");

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
      digitalWrite(pinAuxilio, HIGH);
      tk2.once_ms(5000, apagar, pinAuxilio);
    }
    else if (strstr((char*)data, "mantente") != NULL) {
      digitalWrite(pinMantente, HIGH);
      tk2.once_ms(5000, apagar, pinMantente);
    }
     else if (strstr((char*)data, "tranquilo") != NULL) {
      digitalWrite(pinTranquilo, HIGH);
      tk2.once_ms(5000, apagar, pinTranquilo);
    }
     else if (strstr((char*)data, "detente") != NULL) {
      digitalWrite(pinDetente, HIGH);
      tk2.once_ms(5000, apagar, pinDetente);
    }
     else if (strstr((char*)data, "cuidado") != NULL) {
      digitalWrite(pinCuidado, HIGH);
      tk2.once_ms(5000, apagar, pinCuidado);
    }
      
  });

  tk1.attach_ms(1000, test);
  
}
 
    

void loop()
{
  
}