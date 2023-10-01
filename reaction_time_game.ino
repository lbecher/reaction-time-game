/*

EQUIPE 4

Gabriel Jared de Amorim
Luiz Eduardo Garzon de Oliveira
Luiz Fernando Becher de Araujo
Matheus Lucas Ferreira Jacinto

*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int lcd_sda = D1;
const int lcd_scl = D2;

const int reset_btn = D4;

const int player_1_led = D5;
const int player_2_led = D6;

const int player_1_btn = D3;
const int player_2_btn = D7;

const int buzzer = D8;

const int tempo = 100;

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

int melody_1[] = {

  // Harry Potter
  
  REST, 2, NOTE_D4, 4,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_G4, 2, NOTE_D5, 4,
  NOTE_C5, -2, 
  NOTE_A4, -2,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_F4, 2, NOTE_GS4, 4,
  NOTE_D4, -1, 
  NOTE_D4, 4,

  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4, //10
  NOTE_G4, 2, NOTE_D5, 4,
  NOTE_F5, 2, NOTE_E5, 4,
  NOTE_DS5, 2, NOTE_B4, 4,
  NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_B4, 4,
  NOTE_G4, -1,
  NOTE_AS4, 4,
     
  NOTE_D5, 2, NOTE_AS4, 4,//18
  NOTE_D5, 2, NOTE_AS4, 4,
  NOTE_DS5, 2, NOTE_D5, 4,
  NOTE_CS5, 2, NOTE_A4, 4,
  NOTE_AS4, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_D4, 4,
  NOTE_D5, -1, 
  REST,4, NOTE_AS4,4,  

  NOTE_D5, 2, NOTE_AS4, 4,//26
  NOTE_D5, 2, NOTE_AS4, 4,
  NOTE_F5, 2, NOTE_E5, 4,
  NOTE_DS5, 2, NOTE_B4, 4,
  NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_AS4, 4,
  NOTE_G4, -1, 
  
};
int melody_2[] = {

  // Game of Thrones

  NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16, //1
  NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16,
  NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16,
  NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16,
  NOTE_G4,-4, NOTE_C4,-4,//5

  NOTE_DS4,16, NOTE_F4,16, NOTE_G4,4, NOTE_C4,4, NOTE_DS4,16, NOTE_F4,16, //6
  NOTE_D4,-1, //7 and 8
  NOTE_F4,-4, NOTE_AS3,-4,
  NOTE_DS4,16, NOTE_D4,16, NOTE_F4,4, NOTE_AS3,-4,
  NOTE_DS4,16, NOTE_D4,16, NOTE_C4,-1, //11 and 12

  //repeats from 5
  NOTE_G4,-4, NOTE_C4,-4,//5

  NOTE_DS4,16, NOTE_F4,16, NOTE_G4,4, NOTE_C4,4, NOTE_DS4,16, NOTE_F4,16, //6
  NOTE_D4,-1, //7 and 8
  NOTE_F4,-4, NOTE_AS3,-4,
  NOTE_DS4,16, NOTE_D4,16, NOTE_F4,4, NOTE_AS3,-4,
  NOTE_DS4,16, NOTE_D4,16, NOTE_C4,-1, //11 and 12
  NOTE_G4,-4, NOTE_C4,-4,
  NOTE_DS4,16, NOTE_F4,16, NOTE_G4,4,  NOTE_C4,4, NOTE_DS4,16, NOTE_F4,16,

  NOTE_D4,-2,//15
  NOTE_F4,-4, NOTE_AS3,-4,
  NOTE_D4,-8, NOTE_DS4,-8, NOTE_D4,-8, NOTE_AS3,-8,
  NOTE_C4,-1,
  NOTE_C5,-2,
  NOTE_AS4,-2,
  NOTE_C4,-2,
  NOTE_G4,-2,
  NOTE_DS4,-2,
  NOTE_DS4,-4, NOTE_F4,-4, 
  NOTE_G4,-1,
  
  NOTE_C5,-2,//28
  NOTE_AS4,-2,
  NOTE_C4,-2,
  NOTE_G4,-2, 
  NOTE_DS4,-2,
  NOTE_DS4,-4, NOTE_D4,-4,
  NOTE_C5,8, NOTE_G4,8, NOTE_GS4,16, NOTE_AS4,16, NOTE_C5,8, NOTE_G4,8, NOTE_GS4,16, NOTE_AS4,16,
  NOTE_C5,8, NOTE_G4,8, NOTE_GS4,16, NOTE_AS4,16, NOTE_C5,8, NOTE_G4,8, NOTE_GS4,16, NOTE_AS4,16,
  
  REST,4, NOTE_GS5,16, NOTE_AS5,16, NOTE_C6,8, NOTE_G5,8, NOTE_GS5,16, NOTE_AS5,16,
  NOTE_C6,8, NOTE_G5,16, NOTE_GS5,16, NOTE_AS5,16, NOTE_C6,8, NOTE_G5,8, NOTE_GS5,16, NOTE_AS5,16,  
};

int notes_1 = sizeof(melody_1) / sizeof(melody_1[0]) / 2;
int notes_2 = sizeof(melody_2) / sizeof(melody_2[0]) / 2;

int whole_note = (60000 * 4) / tempo;

volatile int divider = 0;
volatile int note_duration = 0;
volatile int current_note = 0;

enum {
  PLAYER1,
  PLAYER2,
  NONE
} win_state;

volatile int beep_time = 0;
volatile int current_time = 0;

volatile int winner = NONE;

volatile bool beeped = false;
volatile bool song_playing = false;
volatile bool winner_displayed = false;
volatile bool led_activated = false;
volatile bool clean_display = false;

void ICACHE_RAM_ATTR interrupt_reset() {
  digitalWrite(player_1_led, LOW);
  digitalWrite(player_2_led, LOW);

  divider = 0;
  note_duration = 0;
  current_note = 0;

  current_time = millis();
  beep_time = current_time + random(1000, 5000);

  winner = NONE;

  beeped = false;
  song_playing = false;
  winner_displayed = false;
  led_activated = false;
  clean_display = true;
}

void ICACHE_RAM_ATTR interrupt_player_1() {
  if (!song_playing) {
    if (current_time < beep_time) {
      winner = PLAYER2;
      beeped = true;
    } else {
      winner = PLAYER1;
    }

    song_playing = true;
  }
}

void ICACHE_RAM_ATTR interrupt_player_2() {
  if (!song_playing) {
    if (current_time < beep_time) {
      winner = PLAYER1;
      beeped = true;
    } else { 
      winner = PLAYER2;
    }

    song_playing = true;
  }
}

void play_song(int *melody, int *notes) {
  if (current_note < *notes * 2) {
    song_playing = true;
    
    // calculates the duration of each note
    divider = melody[current_note + 1];
    if (divider > 0) {
      // regular note, just proceed
      note_duration = (whole_note) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      note_duration = (whole_note) / abs(divider);
      note_duration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[current_note], note_duration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(note_duration);

    // stop the waveform generation before the next note.
    noTone(buzzer);

    current_note = current_note + 2;
  } else {
    song_playing = false;
  }
}

void display_winner(int reaction) {
  display.clearDisplay();

  display.setCursor(0,0);

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  if (winner == PLAYER1) {
    String string = "P1 ganhou!";
    Serial.println(string);
    display.println(string);
  } else {
    String string = "P2 ganhou!";
    Serial.println(string);
    display.println(string);
  }

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  if (reaction < 0) {
    String string = "\nConcorrente queimou\na largada!";
    Serial.println(string);
    display.println(string);
  } else {
    String string = "\nTempo: " + String(reaction) + " ms.";
    Serial.println(string);
    display.println(string);
  }

  display.display();

  winner_displayed = true;
}

void activate_led() {
  if (winner == PLAYER1) {
    digitalWrite(player_1_led, HIGH);
  } else {
    digitalWrite(player_2_led, HIGH);
  }

  led_activated = true;
}

void setup() {
  Serial.begin(9600);

  pinMode(buzzer, OUTPUT);

  pinMode(reset_btn, INPUT_PULLDOWN_16);
  pinMode(player_1_btn, INPUT_PULLDOWN_16);
  pinMode(player_2_btn, INPUT_PULLDOWN_16);

  pinMode(player_1_led, OUTPUT);
  pinMode(player_2_led, OUTPUT);

  /* Liga os LEDs para testar */

  digitalWrite(player_1_led, HIGH);
  digitalWrite(player_2_led, HIGH);

  /* Adafruit */

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.display();
  delay(2000); // Pause for 2 seconds

  /* Desliga o teste dos LEDs */

  digitalWrite(player_1_led, LOW);
  digitalWrite(player_2_led, LOW);

  /* Conecta interrupções */

  attachInterrupt(digitalPinToInterrupt(player_1_btn), interrupt_player_1, RISING);
  attachInterrupt(digitalPinToInterrupt(player_2_btn), interrupt_player_2, RISING);
  attachInterrupt(digitalPinToInterrupt(reset_btn), interrupt_reset, RISING);

  /* Define primeiro tempo de beep */

  beep_time = millis() + random(1000, 5000);
}

void loop() {
  current_time = millis();

  if (current_time >= beep_time && !beeped) {
    digitalWrite(player_1_led, HIGH);
    digitalWrite(player_2_led, HIGH);

    tone(buzzer, 262, 200);

    digitalWrite(player_1_led, LOW);
    digitalWrite(player_2_led, LOW);

    beeped = true;
  }

  if (winner != NONE && !winner_displayed) {
    display_winner(current_time - beep_time);
  }

  if (winner != NONE && song_playing) {
    if (winner == PLAYER1) {
      play_song(melody_1, &notes_1);
    } else { 
      play_song(melody_2, &notes_2);
    }
  }

  if (winner != NONE && !led_activated) {
    activate_led();
  }

  if (clean_display) {
    display.clearDisplay();
    display.display();
    clean_display = false;
  }
}
