int ledhijau=11;//pinlampu 
int ledmerah=12;
int titikButton=2;//titikbutton
int garisButton=3;//garisbutton
int spasiButton=4;
int buzzer=8;

int karakterascii=0;//karakter
int mulaiposisi=0, 
	akhirposisi=0;//mulai posisi - akhir posisi
int mulaiposisi1=0, 
	akhirposisi1=0;//mulai posisi1 - akhir posisi1
int bagiangarisButton=0;//statusgarisbutton
int bagiantitikButton=0;//statustitikbutton
int bagianspasiButton=0;
// int statusledmerah=0;//statusledmerah

#define karakter 44//array dari ascci untuk morse code karakter 
String sandimorse="";//sandimorse
String karaktersandi="";
String text="";
//char* string data[karakter]
String data[karakter]={
  "/", //47
  "-----",  // 48 - 0
  ".----",  // 49 - 1
  "..---",  // 50 - 2
  "...--",  // 51 - 3
  "....-",  // 52 - 4
  ".....",  // 53 - 5
  "-....",  // 54 - 6
  "--...",  // 55 - 7
  "---..",  // 56 - 8
  "----.",  // 57 - 9
  "---...", // 58 - :
  "-.-.-.", // 59 - ;
  "",       // 60 - <
  "-...-",  // 61 - =
  "",       // 62 - >
  "..--..", // 63 - ?
  ".--.-.", // 64 - @
  ".-",     // 65 - A
  "-...",   // 66 - B
  "-.-.",   // 67 - C
  "-..",    // 68 - D
  ".",      // 69 - E
  "..-.",   // 70 - F
  "--.",    // 71 - G
  "....",   // 72 - H
  "..",     // 73 - I
  ".---",   // 74 - J
  "-.-",    // 75 - K
  ".-..",   // 76 - L
  "--",     // 77 - M
  "-.",     // 78 - N
  "---",    // 79 - O
  ".--.",   // 80 - P
  "--.-",   // 81 - Q
  ".-.",    // 82 - R
  "...",    // 83 - S
  "-",      // 84 - T
  "..-",    // 85 - U
  "...-",   // 86 - V
  ".--",    // 87 - W
  "-..-",   // 88 - X
  "-.--",   // 89 - Y
  "--..",   // 90 - Z
};

        
void setup() {

pinMode(ledhijau, OUTPUT);
pinMode(ledmerah, OUTPUT);
pinMode(titikButton, INPUT);
pinMode(garisButton, INPUT);
pinMode(buzzer, OUTPUT);
Serial.begin(9600);

Serial.println("Tekan 1 di keyboard untuk output hasil ");
Serial.println("Tekan / di keyboard atau pada button untuk spasi ");
Serial.println("Sandi Morse : ");

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
  
  bagiantitikButton=digitalRead(titikButton);
  bagiangarisButton=digitalRead(garisButton);
  bagianspasiButton=digitalRead(spasiButton);
  
  
  if(bagiangarisButton == HIGH)
  {
    merah();
    suara();
    sandimorse=sandimorse+("-");
    Serial.print("-");
    delay(500);
  }
  else if(bagiantitikButton == HIGH)
  {
   hijau();
   suara();
   sandimorse=sandimorse+(".");
   Serial.print(".");
   delay(200);
  }
  else if(bagianspasiButton == HIGH)
  {
   sandimorse=sandimorse+("/");
   Serial.print("/");
   delay(200);
  } 
//  else if(bagiangarisButton==HIGH && bagiantitikButton==HIGH)
//  {
//    sandimorse=sandimorse+(" ");
//    mati();
//  }
  else
  {
    mati();
    delay(50);
  }

}
// {
char konvmenjadikarakter(String karaktersandi) //bruteforce
{

  for(int i=0; i<karakter; i++)
  {
   	if(karaktersandi == data[i])
    {
      karakterascii = i+47;//ascii dari urutan ke 47
      break;
    }
  }
  return karakterascii;

}

// Penjelasan Kode
// Kode ini mendefinisikan sebuah fungsi bernama "konvmenjadikarakter" yang mengambil string "karaktersandi" sebagai parameter masukan dan mengembalikan sebuah karakter.
// Fungsi memeriksa apakah string input cocok dengan karakter apa pun dalam larik karakter "data". Jika ada kecocokan, 
// nilai ASCII yang sesuai dihitung dan disimpan dalam variabel bilangan bulat bernama "karakterascii". 
// Nilai ASCII yang dihitung adalah indeks dari karakter yang cocok dalam larik "data" yang ditambahkan ke 47 (kode ASCII untuk angka 0).
// Terakhir, fungsi mengembalikan karakter yang dihitung (dicetak dari nilai bilangan bulat "karakterascii").
// Secara keseluruhan, kode ini melakukan algoritma brute force untuk mengonversi karakter ke nilai ASCII yang sesuai

// }

//{
void mengeksposdata(String data) //string matching
{
  
        data.concat('/'); // Menempatkan / di akhir kata untuk menyederhanakan pemrosesan lebih lanjut

        akhirposisi=data.indexOf('/');
 
        while(akhirposisi < data.length()) //Loop untuk mengekstraksi sandi morse karakter tunggal dari rangkaian kata  
        {
          text.concat(konvmenjadikarakter(data.substring(mulaiposisi, akhirposisi)));// ditambahkan data.substring
          
          mulaiposisi=akhirposisi+1;
          
          if(mulaiposisi == data.length())
          {
            break;
          }
          akhirposisi=data.indexOf('/', mulaiposisi);
        }
                
        
        Serial.print(text);
        Serial.print(" ");
        mulaiposisi=0;
        akhirposisi=0;
        text="";    

  
}

