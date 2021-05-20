#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int up = 10;
int down = 9;
int select = 8;
int menu = 1;
int LED = 7;
int x;


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(select, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  updateMenu();
}

void loop() {
  lcd.setCursor(0, 1);
  if (!digitalRead(down)){
    menu++;
    updateMenu();
    delay(100);
  }

  if (!digitalRead(up)){
    menu--;
    updateMenu();
    delay(100);
  }

  if(!digitalRead(select)){
    execute();
    updateMenu();
    delay(100);
  }
}

void updateMenu(){
  switch(menu){
    case 1:
    lcd.clear();
    lcd.print("->Encendido");
    lcd.setCursor(0,1);
    lcd.print("Apagado");
    break;
    case 2:
    lcd.clear();
    lcd.print("Encendido");
    lcd.setCursor(0,1);
    lcd.print("->Apagado");
    break;
    case 3:
    lcd.clear();
    lcd.print("->Gradual");
    lcd.setCursor(0,1);
    lcd.print("Parpadeante");
    break;
    case 4:
    lcd.clear();
    lcd.print("Gradual");
    lcd.setCursor(0,1);
    lcd.print("->Parpadeante");
    break;
    case 5:
    menu = 4;
    break;
  }
}

void execute(){
  switch(menu){
    case 1:
    action1();
    break;
    case 2:
    action2();
    break;
    case 3:
    action3();
    break;
    case 4:
    action4();
    break;
  }
}

void action1(){
  lcd.clear();
  lcd.print("->Encendido");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  
  digitalWrite(LED,HIGH);
  delay(500);
}

void action2(){
  lcd.clear();
  lcd.print("->Apagado");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  
  digitalWrite(LED,LOW);
  delay(500);
}

void action3(){
  lcd.clear();
  lcd.print("->Gradual");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  
 for(x=0;x<256; x+=5){ //Este ciclo es para encender gradualmente
 analogWrite(LED,x);   //Encender LED con intensidad establecida en x
 x = millis();
 }
for(x=0;x<256; x-=5){ //Este ciclo es para apagar gradualmente
 analogWrite(LED,x);   //Encender LED con intensidad establecida en x
 x = millis();
  delay(1500);
}
}

void action4(){
  lcd.clear();
  lcd.print("->Parpadeante");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  delay(1500);
}
 
