#include <LiquidCrystal.h>
#include <Servo.h>

// ---------------- LCD 16x2 (paralelo) ----------------
// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

// ---------------- Servo ----------------
Servo servo;
#define SERVO_PIN 6

// ---------------- Joystick ----------------
#define JOY_X A0     // esquerda/direita (HORZ)
#define JOY_Y A1     // opcional (VERT)
#define JOY_SEL 2    // opcional (clique)

// ---------------- Parâmetros ----------------
int angulo = 90;                 // arranca ao meio
const int ANG_MIN = 0;
const int ANG_MAX = 180;

// Centro do ADC (aprox.)
const int ADC_CENTER = 512;

// Zona morta (ajustar consoante joystick)
const int DEADZONE = 120;         // 80..180 típico

// Controlo de repetição
unsigned long tStep = 0;

// Para evitar “flicker” no LCD
int lastShownAngle = -1;
char lastDir = '?';

// ---------------------------------------------------------
void setup() {
  pinMode(JOY_SEL, INPUT_PULLUP); // fica preparado, se quiseres usar

  servo.attach(SERVO_PIN);
  servo.write(angulo);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Joystick + Servo");
  lcd.setCursor(0, 1);
  lcd.print("Angulo: 090 deg");
  delay(1200);
  lcd.clear();
}

// ---------------------------------------------------------
// Calcula direcção e “força” do joystick no eixo X
// Retorna: dir = 'L', 'R' ou 'C' (centro)
// e também devolve magnitude (0..511)
char lerDireccaoX(int &mag) {
  int x = analogRead(JOY_X);
  int delta = x - ADC_CENTER;

  if (delta > DEADZONE) {      // esquerda (no Wokwi, HORZ 1023=left)
    mag = delta;
    return 'L';
  }
  if (delta < -DEADZONE) {     // direita (no Wokwi, HORZ 0=right)
    mag = -delta;
    return 'R';
  }

  mag = 0;
  return 'C';
}

// ---------------------------------------------------------
// Define intervalo entre passos em função do desvio do joystick
// quanto mais desviado, mais rápido
unsigned long intervaloPorMag(int mag) {
  // mag ~ 0..511
  // perto do limite: 50 ms (rápido)
  // pouco desvio:   220 ms (lento)
  if (mag < 0) mag = 0;
  if (mag > 511) mag = 511;
  return (unsigned long)map(mag, 0, 511, 220, 50);
}

// ---------------------------------------------------------
void mostrarLCD(int ang, char dir) {
  if (ang == lastShownAngle && dir == lastDir) return;

  lastShownAngle = ang;
  lastDir = dir;

  lcd.setCursor(0, 0);
  lcd.print("Control Servo   ");

  lcd.setCursor(0, 1);
  lcd.print("Angulo: ");

  // imprimir com 3 dígitos (000..180)
  if (ang < 100) lcd.print("0");
  if (ang < 10)  lcd.print("0");
  lcd.print(ang);

  lcd.print((char)223); // símbolo grau (muitos LCDs aceitam)
  lcd.print(" ");

  lcd.print("Dir:");
  lcd.print(dir);
  lcd.print(" ");
}

// ---------------------------------------------------------
void loop() {
  int mag = 0;
  char dir = lerDireccaoX(mag);

  // centro: não mexe
  if (dir == 'C') {
    mostrarLCD(angulo, 'C');
    delay(30);
    return;
  }

  // controlo de repetição conforme “força”
  unsigned long dt = intervaloPorMag(mag);
  unsigned long now = millis();

  if (now - tStep >= dt) {
    tStep = now;

    if (dir == 'L') angulo++;   // esquerda -> aumenta
    if (dir == 'R') angulo--;   // direita  -> diminui

    if (angulo < ANG_MIN) angulo = ANG_MIN;
    if (angulo > ANG_MAX) angulo = ANG_MAX;

    servo.write(angulo);
    mostrarLCD(angulo, dir);
  }

  delay(10);
}