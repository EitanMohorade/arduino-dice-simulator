#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int btnRoll = 7;
const int btnMode = 6;

int dados[] = {4, 6, 8, 10, 12, 20};
int indexDado = 1;

bool lastRollState = HIGH;
bool lastModeState = HIGH;

void setup() {
  pinMode(btnRoll, INPUT_PULLUP);
  pinMode(btnMode, INPUT_PULLUP);

  lcd.begin(16, 2);

  randomSeed(analogRead(A0));

  mostrarEstado();
}

void loop() {
  bool currentMode = digitalRead(btnMode);
  bool currentRoll = digitalRead(btnRoll);

  if (lastModeState == HIGH && currentMode == LOW) {
    indexDado = (indexDado + 1) % 6;
    mostrarEstado();
  }

  if (lastRollState == HIGH && currentRoll == LOW) {
    tirarDado();
  }

  lastModeState = currentMode;
  lastRollState = currentRoll;

  delay(20);
}

void mostrarEstado() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dado: D");
  lcd.print(dados[indexDado]);

  lcd.setCursor(0, 1);
  lcd.print("Listo...");
}

void tirarDado() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Rolling...");

  for (int i = 0; i < 10; i++) {
    int temp = random(1, dados[indexDado] + 1);

    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(temp);

    delay(80);
  }

  int resultado = random(1, dados[indexDado] + 1);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Resultado:");

  lcd.setCursor(0, 1);
  lcd.print(resultado);
}