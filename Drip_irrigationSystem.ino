#include<SoftwareSerial.h>
SoftwareSerial Serial1(0,1);

#include<LiquidCrystal.h>
LiquidCrystal lcd(14,15,16,17,18,19);
int led=13;
int flag=0;
String str="";

#define motor 11
#define sensor 7

void setup()
{
  lcd.begin(16,2);
  Serial1.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(sensor, INPUT_PULLUP);
  lcd.print("Water Irrigaton");
  lcd.setCursor(4,1);
  delay(2000);
  lcd.clear();
  lcd.print("Circuit Digest");
  lcd.setCursor(0,1);
  lcd.print("Welcomes You");
  delay(2000);
 //gsmInit();
  lcd.clear();
  lcd.print("System Ready");
}

void loop()
{
    lcd.setCursor(0,0);
    lcd.print("Automatic Mode    ");
    if(digitalRead(sensor)==1 && flag==0)
    {
      delay(1000);
      if(digitalRead(sensor)==1)
      {
        digitalWrite(led, HIGH);
        sendSMS("Low Soil Moisture detected. Motor turned ON");
        lcd.begin(16,2);
        lcd.setCursor(0,1);
        lcd.print("Motor ON    ");
        digitalWrite(motor, HIGH);
        delay(2000);
        flag=1;
      }
    }

    else if(digitalRead(sensor)==0 && flag==1)
    {
      delay(1000);
      if(digitalRead(sensor)==0)
      {
        digitalWrite(led, LOW);
        sendSMS("Soil Moisture is Normal. Motor turned OFF");
        digitalWrite(motor, LOW);
        lcd.begin(16,2);
        lcd.print("Motor OFF");
        lcd.setCursor(0,1);
        lcd.print("Motor OFF");
        delay(2000);
        flag=0;
      }
    }
}
 
void sendSMS(String msg)
{
  lcd.clear();
  lcd.print("Sending SMS");
  Serial1.println("AT+CMGF=1");
  delay(500);
  Serial1.print("AT+CMGS=");
  Serial1.print('"');
  Serial1.print("+919550755866");    // number
  Serial1.print('"');
  Serial1.println();
  delay(500);
  Serial1.println(msg);
  delay(500);
  Serial1.write(26);
  delay(1000);
  lcd.clear();
  lcd.print("SMS Sent");
  delay(1000);
  lcd.begin(16,2);
}
