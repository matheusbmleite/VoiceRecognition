
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

//Define address for the Serial LCD display.
#define I2C_ADDR  0x3f  //If 0x3f doesn't work change this to 0x27
#define BACKLIGHT_PIN  3

//Initialise the Serial LCD.
LiquidCrystal_I2C lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7); //These pin numbers are hard coded in on the serial backpack board.

String str = "";
int red = 9;
int green = 10;
int blue = 11;

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
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
    const char *cstr = str.c_str(); // converting str to const char*
    if (str == "calculator mode") {
      writeMessage("Calculator mode ON");
      calculatorMode();
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
        if (str.equalsIgnoreCase("plus") || str.equalsIgnoreCase("times") || str.equalsIgnoreCase("x") || str.equalsIgnoreCase("minus") || str.equalsIgnoreCase("-") || str.equalsIgnoreCase("divided")) {
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
