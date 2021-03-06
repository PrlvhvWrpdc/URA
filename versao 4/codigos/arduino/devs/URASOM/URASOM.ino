#include "SOMArduino.h"
#include "MoveRobo.h"
#include "Ultrassom.h"

MoveRobo mv; 
 
Ultrassom usf(3,2);  // ultrassom frontal 
Ultrassom use(7,6); // ultrassom esquerdo 
Ultrassom usd(9,8); // ultrassom direito 

int comandoAtual; 
int vSensores[SOM_MAX_F]; 

SOMArduino som; 

void testeFuncaoDistancia(){
  int vc[] = {18, 16, 55}; 
  int melhorLinha=0; 
  int melhorColuna=0; 
  som.melhorDistancia(vc,melhorLinha, melhorColuna); 
  Serial.print(melhorLinha);
  Serial.print(" - ");
  Serial.println(melhorColuna);  
}

void testeReposta() {
  int vc[] = {18, 68, 55}; 
  int melhorLinha=0; 
  int melhorColuna=0; 
  som.melhorDistancia(vc,melhorLinha, melhorColuna); 
  Serial.println(som.getLabel(melhorLinha,melhorColuna));
}

void testeMelhorResposta() {
  int vc[] = {18, 68, 22}; 
  Serial.println(som.melhorResposta(vc)); 
}

void testeRedeSOM(){
  vSensores[0] = use.dist();
  vSensores[1] = usf.dist(); 
  vSensores[2] = usd.dist(); 
  mv.ativaProximoCMD(); 
  
  char c = som.melhorResposta(vSensores); 

  Serial.println(c); 
  
  comandoAtual = mv.converteCharParaCmd(c);
  Serial.println( comandoAtual);
  mv.comandoTempo(comandoAtual,500);
}

void setup() {
  Serial.begin(9600); 
  comandoAtual = CMD_PARA; 
  mv.setup(5,4,1610,1460); 
  usf.setup();
  use.setup();
  usd.setup();
}

void loop() {
  delay(20); 
  //testeFuncaoDistancia(); 
  //testeReposta();  
  //testeMelhorResposta();
  testeRedeSOM(); 


}
