#include "SoftwareSerial.h" //incluindo a biblioteca SoftwareSerial
#define ENA 5; // ativa motor motor A
#define IN1 2; // Sentido de rotação horaria motor A
#define IN2 3; // Sentido de rotação antihoraria motor A

#define ENB 6; // ativa motor motor B
#define IN3 4; // Sentido de rotação horaria motor B
#define IN4 7; // Sentido de rotação antihoraria motor B

#define RXD	11; // receptor de dados
#define TXD 10; //transmissor de dados
#define TR_MDC 9; // ativa motor arma



SoftwareSerial bluetooth(TXD,RXD); //criando uma nova série de software
//TX, RX (Bluetooth)
const int ledpin = 13; //pino do LED Conectado
int incomingByte;  //criei uma variavel para ler os dados da serial recebidos


void setup(){
bluetooth.begin(9600); //Inicia Software Serial
pinMode(ledPin, OUTPUT); //Inicializa o pino do LED como uma saída:

//Serial.begin(9600); //inicia a porta serial, com a taxa de dados = 9600 bps
// Motor arma
pinMode(TR_MDC, OUTPUT);

//Ponte H -  motor A
analogWrite(ENA,0);
pinMode(ENA, OUTPUT);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);

//Ponte H -  motor B
analogWrite(ENB,0);
pinMode(ENB, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);

// configuração bluetooth
pinMode(RXD, OUTPUT);
pinMode(TXD, OUTPUT);
}

void loop(){
    // veja se há dados seriais recebidos:
    if(bluetooth.available() > 0){
        // leia o byte mais antigo no buffer serial:
        incomingByte = bluetooth.read();
        // se for um H maiúsculo (ASCII 72)
        //Carrinho vai para Frente
        if (incomingByte == 'F') {
            andarFrente();
            bluetooth.println("MOVIMENTO: Frente");
        }
        // se for um L (ASCII 76)
        //Carrinho vai para Trás
        if (incomingByte == 'R') {
            andarTras();
            bluetooth.println("MOVIMENTO: Ré");
        }
        //Carrinho vai para o lado direito
        if (incomingByte == 'D') {
            andarLadoDireito();
            bluetooth.println("MOVIMENTO: Lado Direito");
        }
        //Carrinho vai para o lado esquerdo
        if (incomingByte == 'E') {
            andarLadoEsquerdo();
            bluetooth.println("MOVIMENTO: Lado Esquerdo");
        }
        if (incomingByte == 'L') {
            ligarArma();
            bluetooth.println("Ação: Ligar Arma");
        }
        if (incomingByte == 'A') {
            desligarArma();
            bluetooth.println("Ação: desligar Arma");
        }
    }
	
}
void andarFrente(){
    analogWrite(ENA,255);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    analogWrite(ENB,255);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    delay(100);
}
void andarTras(){
    analogWrite(ENA,255);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    analogWrite(ENB,255);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    delay(100);
}
void andarLadoDireito(){
    analogWrite(ENA,255);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    analogWrite(ENB,0);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    delay(100);
}
void andarLadoEsquerdo(){
    analogWrite(ENA,0);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    analogWrite(ENB,255);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    delay(100);
}
void ligarArma(){
digitalWrite(TR_MDC,HIGH);
delay(100);
}
void desligarArma(){
digitalWrite(TR_MDC,LOW);
delay(100);
}

