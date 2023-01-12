#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 8
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float celsius, fahrenheit;

int Sensor1 = A0;
int Sensor2 = A1;

int Bulb = A5;
int Fan = A4;
int Buzzer = A3;

int Counter = 0;
int Sen1Check = 0;
int Sen2Check = 0;

void setup(void)
{
    Serial.begin(9600);
    digitalWrite(Bulb, HIGH);
    digitalWrite(Fan, HIGH);
    digitalWrite(Buzzer, HIGH);
    pinMode(Sensor1, INPUT);
    pinMode(Sensor2, INPUT);
    pinMode(Bulb, OUTPUT);
    pinMode(Fan, OUTPUT);
    pinMode(Buzzer, OUTPUT);

    lcd.begin(20, 4);
    lcd.setCursor(0, 1);
    lcd.print("Temp = ");
    lcd.setCursor(0, 0);
    lcd.print("Counter = ");
    lcd.setCursor(12, 0);
    lcd.print("Persons");
}

void loop()
{
    CheckEntry();
    CheckLeaving();
    lcd.setCursor(7, 1);
    sensors.requestTemperatures();
    lcd.println(sensors.getTempCByIndex(0));
    lcd.setCursor(12, 1);
    lcd.print(" degC");
    lcd.setCursor(10, 0);
    if(Counter >= 0){lcd.print(Counter);}
    if(Counter < 0){Counter = 0;}

    if(Counter > 0)
    {
        digitalWrite(Bulb, LOW);
        digitalWrite(Fan, LOW);
        digitalWrite(Buzzer, HIGH);
        lcd.setCursor(0, 2);
        lcd.print("Fan : ON ");
        lcd.setCursor(0, 3);
        lcd.print("Bulb : ON ");
    }

    if(Counter < 1)
    {
        digitalWrite(Bulb, HIGH);
        digitalWrite(Fan, HIGH);
        digitalWrite(Buzzer, HIGH);
        lcd.setCursor(0, 2);
        lcd.print("Fan : OFF");
        lcd.setCursor(0, 3);
        lcd.print("Bulb : OFF");

    }
}

void CheckEntry()
{
    if(((digitalRead(Sensor1) == LOW) || (Sen1Check == 1)) && (Sen2Check == 0))
    {
        while(digitalRead(Sensor1) == LOW);
        Sen1Check = 1;

        if(digitalRead(Sensor2) == LOW)
        {
            Counter++;
            Sen1Check = 0;
            while(digitalRead(Sensor2) == LOW);
        }
    }
}

void CheckLeaving()
{
    if(((digitalRead(Sensor2) == LOW) || (Sen2Check == 1)) && (Sen1Check == 0))
    {
        while(digitalRead(Sensor2) == LOW);
        Sen2Check = 1;

        if(digitalRead(Sensor1) == LOW)
        {
            Counter = Counter - 1;
            Sen2Check = 0;
            while(digitalRead(Sensor1) == LOW);
        }
    }
}