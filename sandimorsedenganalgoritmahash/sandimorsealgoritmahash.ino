#include <Arduino.h>
#include <LiquidCrystal.h>
#include <string.h>
#include <Hash.h> // Impor Hash

#define LED_PIN 13
#define BUTTON_PIN 2
#define MORSE_CHAR_COUNT 36

// sandi morse
const char* MORSE_CHARS[MORSE_CHAR_COUNT] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..",
  "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
  "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..",
  "----.", "-----"
};

// Nilai hash untuk setiap karakter kode Morse
uint32_t MORSE_HASHES[MORSE_CHAR_COUNT] = {
  116, 325, 288, 224, 46, 247, 301, 81, 77, 118, 232, 143, 278, 227, 218, 276, 346, 262, 321,
  239, 308, 269, 292, 379, 331, 428, 369, 406, 421, 461, 489, 406, 332, 342, 320, 287, 300
};

LiquidCrystal lcd(12, 11, 5, 4, 3, 1);  // Inisialisasi layar LCD

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  lcd.begin(16, 2);  
  Hash.init(); // Inisialisasi algoritma hash
}

void loop() {
  String morseSequence = "";  // Inisialisasi urutan sandi morse
  bool buttonPressed = false;
  while (!buttonPressed) {
    if (digitalRead(BUTTON_PIN) == HIGH) {  // tombol ditekan
      digitalWrite(LED_PIN, HIGH);  // Turn on LED
      delay(100);  // 100 ms
      digitalWrite(LED_PIN, LOW);  // Turn off LED
      buttonPressed = true;
      int morseLength = 0;
      unsigned long startTime = millis();
      while (millis() - startTime < 3000) {  // mengurtkan selama 3 detik
        if (digitalRead(BUTTON_PIN) == HIGH) {  // memeriksa jika tombol ditekan
          morseSequence += "-";
          morseLength++;
        } else {
          morseSequence += ".";
          morseLength++;
        }
        delay(100);  // 100 ms
      }
      // Decoding kode morse menggunakan algoritma hash
      uint32_t hashValue = Hash.FNV1aHash((const uint8_t*)morseSequence.c_str(), morseLength);
      char decodedChar = ' ';  // Inisialisasi karakter yang didekodekan ke spasi
      for (int i = 0; i < MORSE_CHAR_COUNT; i++) {
        if (hashValue == MORSE_HASHES[i]) {  // Periksa apakah nilai hash cocok dengan entri pada library
          decodedChar = (char)(i + 65);  // Ubah indeks menjadi kode karakter ASCII
          break;
        }
      }
      lcd.clear();  // Bersihkan layar LCD

      