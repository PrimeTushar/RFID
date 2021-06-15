0#include<SPI.h>
#include<EEPROM.h>
#include<MFRC522.h>
#include<ESP8266WiFi.h>
#include<esp8266Data.h>

const char* ssid="Gaurav";
const char* password="ampme1234";
const char* host="192.168.43.197";
const char* WebLink="emergency";
esp8266Data myData;
WiFiClient client;
String pubString,pubStringLength;

#define SS_PIN D4
#define RST_PIN D1
int addr = 0;
int Para_1 = 2, Para_2,Para_3,Para_4;
char id[10];
int ptr=0;
MFRC522 mfrc522 (SS_PIN ,RST_PIN);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(16,OUTPUT);
  WiFi.begin(ssid,password);
  delay(10);
  while(WiFi.status()!= WL_CONNECTED)
  {
      delay(10);
      Serial.print(".");
    }
    SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Approximate your card to the reader");
}

void loop() {
  // put your main code here, to run repeatedly:

  
  if( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }

  if(! mfrc522.PICC_ReadCardSerial())
  {
      return;
    }

  Serial.println("UID of tag :");
  for(int i=0; i<mfrc522.uid.size; i++)
  {
    Serial.print(" ");
    Serial.print(mfrc522.uid.uidByte[i],DEC);
    
  }
Serial.println();
     digitalWrite(16,LOW);
    //ID0=mfrc522.uid.uidByte[0];
    Para_2=mfrc522.uid.uidByte[1];
    Para_3=mfrc522.uid.uidByte[2];
    Para_4=mfrc522.uid.uidByte[3];
    
  SendData();
  digitalWrite(16,HIGH);
  delay(500);
  digitalWrite(16,LOW);
}

void SendData()
{
  WiFiClient client;
  const int httpPort=80;
  if(!client.connect(host,httpPort))
  {
      return;
    }
  int para1=1,para2=2,para3=3,para4=4;
  pubString=myData.buildData(Para_1, Para_2, Para_3, Para_4);
  Serial.println(pubString);
  
  client.print(myData.buildHTTP(WebLink));
 
  client.print(myData.buildHOST(host));
  
  client.print(myData.buildContentType());

  client.print(myData.buildLength(pubString));
  
  client.print(pubString);
  
  client.println();
  delay(10);
  Serial.print("Data Send..");
  }
