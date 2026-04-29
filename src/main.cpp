#include <Arduino.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Botones
const int btnRoll = 7;
const int btnMode = 6;

// Tipos de dados
int dados[] = {4, 6, 8, 10, 12, 20};
int indexDado = 1; // D6 al inicio

// Para evitar clicks dobles
unsigned long lastPressMode = 0;
unsigned long lastPressRoll = 0;
const int debounceDelay = 200;

void mostrarEstado();
void tirarDado();
int generarNumeroRandom();

void setup() {
  pinMode(btnRoll, INPUT_PULLUP);
  pinMode(btnMode, INPUT_PULLUP);

  Serial.begin(9600);
  lcd.begin(16, 2);

  // Iniciar generador de números aleatorios
  randomSeed(analogRead(A0) + analogRead(A1) + millis());

  mostrarEstado();
}

void loop() {
  unsigned long now = millis();

  // Si presionan MODE, cambiar tipo de dado
  if (digitalRead(btnMode) == LOW && (now - lastPressMode) > debounceDelay) {
    lastPressMode = now;
    indexDado = (indexDado + 1) % 6;
    mostrarEstado();
    Serial.println("MODE pressed");
  }

  // Si presionan ROLL, tirar el dado
  if (digitalRead(btnRoll) == LOW && (now - lastPressRoll) > debounceDelay) {
    lastPressRoll = now;
    tirarDado();
    Serial.println("ROLL pressed");
  }
}

// Pantalla principal
void mostrarEstado() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dado: D");
  lcd.print(dados[indexDado]);
  lcd.setCursor(0, 1);
  lcd.print("Listo...");
}

// Generar número bien aleatorio
int generarNumeroRandom() {
  // Mezclar más para mejor aleatoriedad
  int ruido = analogRead(A0) + analogRead(A1);
  randomSeed(ruido + millis());
  
  // Descartar algunos valores
  for(int i = 0; i < 5; i++) {
    random(1, dados[indexDado] + 1);
  }
  
  return random(1, dados[indexDado] + 1);
}

// Animación de tirada
void tirarDado() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Rolling...");

  // Generar resultado ANTES
  int resultado = generarNumeroRandom();

  int velocidad = 50;
  int duracion = 15;

  for(int i = 0; i < duracion; i++) {
    lcd.setCursor(0, 1);
    lcd.print("     ");
    lcd.setCursor(0, 1);

    //  Si es el último frame entonces mostrar resultado real
    if(i == duracion - 1) {
      lcd.print(resultado);
    } else {
      lcd.print(random(1, dados[indexDado] + 1));
    }

    delay(velocidad);

    if(i > duracion - 5) {
      velocidad += 30;
    }
  }

  delay(200);

  // Mostrar resultado final centrado
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Resultado:");

  String texto = ">>> " + String(resultado) + " <<<";
  int offset = (16 - texto.length()) / 2;
  lcd.setCursor(offset, 1);
  lcd.print(texto);

  // Parpadeo
  for(int i = 0; i < 2; i++) {
    delay(150);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    delay(150);
    lcd.setCursor(offset, 1);
    lcd.print(texto);
  }
}