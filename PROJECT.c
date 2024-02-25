#include <Wire.h> 
#include <LCD_I2C.h>
LCD_I2C lcd(0x27); 
# define solar A0
#include "DHT.h"
#define DHTPIN A3
#define relay 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int t,solarval;
unsigned int m=0,act=0,val1;

String inputString = ""; 
unsigned char a[200];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   Wire.begin();
  lcd.begin();                 //Init the LCD
  lcd.backlight();            //Activate backlight     
  lcd.home(); 
  dht.begin();
  pinMode(solar,INPUT);
  pinMode(relay,OUTPUT);
  digitalWrite(relay,HIGH); 
  lcd.setCursor(0,0);
  lcd.print("SOLAR VOLTAGE");
  lcd.setCursor(3,1);
  lcd.print("MEASUREMENT");
  delay(3000);
  lcd.clear();
}

void loop() {
     
       solarval=analogRead(solar);
       solarval=map(solarval,95,140,1,9);
       if(solarval<=0){solarval=1;}
       else if(solarval>=9){solarval=9;}
       Serial.print("solar:");
       Serial.println(solarval);
       
     lcd.setCursor(0,0);lcd.print("SOLAR VOLT:");
    if(solarval <= 9){lcd.print("00");lcd.print(solarval);}
    else if(solarval <= 99){lcd.print("0");lcd.print(solarval);}
    else if(solarval <= 999){lcd.print(solarval);}
  
     t = dht.readTemperature();
    lcd.setCursor(0,1);lcd.print("TEM:");
    if(t <= 9){lcd.print("00");lcd.print(t);}
    else if(t <= 99){lcd.print("0");lcd.print(t);}
    else if(t <= 999){lcd.print(t);}
    lcd.setCursor(8,1);lcd.print("B:");lcd.print("12V");
    while(Serial.available())
    {
        char data;
        data=Serial.read();
  
        a[m]=data;
          if(a[0] == '*')
          {
            if(m<=3)
            {m++;}
          }
      }
      if(m > 1)
      {
        val1 = (a[1]-0x30)*100 + (a[2]-0x30)*10  + (a[3] - 0x30);  
        
        m=0;
      }
      delay(200);

Serial.print("VAlue :");
Serial.println(val1);
      if(val1==1)
  {   
    digitalWrite(relay,LOW);
     Serial.println("received...............");
  }
    else if(val1==0)
  {
   digitalWrite(relay,HIGH);
     Serial.println("not received...............");
  }
    sendata();
    delay(500);
}
void sendata()
{
  Serial.print("*");
  if(solarval <= 9){Serial.print("00");Serial.print(solarval);}
    else if(solarval <= 99){Serial.print("0");Serial.print(solarval);}
    else if(solarval <= 999){Serial.print(solarval);}

    if(t <= 9){Serial.print("00");Serial.print(t);}
    else if(t <= 99){Serial.print("0");Serial.print(t);}
    else if(t <= 999){Serial.print(t);}
}