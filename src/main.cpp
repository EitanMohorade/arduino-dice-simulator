#include <Arduino.h>
#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pines botones
const int btnRoll = 7;
const int btnMode = 6;

// Dados disponibles
int dados[] = {4, 6, 8, 10, 12, 20};
int indexDado = 1; // empieza en D6

// Control anti-rebote simple
unsigned long lastPressMode = 0;
unsigned long lastPressRoll = 0;
const int debounceDelay = 200;

// Prototipos
void mostrarEstado();
void tirarDado();


void setup() {
  pinMode(btnRoll, INPUT_PULLUP);
  pinMode(btnMode, INPUT_PULLUP);

  Serial.begin(9600);

  lcd.begin(16, 2);

  // Semilla random
  randomSeed(analogRead(A0));

  mostrarEstado();
}

void loop() {
  unsigned long now = millis();

  // Botón MODE
  if (digitalRead(btnMode) == LOW && (now - lastPressMode) > debounceDelay) {
    lastPressMode = now;

    indexDado = (indexDado + 1) % 6;
    mostrarEstado();

    Serial.println("MODE pressed");
  }

  // Botón ROLL
  if (digitalRead(btnRoll) == LOW && (now - lastPressRoll) > debounceDelay) {
    lastPressRoll = now;

    tirarDado();

    Serial.println("ROLL pressed");
  }
}

// Mostrar tipo de dado
void mostrarEstado() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dado: D");
  lcd.print(dados[indexDado]);

  lcd.setCursor(0, 1);
  lcd.print("Listo...");
}

// Tirar dado
void tirarDado() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Rolling...");

  delay(400);

  int resultado = random(1, dados[indexDado] + 1);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Resultado:");

  lcd.setCursor(0, 1);
  lcd.print(resultado);
}