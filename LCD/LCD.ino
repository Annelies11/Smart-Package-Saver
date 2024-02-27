#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define tombol1 4
#define tombol2 5
#define tombol3 6

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

String names[] = {"Aku", "Kamu", "Dia", "Mereka"}; 
int n = sizeof(names) / sizeof(names[0]);
int btnUp, btnDown, btnOk;
int j = 0;  
void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);
  pinMode(tombol1, INPUT_PULLUP);
  pinMode(tombol2, INPUT_PULLUP);
  pinMode(tombol3, INPUT_PULLUP);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pilih Penerima :");
}


void loop()
{ 
  int cState = 0, lState = 0;
  btnUp = digitalRead(tombol1);
  btnDown = digitalRead(tombol2);
  btnOk = digitalRead(tombol3);
  Serial.println(String()+btnUp+F(" : ")+btnDown+F(" : ")+j+F(" : ")+n);
  if(btnUp == 0){
    if(j == n-1){
      lcd.setCursor(0,0);
      lcd.print("The End Of List");
    } else {
      j++;  
      delay(500);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Pilih Penerima :");
    }
    
  }
  if(btnDown == 0){
    if(j <= 0){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("The End Of List");
    } else {
      j--;  
      delay(500);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Pilih Penerima :");
    }
    
  }
  
  lcd.setCursor(0,1);
  lcd.print(String()+(j+1)+F(". ")+names[j]);
  if(btnOk == 0){
    lcd.setCursor(14,1);
    lcd.print("OK");
  } if(btnOk == 1) {
    lcd.setCursor(14,1);
    lcd.print("  ");
  }
}
