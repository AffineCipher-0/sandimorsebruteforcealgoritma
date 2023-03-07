#include <Arduino.h>
#include <LiquidCrystal.h>
#include <string.h>

#define LED_PIN 13
#define BUTTON_PIN 2
#define MORSE_CHAR_COUNT 36


const char* MORSE_CHARS[MORSE_CHAR_COUNT] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..",
  "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
  "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..",
  "----.", "-----"
};


const char* MORSE_PATTERN = "-.-.-";

LiquidCrystal lcd(12, 11, 5, 4, 3, 1);  

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  lcd.begin(16, 2);  
}

void loop() {
  String morseSequence = "";  
  bool buttonPressed = false;
  while (!buttonPressed) {
    if (digitalRead(BUTTON_PIN) == HIGH) {  
      digitalWrite(LED_PIN, HIGH); 
      delay(100);  
      digitalWrite(LED_PIN, LOW);  
      buttonPressed = true;
      int morseLength = 0;
      unsigned long startTime = millis();
      while (millis() - startTime < 3000) {  
        if (digitalRead(BUTTON_PIN) == HIGH) {
          morseSequence += "-";
          morseLength++;
        } else {
          morseSequence += ".";
          morseLength++;
        }
        delay(100);  
      }
    
      int i = 0, j = 0;
      while (i < morseLength) {
        if (morseSequence.charAt(i) == MORSE_PATTERN[j]) {
          i++;
          j++;
        }
        if (j == strlen(MORSE_PATTERN)) {  
          char decodedChar = ' ';  
          for (int k = 0; k < MORSE_CHAR_COUNT; k++) {
            if (strcmp(morseSequence.substring(i - j, i).c_str(), MORSE_CHARS[k]) == 0) { 
              decodedChar = (char)(k + 65);  
              break;
            }
          }
          lcd.clear();  
          lcd.print(decodedChar);  
          break;
        } else if (i < morseLength && morseSequence.charAt(i) != MORSE_PATTERN[j]) {
          if (j != 0) {
            j = 0;
          } else {
            i++;
          }
        }
      }
    }
  }
}
