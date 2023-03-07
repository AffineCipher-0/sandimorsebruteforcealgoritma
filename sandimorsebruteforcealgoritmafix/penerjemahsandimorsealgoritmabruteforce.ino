#include <Arduino.h>
#include <LiquidCrystal.h>

#define LED_PIN 13
#define BUTTON_PIN 2
#define MORSE_CHAR_COUNT 36

// Morse code library
const char* MORSE_CHARS[MORSE_CHAR_COUNT] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..",
  "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
  "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..",
  "----.", "-----"
};

LiquidCrystal lcd(12, 11, 5, 4, 3, 1);  // Initialize the LCD display

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  lcd.begin(16, 2);  // Initialize the LCD display
}

void loop() {
  String morseSequence = "";  // Initialize an empty Morse code sequence
  bool buttonPressed = false;
  while (!buttonPressed) {
    if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
      digitalWrite(LED_PIN, HIGH);  // Turn on LED
      delay(100);  // Wait for 100 milliseconds
      digitalWrite(LED_PIN, LOW);  // Turn off LED
      buttonPressed = true;
      int morseLength = 0;
      unsigned long startTime = millis();
      while (millis() - startTime < 3000) {  // Record Morse code sequence for up to 3 seconds
        if (digitalRead(BUTTON_PIN) == HIGH) {  // Check if button is pressed
          morseSequence += "-";
          morseLength++;
        } else {
          morseSequence += ".";
          morseLength++;
        }
        delay(100);  // Wait for 100 milliseconds
      }
      // Morse code decoding using brute force algorithm
      char decodedChar = ' ';  // Initialize the decoded character to a space
      for (int i = 0; i < MORSE_CHAR_COUNT; i++) {
        if (morseSequence == MORSE_CHARS[i]) {  // Check if Morse code sequence matches library entry
          decodedChar = (char)(i + 65);  // Convert index to ASCII character code
          break;
        }
      }
      lcd.clear();  // Clear the LCD display
      lcd.print(morseSequence);  // Print the Morse code sequence to the LCD display
      lcd.setCursor(0, 1);  // Move cursor to second row of LCD display
      lcd.print(decodedChar);  // Print the decoded character to the LCD display
      delay(3000);  // Wait for 3 seconds before starting over
    }
  }
}


// Dalam contoh ini, alat decoder kode Morse berbasis Arduino menggunakan LED dan tombol untuk merekam urutan kode Morse dari 
// pengguna. Alat tersebut kemudian menggunakan algoritme brute force untuk mencocokkan urutan kode Morse yang dimasukkan dengan 
// pustaka karakter kode Morse. Alat tersebut kemudian menampilkan urutan kode Morse dan karakter yang diterjemahkan pada layar LCD.

// Fungsi pengaturan menginisialisasi tampilan LED, tombol, dan LCD, sedangkan fungsi loop menunggu pengguna menekan tombol
//  untuk mulai merekam urutan kode Morse. Setelah tombol ditekan, fungsi merekam urutan kode Morse hingga 3