#define tombol1 4
#define tombol2 5
#define tombol3 6

String names[] = {"Zahra", "Anggita", "Pak Ivan", "Om Aris", "Abel"}; 
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
