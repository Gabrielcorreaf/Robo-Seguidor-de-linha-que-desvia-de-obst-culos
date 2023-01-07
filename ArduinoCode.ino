/*PROGRAMA FINAL VEÍCULO SEGUIDOR DE LINHA*/

//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>

/*DECLARAÇÃO DE VARIAVEIS*/

/*MOTORES*/
#define MotorA_sentidoFrente 2 //Motor A para frente
#define MotorA_sentidoTras 4   //Motor A para tras
#define MotorB_sentidoFrente 8 //Motor B para frente
#define MotorB_sentidoTras 10 //Motor B para tras
#define MotorA_PWM 3 //Controla a velocidade Motor A
#define MotorB_PWM 9 //Controla a velocidade Motor A

/*SENSOR DE REFLETÂNCIA*/
#define Sensor_direita 6 //Sensor direito
#define Sensor_esquerda 7 //Sensor direito
bool direita, esquerda; //Tranforma em valores lógicos

/*SENSOR ULTRASONICO*/
#define pino_trigger 11 //Entrada do pulso ultrasônico
#define pino_echo 12 //Saída do pulso ultrasônico
Ultrasonic ultrasonic(pino_trigger, pino_echo);

/*LED*/
#define pino_led 13 //Pino do LED



/*Cria 4 níveis de velocidade*/
#define veloc0 0
#define veloc1 60
#define veloc2 80
#define veloc3 255

/*Configurações do sitema*/
void setup() {
  delay(5000); //Espera 5 segundos para iniciar
  Serial.begin(115200); //Frequência leitura dos dados
  /*Define pinos de entrada e saída*/
  pinMode(MotorA_sentidoFrente, OUTPUT);
  pinMode(MotorA_sentidoTras, OUTPUT);
  pinMode(MotorB_sentidoFrente, OUTPUT);
  pinMode(MotorB_sentidoTras, OUTPUT);
  pinMode(MotorA_PWM, OUTPUT);
  pinMode(MotorB_PWM, OUTPUT);
  pinMode(Sensor_direita, INPUT);
  pinMode(Sensor_esquerda, INPUT);
  pinMode(pino_led, OUTPUT); 

}

void loop() {
    //Le as informacoes do sensor
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);

  //Exibe informacoes no serial monitor

  Serial.print(cmMsec);
  direita = digitalRead(Sensor_direita);
  esquerda = digitalRead(Sensor_esquerda);
  Serial.println(direita);
  Serial.println(" || ");
  Serial.println(esquerda);

  delay(50);
  
  //Define o sentido de rotação dos motores
  digitalWrite(MotorA_sentidoFrente, HIGH);
  digitalWrite(MotorA_sentidoTras, LOW);
  digitalWrite(MotorB_sentidoFrente, HIGH);
  digitalWrite(MotorB_sentidoTras, LOW);

  //Leituras dos Sensores
 

  //Caso seja dectado um obstáculo a 5 cm:
  if (cmMsec <= 5.0) {
    digitalWrite(pino_led, HIGH); //acende o LED vermelho 


    analogWrite(MotorA_PWM, veloc0); //para
    analogWrite(MotorB_PWM, veloc0);
    delay(2000);
    analogWrite(MotorA_PWM, veloc0); 
    analogWrite(MotorB_PWM, veloc2);
    delay(1000);
    analogWrite(MotorA_PWM, veloc0); //para
    analogWrite(MotorB_PWM, veloc0);
    delay(1000);
    analogWrite(MotorA_PWM, veloc2); ////para frente
    analogWrite(MotorB_PWM, veloc2);
    delay(1000);
    analogWrite(MotorA_PWM, veloc0); //para
    analogWrite(MotorB_PWM, veloc0);
    delay(1000);
    analogWrite(MotorA_PWM, veloc2); //gira a 90º graus para direita
    analogWrite(MotorB_PWM, veloc0);
    delay(1000);
    analogWrite(MotorA_PWM, veloc0); //para
    analogWrite(MotorB_PWM, veloc0);
    delay(500);
    analogWrite(MotorA_PWM, veloc2); //para frente
    analogWrite(MotorB_PWM, veloc2);
    delay(1000);
    analogWrite(MotorA_PWM, veloc0); //para
    analogWrite(MotorB_PWM, veloc0);
    delay(1000);
    analogWrite(MotorA_PWM, veloc2); //gira a 90º graus para direita
    analogWrite(MotorB_PWM, veloc0);
    delay(1000);
    analogWrite(MotorA_PWM, veloc0); //para
    analogWrite(MotorB_PWM, veloc0);
    delay(1000);
    analogWrite(MotorA_PWM, veloc0); //gira a 90º graus para esquerda
    analogWrite(MotorB_PWM, veloc2);
    delay(1000);
    digitalWrite(pino_led, LOW); //Apaga o led
    
 
  } 
  //Caso o caminho esteja livre
  else {
  //Se detectar preto liga os 2 motores
  if (direita == true && esquerda == true) {
    analogWrite(MotorA_PWM, veloc2);
    analogWrite(MotorB_PWM, veloc2);
  //Se detectar a esquerda detectar branco, vira a esquerda
  } else if (direita == true && esquerda == false) {
    analogWrite(MotorA_PWM, veloc0); //para
    analogWrite(MotorB_PWM, veloc0);
    delay(100);
    analogWrite(MotorA_PWM, veloc0);
    analogWrite(MotorB_PWM, veloc2);
    delay(50);
  //Se detectar a direita detectar branco, vira a direita
  } else if (direita == false && esquerda == true) {
    analogWrite(MotorA_PWM, veloc0); //para
    analogWrite(MotorB_PWM, veloc0);
    delay(100);
    analogWrite(MotorA_PWM, veloc2);
    analogWrite(MotorB_PWM, veloc0);
    delay(50);
  //Se detectar os dois detectarem branco, vira a para
  } else if (direita == false && esquerda == false) {
    analogWrite(MotorA_PWM, veloc0);
    analogWrite(MotorB_PWM, veloc0);
  }
} }
