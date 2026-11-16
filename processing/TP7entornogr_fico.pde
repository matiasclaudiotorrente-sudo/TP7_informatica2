import processing.serial.*;

Serial puerto;

int e1 = 0, e2 = 0;
int l1 = 0, l2 = 0;


float xL1 = 350, yL1 = 270, radioL = 45;
float xL2 = 500, yL2 = 270;

void setup() {
  size(650, 400);
  textAlign(CENTER, CENTER);
  
 
  printArray(Serial.list());
  
 
  if (Serial.list().length > 0) {
    String nombrePuerto = Serial.list()[1]; 
    puerto = new Serial(this, nombrePuerto, 9600);
    puerto.bufferUntil('\n');
  } else {
    println("No se detectó ningún puerto COM conectado.");
  }
}

void draw() {
  background(255);
  
  stroke(60, 90, 120);
  strokeWeight(2);
  fill(130, 165, 205);
  rect(80, 100, 160, 50);
  fill(0);
  textSize(20);
  text("Entradas", 160, 125);

 
  stroke(0);
  strokeWeight(3);
  if (e1 == 1) fill(50, 220, 80); 
  else fill(255);                 
  rect(305, 100, 90, 50);
  fill(0);
  text("E1", 350, 125);

  
  if (e2 == 1) fill(50, 220, 80);
  else fill(255);
  rect(455, 100, 90, 50);
  fill(0);
  text("E2", 500, 125);

  
  stroke(150, 120, 100);
  strokeWeight(2);
  fill(250, 230, 215);
  rect(80, 245, 160, 50);
  fill(0);
  text("Salidas", 160, 270);

  
  stroke(0);
  strokeWeight(3);
  if (l1 == 1) fill(255, 60, 60); 
  else fill(255);                
  ellipse(xL1, yL1, radioL * 2, radioL * 2);
  fill(0);
  text("L1", xL1, yL1);

  if (l2 == 1) fill(255, 210, 40); 
  else fill(255);                  
  ellipse(xL2, yL2, radioL * 2, radioL * 2);
  fill(0);
  text("L2", xL2, yL2);

}

void mousePressed() {
  if (puerto == null) return;
  
  if (dist(mouseX, mouseY, xL1, yL1) <= radioL) {
    puerto.write('1');
  } else if (dist(mouseX, mouseY, xL2, yL2) <= radioL) {
    puerto.write('2');
  }
}


void serialEvent(Serial p) {
  String linea = p.readStringUntil('\n');
  if (linea != null) {
    linea = trim(linea);
    String[] datos = split(linea, ',');
    if (datos.length == 4) {
      e1 = int(datos[0]);
      e2 = int(datos[1]);
      l1 = int(datos[2]);
      l2 = int(datos[3]);
    }
  }
}
