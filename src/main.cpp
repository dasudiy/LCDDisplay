#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
char buffer[32];
size_t cursor = 0;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  lcd.init(); // initialize the lcd
  lcd.backlight();
}

void loop()
{
  // put your main code here, to run repeatedly:
  // If characters arrived over the serial port...
  if (Serial.available())
  {
    // Write all characters received with the serial port to the LCD.
    while (Serial.available() > 0)
    {
      char input = Serial.read();

      if (input == '\r')
      {
        String cmd = Serial.readStringUntil('\r');
        if (cmd == "0")
        {
          lcd.clear();
          cursor = 0;
          memset(buffer, 0, sizeof(buffer));
        }
        else if (cmd == "1")
        {
          lcd.noBacklight();
        }
        else if (cmd == "2")
        {
          lcd.noBacklight();
        }
        continue;
      }
      else if (input == '\n')
      {
        if (cursor > 31)
        {
          cursor = 0;
          lcd.setCursor(0, 0);
          for (size_t i = 16; i < 32; i++)
          {
            buffer[cursor] = buffer[i];
            lcd.write(buffer[cursor]);
            cursor++;
          }
        }
        if (cursor > 15)
        {
          lcd.setCursor(cursor % 16, cursor / 16);
          for (size_t i = cursor; i < 32; i++)
          {
            buffer[i] = ' ';
            lcd.write(buffer[i]);
          }
          cursor = 32;
        }
        else
        {
          for (size_t i = cursor; i < 16; i++)
          {
            buffer[i] = ' ';
          }
          cursor = 16;
        }
        continue;
      }
      else if (cursor > 31)
      {
        cursor = 0;
        lcd.setCursor(0, 0);
        bool lineEnd = false;
        for (size_t i = 16; i < 32; i++)
        {
          buffer[cursor] = buffer[i];
          lcd.write(buffer[cursor]);
          cursor++;
        }
      }
      lcd.setCursor(cursor % 16, cursor / 16);
      buffer[cursor] = input;
      cursor++;
      lcd.write(input);
    }
  }
}