int ledhijau = 11;     //pin lampu
int ledmerah = 12;
int titikButton = 2;   //titik button
int garisButton = 3;   //garis button
int spasiButton = 4;
int buzzer = 8;

int karakterascii = 0; //karakter
int mulaiposisi = 0,
    akhirposisi = 0; //mulai posisi - akhir posisi
int mulaiposisi1 = 0,
    akhirposisi1 = 0; //mulai posisi1 - akhir posisi1
int bagiangarisButton = 0; //status garis button
int bagiantitikButton = 0; //status titik button
int bagianspasiButton = 0;

#define karakter 44 //array dari ascii untuk morse code karakter 
String sandimorse = ""; //sandi morse
String karaktersandi = "";
String text = "";
String hasilTerjemahan = ""; // Menyimpan hasil terjemahan

String data[karakter] = {
  "/",       //47
  "-----",   //48 - 0
  ".----",   //49 - 1
  "..---",   //50 - 2
  "...--",   //51 - 3
  "....-",   //52 - 4
  ".....",   //53 - 5
  "-....",   //54 - 6
  "--...",   //55 - 7
  "---..",   //56 - 8
  "----.",   //57 - 9
  "---...",  //58 - :
  "-.-.-.",  //59 - ;
  "",        //60 - <
  "-...-",   //61 - =
  "",        //62 - >
  "..--..",  //63 - ?
  ".--.-.",  //64 - @
  ".-",      //65 - A
  "-...",    //66 - B
  "-.-.",    //67 - C
  "-..",     //68 - D
  ".",       //69 - E
  "..-.",    //70 - F
  "--.",     //71 - G
  "....",    //72 - H
  "..",      //73 - I
  ".---",    //74 - J
  "-.-",     //75 - K
  ".-..",    //76 - L
  "--",      //77 - M
  "-.",      //78 - N
  "---",     //79 - O
  ".--.",    //80 - P
  "--.-",    //81 - Q
  ".-.",     //82 - R
  "...",     //83 - S
  "-",       //84 - T
  "..-",     //85 - U
  "...-",    //86 - V
  ".--",     //87 - W
  "-..-",    //88 - X
  "-.--",    //89 - Y
  "--.."     //90 - Z
};

bool translateMode = false; // Mode terjemahan, awalnya false (Morse ke teks)

void setup()
{
  pinMode(ledhijau, OUTPUT);
  pinMode(ledmerah, OUTPUT);
  pinMode(titikButton, INPUT);
  pinMode(garisButton, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);

}

void hijau()
{
  digitalWrite(ledhijau, HIGH);
}

void merah()
{
  digitalWrite(ledmerah, HIGH);
}

void suara()
{
  digitalWrite(buzzer, HIGH);
}

void mati()
{
  digitalWrite(ledhijau, LOW);
  digitalWrite(ledmerah, LOW);
  digitalWrite(buzzer, LOW);
}

//proses pada hardware
void proses()
{
  bagiantitikButton = digitalRead(titikButton);
  bagiangarisButton = digitalRead(garisButton);
  bagianspasiButton = digitalRead(spasiButton);

  if (bagiangarisButton == HIGH)
  {
    merah();
    suara();
    sandimorse = sandimorse + ("-");
    Serial.print("-");
    delay(500);
  }
  else if (bagiantitikButton == HIGH)
  {
    hijau();
    suara();
    sandimorse = sandimorse + (".");
    Serial.print(".");
    delay(200);
  }
  else if (bagianspasiButton == HIGH)
  {
    sandimorse = sandimorse + ("/");
    Serial.print("/");
    delay(200);
  }
  else
  {
    mati();
    delay(50);
  }
}

char konvmenjadikarakter(String karaktersandi)
{
  for (int i = 0; i < karakter; i++)
  {
    if (karaktersandi == data[i])
    {
      karakterascii = i + 47;
      return (char)karakterascii;
    }
  }
  return '\0'; // Mengembalikan karakter null jika tidak ada sandi Morse yang cocok
}

void mengeksposdata(String data)
{
  data.concat('/');

  akhirposisi = data.indexOf('/');

  while (akhirposisi < data.length())
  {
    char result = konvmenjadikarakter(data.substring(mulaiposisi, akhirposisi));
    if (result != '\0') {
      text.concat(result);
    } else {
      Serial.println("\nSandi Morse salah. Ulangi lagi.");
      return;
    }

    mulaiposisi = akhirposisi + 1;

    if (mulaiposisi == data.length())
    {
      break;
    }
    akhirposisi = data.indexOf('/', mulaiposisi);
  }

  hasilTerjemahan += text + " ";
  Serial.println(text);
  mulaiposisi = 0;
  akhirposisi = 0;
  text = "";
}

void loop()
{
  while (Serial.available() > 0)
  {
    int ascii = Serial.read();

    switch (ascii)
    {
      case 49:
        Serial.print("\n");
        sandimorse = sandimorse + ("#");
        Serial.print("\nTerjemahan Sandi Morse: ");

        akhirposisi1 = sandimorse.indexOf('#');

        while (akhirposisi1 < sandimorse.length())
        {
          mengeksposdata(sandimorse.substring(mulaiposisi1, akhirposisi1));
          mulaiposisi1 = akhirposisi1 + 1;

          if (mulaiposisi1 == sandimorse.length())
          {
            break;
          }
          akhirposisi1 = sandimorse.indexOf('#', mulaiposisi1);
        }

        mulaiposisi1 = 0;
        akhirposisi1 = 0;
        text = "";
        sandimorse = "";
        Serial.println("\n");
        Serial.println("Tekan 1 di keyboard untuk output hasil");
        Serial.println("Sandi Morse : ");
        break;

      default:
        sandimorse += ascii;
        Serial.print((char)ascii);
        break;
    }
  }
  proses();
}