// Kode ini mendefinisikan fungsi yang disebut "mengeksposdata" yang mengambil parameter string tunggal yang disebut "data". 
// Fungsi memproses string input ini dengan menambahkan garis miring (/) untuk menyederhanakan pemrosesan selanjutnya. 
// Kemudian mengekstrak karakter sandi morse satu karakter dari string dan mengubahnya menjadi karakter (ASCII) menggunakan fungsi lain yang disebut "konvmenjadikarakter". 
// Karakter yang diekstraksi digabungkan bersama dalam variabel string baru yang disebut "teks". Terakhir, isi "teks" ditampilkan di layar LCD (LCD pada serial monitor) menggunakan fungsi bernama "lcd_1.print" 
// dan dicetak ke monitor serial menggunakan "Serial.print". Variabel "mulaiposisi", "akhirposisi", dan "teks" diatur ulang di akhir fungsi untuk mempersiapkan pemrosesan selanjutnya.

// }

// void mengeksposdata(String data) //string matching
// {
//         data.concat('/'); // Menempatkan / di akhir kata untuk menyederhanakan pemrosesan lebih lanjut

//         akhirposisi=data.indexOf('/');

//          // while(akhirposisi != -1)
//         // {
//         //   karaktersandi=data.substring(mulaiposisi, akhirposisi);
//         //   karakterascii=konvmenjadikarakter(karaktersandi);
//         //   text=text+char(karakterascii);
//         //   mulaiposisi=akhirposisi+1;
//         //   akhirposisi=data.indexOf('/', mulaiposisi);
//         // }

//         // while(akhirposisi != -1)
//         // {
//         //   mulaiposisi=akhirposisi+1;
//         //   akhirposisi=data.indexOf('/', mulaiposisi);
//         //   karaktersandi=data.substring(mulaiposisi, akhirposisi);
//         //   text=text+konvmenjadikarakter(karaktersandi);
//         // }
       
//         // while( akhirposisi<data.length() )
//         // {
//         //   karaktersandi=data.substring(mulaiposisi, akhirposisi);
//         //   text.concat(konvmenjadikarakter(karaktersandi));
//         //   mulaiposisi=akhirposisi+1;
//         //   karaktersandi="";
//         //   if(mulaiposisi == data.length() )
//         //   {
//         //     break;
//         //   }
//         //   akhirposisi=data.indexOf('/', mulaiposisi);  
//         //  }
       
//         while(akhirposisi < data.length()) //Loop untuk mengekstraksi sandi morse karakter tunggal dari rangkaian kata  
//         {
//           text.concat(konvmenjadikarakter(data.substring(mulaiposisi, akhirposisi)));// ditambahkan data.substring
         
//           mulaiposisi=akhirposisi+1;
         
//           if(mulaiposisi == data.length())
//           {
//             break;
//           }
//           akhirposisi=data.indexOf('/', mulaiposisi);
//         }
               
       
//         Serial.print(text);
//         Serial.print(" ");
//         mulaiposisi=0;
//         akhirposisi=0;
//         text="";    

 
// }


void loop() 
{
while(Serial.available() > 0 ) 
{
      int ascii=Serial.read();

	  // if(ascii == 1)
      // {
      //   proses();
      // }
      // else if(ascii == 92)
      // {
      //   sandimorse=sandimorse+("/");
      //   Serial.print("/");
      //   mengeksposdata(sandimorse);
      //   sandimorse="";
      // }
      // else
      // {
      //   sandimorse=sandimorse+("#");
      //   Serial.print("#");
      //   mengeksposdata(sandimorse);
      //   sandimorse="";
      // }
  

      switch(ascii)
      {
        case 49: //

        Serial.print("\n");
        sandimorse=sandimorse+("#");

         Serial.print("\nTerjemahan Sandi Morse :  ");
         
        akhirposisi1=sandimorse.indexOf('#');

        while(akhirposisi1 < sandimorse.length() ) //string matching brute force
        {
          mengeksposdata(sandimorse.substring(mulaiposisi1, akhirposisi1)); 
            // fungsi yang mengubah data sandi morse menjadi angka, huruf, dan simbol.
          mulaiposisi1=akhirposisi1+1;
          if(mulaiposisi1 == sandimorse.length() )
          {
            break; 
          }
           akhirposisi1= sandimorse.indexOf('#', mulaiposisi1);
        }
        
        mulaiposisi1=0;
        akhirposisi1=0;

        text=""; //mengubah terjemahan baru   
        sandimorse="";
        Serial.println("\n\nMasukan Sandi Morse :");
        
              
        break;

        case 47: // 47 data ascii ditombol keyboard /
        
        sandimorse=sandimorse+("/");
        Serial.print("/");
        delay(200);
        
        break;

        case 51: // 51 data ascii dari keyboard 3
          
        sandimorse=sandimorse+("#");
        Serial.print("#");
        delay(200);
        
        break;
        
      }
      
}

proses();

}
