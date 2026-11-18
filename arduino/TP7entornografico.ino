const int pinE1 = 2;
const int pinE2 = 3;
const int pinL1 = 8;
const int pinL2 = 9;

int estadoE1 = 0;
int estadoE2 = 0;
int estadoL1 = 0;
int estadoL2 = 0;

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
  int lecturaE1 = !digitalRead(pinE1);
  int lecturaE2 = !digitalRead(pinE2);

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
