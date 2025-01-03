#sarinakasaiyan

#include <Keypad.h>
#include <LiquidCrystal.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const char* password = "1234"; // رمز عبور
int position = 0;
const int ledPin = 13; // پین LED
const int buzzerPin = 10; // پین بازر
int failedAttempts = 0; // شمارنده تلاش‌های ناموفق

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(ledPin, LOW); // قفل در ابتدا بسته است
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Enter Password:");
}

void loop() {
  char key = keypad.getKey();
  
  if (key != NO_KEY) {
    Serial.println(key);
    lcd.setCursor(position, 1);
    lcd.print('*');
    
    if (key == password[position]) {
      position++;
    } else {
      position = 0;
      failedAttempts++;
      lcd.clear();
      lcd.print("Wrong! Try again");
      delay(1000);
      lcd.clear();
      lcd.print("Enter Password:");
    }
    
    if (position == 4) {
      digitalWrite(ledPin, HIGH); // باز کردن قفل
      lcd.clear();
      lcd.print("Unlocked!");
      Serial.println("قفل باز شد");
      tone(buzzerPin, 1000, 500); // صدای باز شدن قفل
      delay(5000); // قفل برای 5 ثانیه باز می‌ماند
      digitalWrite(ledPin, LOW); // بستن مجدد قفل
      lcd.clear();
      lcd.print("Locked");
      Serial.println("قفل بسته شد");
      tone(buzzerPin, 500, 500); // صدای بسته شدن قفل
      position = 0;
      failedAttempts = 0;
      delay(1000);
      lcd.clear();
      lcd.print("Enter Password:");
    }
    
    if (failedAttempts >= 3) {
      lcd.clear();
      lcd.print("Locked Out!");
      tone(buzzerPin, 2000, 3000); // هشدار صوتی
      delay(30000); // قفل برای 30 ثانیه غیرفعال می‌شود
      failedAttempts = 0;
      lcd.clear();
      lcd.print("Enter Password:");
    }
  }
}
