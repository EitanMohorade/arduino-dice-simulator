# 🎲 Arduino Dice Simulator

Simulador de dados con Arduino, pantalla LCD y botones físicos.

## 📌 Descripción

Este proyecto permite simular distintos tipos de dados (D4, D6, D8, D10, D12, D20) usando:

* Una pantalla LCD 16x2
* Dos botones:

  * **MODE**: cambia el tipo de dado
  * **ROLL**: lanza el dado

El resultado se muestra en la pantalla.

---

## 🧠 Funcionamiento

* El sistema comienza en **D6**
* Con el botón MODE se cicla entre los dados disponibles
* Con el botón ROLL se genera un número aleatorio según el dado seleccionado

---

## 🧩 Hardware utilizado

* Arduino UNO
* Pantalla LCD 16x2 (modo paralelo)
* 2 botones
* Resistencias (para backlight o contraste)
* Protoboard + cables

---

## 🔌 Conexiones principales

### LCD (modo 4 bits)

| LCD | Arduino |
| --- | ------- |
| RS  | 12      |
| E   | 11      |
| D4  | 5       |
| D5  | 4       |
| D6  | 3       |
| D7  | 2       |

Otros:

* VSS → GND
* VDD → 5V
* RW → GND
* V0 → control de contraste

---

### Botones

| Botón | Pin Arduino |
| ----- | ----------- |
| MODE  | 6           |
| ROLL  | 7           |

Configurados con `INPUT_PULLUP`:

* Presionado = LOW
* Suelto = HIGH

---

## 💻 Código

Ubicado en:

```
src/dice_simulator.ino
```

---

## 🧪 Simulación

El proyecto incluye simulación en:

```
wokwi/
```

---

## 🚀 Cómo usar

1. Conectar el hardware
2. Subir el código al Arduino
3. Encender
4. Usar botones:

   * MODE → cambiar dado
   * ROLL → tirar dado

---

## ⚠️ Problemas comunes

* Pantalla no muestra nada:

  * Revisar contraste (V0)
  * Verificar conexiones RS/E/D4-D7
* Botones no responden:

  * Revisar GND común
  * Verificar INPUT_PULLUP
* Resultado errático:

  * Confirmar `randomSeed()`

---

## 📷 Referencias

Ver:

```
docs/circuitos.png
```


## 📄 Licencia

Libre para uso educativo y personal.
