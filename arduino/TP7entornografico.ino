// Pines de Entradas (Pulsadores)
const int pinE1 = 2;
const int pinE2 = 3;

// Pines de Salidas (LEDs)
const int pinL1 = 8;
const int pinL2 = 9;

// Estados actuales (0 = BAJO/APAGADO, 1 = ALTO/ENCENDIDO)
int estadoE1 = 0;
int estadoE2 = 0;
int estadoL1 = 0;
int estadoL2 = 0;

// Variables para detectar flancos (antirrebote)
int ultimoE1 = 0;
int ultimoE2 = 0;
unsigned long tiempoAntirrebote = 0;
const unsigned long delayDebounce = 50;

unsigned long ultimoEnvio = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(pinE1, INPUT_PULLUP);
  pinMode(pinE2, INPUT_PULLUP);
  
  pinMode(pinL1, OUTPUT);
  pinMode(pinL2, OUTPUT);
  
  digitalWrite(pinL1, LOW);
  digitalWrite(pinL2, LOW);
}

void loop() {
  // 1. Leer entradas físicas (invertimos porque INPUT_PULLUP lee LOW al presionar)
  int lecturaE1 = !digitalRead(pinE1);
  int lecturaE2 = !digitalRead(pinE2);

  // 2. Detectar pulsación física para conmutar las salidas (Punto 3 del TP)
  if ((millis() - tiempoAntirrebote) > delayDebounce) {
    if (lecturaE1 == 1 && ultimoE1 == 0) {
      estadoL1 = !estadoL1;
      digitalWrite(pinL1, estadoL1);
      tiempoAntirrebote = millis();
      enviarEstados();
    }
    if (lecturaE2 == 1 && ultimoE2 == 0) {
      estadoL2 = !estadoL2;
      digitalWrite(pinL2, estadoL2);
      tiempoAntirrebote = millis();
      enviarEstados();
    }
  }
  ultimoE1 = lecturaE1;
  ultimoE2 = lecturaE2;
  estadoE1 = lecturaE1;
  estadoE2 = lecturaE2;

  // 3. Escuchar comandos desde Processing (Punto 2 del TP)
  if (Serial.available() > 0) {
    char comando = Serial.read();
    if (comando == '1') {
      estadoL1 = !estadoL1;
      digitalWrite(pinL1, estadoL1);
      enviarEstados();
    } else if (comando == '2') {
      estadoL2 = !estadoL2;
      digitalWrite(pinL2, estadoL2);
      enviarEstados();
    }
  }

  // 4. Enviar actualización periódica a Processing para mantener sincronía
  if (millis() - ultimoEnvio >= 100) {
    enviarEstados();
    ultimoEnvio = millis();
  }
}

void enviarEstados() {
  Serial.print(estadoE1);
  Serial.print(",");
  Serial.print(estadoE2);
  Serial.print(",");
  Serial.print(estadoL1);
  Serial.print(",");
  Serial.println(estadoL2);
}