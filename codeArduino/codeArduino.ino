#include <Servo.h>
Servo myservo;

#define A 2  //Motor 1 A
#define B 3  //Motor 1 B
#define F 7  //Rele 1
#define S1 13  //Servo 1 

int confi_capturar_foto;  // 0 no capture -- 1 capture
int confi_para_prediccion; // 0 no predict -- 1 predict
int sensor_Infra_Value = 0;
char dataReciver;

void init_Var(){
  digitalWrite(F, HIGH);
  myservo.write(170);
  confi_capturar_foto = 0; 
  confi_para_prediccion = 0; 
  
}
void setup() {
  Serial.begin(9600);
  myservo.attach(S1);
  pinMode(F, OUTPUT);

  init_Var();
}

void loop() {
  
  if (Serial.available()>0) {
    dataReciver = Serial.read();
  }
 
  sensor_Infra_Value = analogRead(0);
  switch (dataReciver){
    case 'u':
        //muevo servo
        dataReciver = " ";
        //Serial.print("uno");
        confi_para_prediccion = 1;
        myservo.write(100);
        if (sensor_Infra_Value > 1020){
           analogWrite(B, 0); 
           analogWrite(A, 255);     
        }
        delay(3000); // medir tiempo de caida
        //servo posicion original
        myservo.write(170);
    
    break;
    case 'n':
        dataReciver = " ";
        confi_para_prediccion = 1;
        if (sensor_Infra_Value > 1020){
           analogWrite(B, 0); 
           analogWrite(A, 255);     
        }
        delay(3000);
    break;
    case 's':
        analogWrite(B, 0); 
        analogWrite(A, 0); 
    break;
    case 'a': //confirmacion de foto tomada
      confi_capturar_foto = 1;
    break;
  }
    //mueve motor asta detectar objetos
    //Serial.println(sensorValue);
  if (sensor_Infra_Value < 1020){
     Serial.print("c"); // no hay objeto 
     analogWrite(B, 0); 
     analogWrite(A, 255);
     
     
     confi_capturar_foto = 0; 
     confi_para_prediccion = 0;  
  }else{
    //para el motor
     analogWrite(B, 0); 
     analogWrite(A, 0); 

     if (confi_capturar_foto == 0){
        Serial.print("m");
     }else if(confi_capturar_foto == 1 && confi_para_prediccion ==0){
        Serial.print("p");
     }
      
  }
  //Serial.println(sensor_Infra_Value);
  // m confirmacion para tomar foto
  // p activar predict
  // c continua la banda no hay objeto
  // a confirmacion de foto tomada
  // n recibio dato de nano
  // u recibio dato de uno
  // s paro de emergencia
}
