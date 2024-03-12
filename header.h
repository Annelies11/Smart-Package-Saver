/*
<   === 5
OK  === 6
>   === 4
ijo === 10
biru=== 11
Cam === A0
L1  === A1
L2  === A2
L3  === A3
   */
#define tombol1 4
#define tombol2 5
#define tombol3 6
#define buzzer 13


String names[] = {"Zahra", "Anggita", "Arifina"}; 
uint8_t loker[] = {A1, A2, A3};
const int n = sizeof(names) / sizeof(names[0]);
int btnUp, btnDown, btnOk;
int j = 0; 
//void printResult(HUSKYLENSResult result);
uint8_t state = 0, menu = 0, menuTemp = 0;
bool isThere[n] = {0}, first = 0, face = 0;
unsigned long previousMillis = 0;  // will store last time LED was updated
byte customChar[] = {
  B10000,
  B11000,
  B11100,
  B11110,
  B11111,
  B11110,
  B11000,
  B10000
};
