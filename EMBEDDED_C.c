#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "2pWboHpxs3JlmkDR9FKyZYcGnA0SPHch";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "IOT";
char pass[] = "123456789";

unsigned int m=0,act=0,val,val1,val2,val3,val4,val5,val6,val7;

String inputString = ""; 
unsigned char a[200];

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
    
}
BLYNK_WRITE(V0)
{
  int button = param.asInt(); // read button
  if (button == 1) 
  { 
     Serial.print('*');
    Serial.print("001");
 
  } 
  else
  {
    Serial.print('*');
    Serial.print("000");
    
  }
} 
void loop()
{
   while(Serial.available())
    {
        char data;
        data=Serial.read();
  
        a[m]=data;
          if(a[0] == '*')
          {
            if(m<=6)
            {m++;}
          }
      }
      if(m > 1)
      {
        val1 = (a[1]-0x30)*100 + (a[2]-0x30)*10  + (a[3] - 0x30);
        val2 = (a[4]-0x30)*100 + (a[5]-0x30)*10  + (a[6] - 0x30);
        
        m=0;
      }
    
     int X=12;
      
        Blynk.virtualWrite(V1,val1);
     
    
    delay(100);
    Blynk.virtualWrite(V2,val2);


    delay(100);
    Blynk.virtualWrite(V3,X);
       delay(100);
      Blynk.run();
      delay(100);
  }