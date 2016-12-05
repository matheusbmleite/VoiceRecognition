
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"


#define I2C_ADDR  0x3f  //Defining address for the Serial LCD display.
#define BACKLIGHT_PIN  3

//Initialise the Serial LCD.
LiquidCrystal_I2C lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7); //These pin numbers are hard coded in on the serial backpack board.

String str = "";
int red = 9;
int green = 10;
int blue = 11;
int tempPin = A2; //Initializing the Temperature sensor
int buzzer = 5;
int DHT11Pin = 4;
DHT dht(DHT11Pin, DHT11); //Initializing the Humidity sensor


void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  dht.begin(); // Starting the humidity sensor
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin (16, 2);    //Initalize the LCD.
  lcd.setBacklightPin(3, POSITIVE); //Setup the backlight.
  lcd.setBacklight(HIGH); //Switch on the backlight.

}

void loop() {
  writeMessage("I'm SmartINO, ask me anything :)");
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    str = Serial.readString();
    if (str.equalsIgnoreCase("calculator mode")) {
      writeMessage("Calculator mode ON");
      calculatorMode();
    }else if(str.equalsIgnoreCase("temperature")) {
      temperature();
    }else if(str.equalsIgnoreCase("who is the best teacher") || str.equalsIgnoreCase("who's the best teacher")) {
      writeMessage("Ross Bigelow of course!"); 
      delay(2000); 
    }else if(str.equalsIgnoreCase("play me a song")) {
      writeMessage("Of course");
      delay(1000);
      playSong();
    }else if(str.equalsIgnoreCase("humidity")) {
      humidity();
    }    else {
      writeMessage(" Sorry, I don't have this module implemented yet :(");  
    }
  }
  delay(1000);
}

void writeMessage(String message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  if (message.length() > 16) {
    lcd.write(message.substring(0, 16).c_str());
    lcd.setCursor(0, 1);
    if (message.substring(16, 17).equalsIgnoreCase(" ")) {
      lcd.write(message.substring(17).c_str());
    } else {
      lcd.write(message.substring(16).c_str());
    }
  } else {
    lcd.write(message.c_str());
  }
  if (message.length() > 32) {
    delay(3000);
    if (message.substring(33, 34).equalsIgnoreCase(" ")) {
      writeMessage(message.substring(34));
    } else {
      writeMessage(message.substring(33));
    }
    delay(3000);
  }
}

void calculatorMode() {
  digitalWrite(blue, HIGH);
  bool exit = false;
  int first;
  int second;
  String operation;
  while (!exit) {
    str = Serial.readString();
    if (str == "exit") {
      writeMessage("Calculator mode OFF");
      digitalWrite(blue, LOW);
      delay(2000);
      break;
    } else { 
      writeMessage("Tell me the 1st number");
      while (Serial.available() <= 0) {
        //waiting for the speechRecognition
      }
      //---------------------------Reading the first number
      str = Serial.readString();
      if (str == "exit") {
        writeMessage("Calculator mode OFF");
        digitalWrite(blue, LOW);
        break;
      }
      if (str.toInt() != 0) {
        first = str.toInt();
        writeMessage("You said: "+String(first));
        delay(2000);
        writeMessage("Tell me the operation (+,/,*,-)");
        //-------------------------Reading the operation
        
        
        while (Serial.available() <= 0) {
          //waiting for the speechRecognition
        }
        str = Serial.readString();
        if (str == "exit") {
          writeMessage("Calculator mode OFF");
          digitalWrite(blue, LOW);
          delay(2000);
          break;
        }
        if (str.equalsIgnoreCase("plus") || str.equalsIgnoreCase("times") || str.equalsIgnoreCase("x") 
        || str.equalsIgnoreCase("minus") || str.equalsIgnoreCase("-") || str.equalsIgnoreCase("divided")) {
          operation = str;
          writeMessage("The operation is: "+operation);
          delay(1000);
        }
      }
      writeMessage("Tell me the 2nd number");
      while (Serial.available() <= 0) {
        //waiting for the speechRecognition
      }
      str = Serial.readString();  //THE CODE BELOW THIS COMMENT IS NOT SOMETHING I'M PROUD OF
      if (str == "exit") {
        writeMessage("Calculator mode OFF");
        digitalWrite(blue, LOW);
        delay(2000);
        break;
      }
      if (str.toInt() != 0) {
        second = str.toInt();
        writeMessage("You said: "+String(second));
        delay(2000);
        if (operation.equalsIgnoreCase("plus")) {
          int result = first + second;
          writeMessage(String(first)+" "+operation+" "+String(second)+" = "+String(result));
          delay(3000);
        } else if (operation.equalsIgnoreCase("x") || operation.equalsIgnoreCase("times") ) {
          int result = first * second;
          writeMessage(String(first)+" "+operation+" "+String(second)+" = "+String(result));
          delay(3000);
        } else if (operation.equalsIgnoreCase("-") || operation.equalsIgnoreCase("minus")) {
          int result = first - second;
          writeMessage(String(first)+" "+operation+" "+String(second)+" = "+String(result));
          delay(3000);
        } else if (operation.equalsIgnoreCase("divided")) {
          double result = double(first) / double(second);
          writeMessage(String(first)+" "+operation+" "+String(second)+" = "+String(result,3));
          delay(3000);
        }

      }
    }
  }
}

void temperature() {
  int temperature = analogRead(tempPin);
  float temperatureC = (5.0 * temperature * 100.0) / 1024;
  writeMessage("The temperature is: "+String(temperatureC)+" C");
  delay(2000);
}

void playSong() {
  tone(buzzer, 510,100);
  delay(450);
  tone(buzzer, 380,100);
  delay(400);
  tone(buzzer, 320,100);
  delay(500);
  tone(buzzer, 440,100);
  delay(300);
  tone(buzzer, 480,80);
  delay(330);
  tone(buzzer, 450,100);
  delay(150);
  tone(buzzer, 430,100);
  delay(300);
  tone(buzzer, 380,100);
  delay(200);
  tone(buzzer, 660, 80);
  delay(200);
  tone(buzzer, 760, 50);
  delay(150);
  tone(buzzer, 860, 100);
  delay(300);
  tone(buzzer, 700, 80);
  delay(150);
  tone(buzzer, 760, 50);
  delay(350);
  tone(buzzer, 660, 80);
  delay(300);
  tone(buzzer, 520, 80);
  delay(150);
  tone(buzzer, 580, 80);
  delay(150);
  tone(buzzer, 480, 80);
  delay(500);
}

void humidity() {
  float humidity = dht.readHumidity();
  writeMessage("The humidity is: "+String(humidity)+"%");
  delay(2000);

}
