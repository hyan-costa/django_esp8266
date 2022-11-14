#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "conexao_wifi.h"

//---------dados wifi----------
const char* server_ip = SERVER_IP;
const char* ssid = SSID;
const char* password = SENHA;
//-----------------------------


const byte LED = D8;
const byte BOTAO = D2;
const byte BUZZER = D7;
void setup() {
  Serial.begin(115200);
  pinMode(LED, 1);
  pinMode(BOTAO, INPUT_PULLUP);
  pinMode(BUZZER, 1);
    
  //-----------------------------------conexão_wifi--------------------------------------------------
  WiFi.begin(ssid,password);
  Serial.print("\n\n\nConectando");
  while(WiFi.status() != WL_CONNECTED){
    digitalWrite(LED,0);
    delay(500);
    digitalWrite(LED,1);
    delay(500);
  }
  Serial.print("\nconectado! Endereco IP: ");
  Serial.print(WiFi.localIP());
  //-------------------------------------------------------------------------------------------------
  
  
}

void loop() {
  if (WiFi.status()== WL_CONNECTED){
    
    WiFiClient client;
    HTTPClient http;
    String body;  //corpo da requisição http
    http.begin(client,"http://" SERVER_IP "/data/");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    if(digitalRead(BOTAO) == 0){
      digitalWrite(LED,1);
      int status_luz = digitalRead(LED);
      body = "status=ligado&luz="+ String(status_luz);
      http.POST(body);
      
      tone(BUZZER,500);
      
    }
    else{
      
      digitalWrite(LED,0);
      noTone(BUZZER);
    
    }
    
  }
  else {
    Serial.println("WiFi is not connected");
  }

  
}
