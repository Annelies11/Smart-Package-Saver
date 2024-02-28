#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11); // RX, TX
//HUSKYLENS green line >> Pin 10; blue line >> Pin 11

#include "header.h"

void setup() {
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);
  pinMode(tombol1, INPUT_PULLUP);
  pinMode(tombol2, INPUT_PULLUP);
  pinMode(tombol3, INPUT_PULLUP);
//  lcd.setCursor(0,0);
//  lcd.print("Pilih Penerima :");
  mySerial.begin(9600);
  lcd.createChar(0, customChar);
  
//  while (!huskylens.begin(mySerial))
//    {
//      Serial.println(F("Begin failed!"));
//      Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
//      Serial.println(F("2.Please recheck the connection."));
//      delay(100);
//    }
   
}

void loop() {
  //Serial.println(String()+btnUp+F(" : ")+btnDown+F(" : ")+j+F(" : ")+n);
  //checkHusky();
  first = 0;
  const long interval = 2000;  // interval at which to blink (milliseconds)
  j = 0;
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.write(0);
  menuTemp = 1;
  
  // Menu Awal
  while(menu == 0){  
    btnUp = digitalRead(tombol1);
    btnDown = digitalRead(tombol2);
    btnOk = digitalRead(tombol3);
    lcd.setCursor(1,0);
    lcd.print("Anda Sebagai :");
    lcd.setCursor(1,1);
    lcd.print("Kurir");
    lcd.setCursor(8,1);
    lcd.print("Penerima");
    if(btnUp == 0){
      lcd.setCursor(0,1);
      lcd.print(" ");
      lcd.setCursor(7,1);
      lcd.write(0);
      delay(500);
      menuTemp = 2;         
    }
    if(btnDown == 0){
      lcd.setCursor(0,1);
      lcd.write(0);
      lcd.setCursor(7,1);
      lcd.print(" ");    
      delay(500);   
      menuTemp = 1;
    }
    if(btnOk == 0){
      delay(500);
      menu = menuTemp;
      lcd.clear();
      if(menu == 1){
        lcd.setCursor(0,0);
        lcd.print("Pilih Penerima :");
      }
    }
  }

  //Menu Kurir
  while(menu == 1){
    btnUp = digitalRead(tombol1);
    btnDown = digitalRead(tombol2);
    btnOk = digitalRead(tombol3);   
    if(btnUp == 0){
      if(j == n-1){
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,0);
        lcd.print("The End Of List");
      } else {
        j++;  
        delay(500);
        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(0,0);
        lcd.print("Pilih Penerima :");
      }
    }
    if(btnDown == 0){
      if(j <= 0){
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,0);
        lcd.print("The End Of List");
      } else {
        j--;  
        delay(500);
        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(0,0);
        lcd.print("Pilih Penerima :");
      }
    }
    if(btnOk == 0){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Status : ");
      delay(500);
      if(isThere[j] == 0){
        lcd.setCursor(0,1);
        lcd.print("Bisa Masuk");
        delay(1000);
        lcd.clear();
        bool out = 0;
        uint8_t msg = 1;
        while(out == 0){
          btnOk = digitalRead(tombol3); 
          unsigned long currentMillis = millis();
          if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            if(msg == 1){
              msg = 2;
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Paket ");
              lcd.setCursor(6,0);
              lcd.print(names[j]);
              lcd.setCursor(0,1);
              lcd.print("Loker nomor : ");
              lcd.setCursor(14,1);
              lcd.print(j+1);
            } else {
              msg = 1;
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Tekan OK untuk");
              lcd.setCursor(0,1);
              lcd.print("mengunci loker.");
            }
          }
          if(btnOk == 0){
            delay(500);
            out = 1;
          }
        }
        isThere[j] = 1;
      } else if(isThere[j] == 1){
        lcd.setCursor(0,1);
        lcd.print("Tidak Bisa Masuk");
        delay(1000);
        lcd.clear();
        for(int i = 0; i < 3; i++){
          lcd.setCursor(0,0);
          lcd.print("Paket ");
          lcd.setCursor(6,0);
          lcd.print(names[j]);
          lcd.setCursor(0,1);
          lcd.print("Tidak Bisa Masuk");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Penerima Belum");
          lcd.setCursor(0,1);
          lcd.print("Ambil paket");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("sebelumnya");
          delay(1000);
          lcd.clear();
        } 
      }
      delay(500);
      menu = 0; 
      lcd.clear();
    }
    lcd.setCursor(0,1);
    lcd.print(String()+(j+1)+F(". ")+names[j]);
  }

  //Menu Penerima
  while(menu == 2){
    btnOk = digitalRead(tombol3);
    uint8_t msg = 1;
    previousMillis = 0;
    while (!huskylens.begin(mySerial)){
      btnOk = digitalRead(tombol3); 
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
            if(msg == 1){
              msg = 2;
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Huskylens tidak");
              lcd.setCursor(0,1);
              lcd.print("terdeteksi");  
            } else {
              msg = 1;
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Sambungkan Husky");
              lcd.setCursor(0,1);
              lcd.print("lens sekarang."); 
            }
          }
          if(btnOk == 0){
          delay(500);
          menu = 0;
          first = 0; 
          break;
          lcd.clear();
          }
      }
      if(huskylens.begin(mySerial)){
        if(first == 0){
          lcd.clear();
          first = 1;
        } else {
          face = 1;
          lcd.setCursor(0,0);
          lcd.print("Kamera Aktif");
          delay(1000); 
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Hadap ke kamera");
          while(face == 1){
            if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
            else if(!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
            else if(!huskylens.available()){
              Serial.println(F("No block or arrow appears on the screen!"));
              if(state != 1){
                state = 1;
                lcd.setCursor(0,1);
                lcd.print("                ");  
              }   
              lcd.setCursor(0,1);
              lcd.print("Tidak Terdeteksi");
            }
            else {
              while (huskylens.available()) {
                HUSKYLENSResult result = huskylens.read();
                Serial.println(result.ID);
                if(result.ID == 0){
                  if(state != 2){
                    lcd.setCursor(0,1);
                    lcd.print("                ");
                    state = 2;
                  }
                  lcd.setCursor(0,1);
                  lcd.print("Tidak Dikenal");                      
                } else {
                  if(state != 3){
                    lcd.setCursor(0,1);
                    lcd.print("                ");
                    state = 3;
                  }
                  lcd.setCursor(0,1);
                  lcd.print(names[result.ID-1]);
                  isThere[result.ID-1] = 0;
                  delay(2000);
                  lcd.clear();
                  lcd.setCursor(0,0);
                  lcd.print("Silakan ambil");
                  lcd.setCursor(0,1);
                  lcd.print("                ");
                  delay(2000);
                  lcd.clear();   
                  face = 0;
                  menu = 0;
                }
                if(face == 0){
                  break;
                }   
              }    
              }
          }        
          if(btnOk == 0){
            delay(500);
            menu = 0; 
            lcd.clear();
          }  
        }
      }
    }
}
