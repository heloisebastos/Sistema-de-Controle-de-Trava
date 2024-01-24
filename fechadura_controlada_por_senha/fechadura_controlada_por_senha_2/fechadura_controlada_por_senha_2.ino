#include <Keypad.h> // Biblioteca do teclado
#include <Servo.h>//Biblioteca do servo motor
#include <LiquidCrystal_I2C.h> // biblioteca do lcd com o modulo i2c
LiquidCrystal_I2C lcd(0x27,16,2); 

int i=0;
int cont=0;
int buzzer =10;
const int ledRed = 12; //porta do led vermelho
const int ledGreen = 13; //porrta do led verde
Servo servoMotor; //objeto do tipo Servo
const String senha = "1234";
//String senha = "";


const byte ROWS = 4; //num de linhas do teclado
const byte COLS = 4; //num de colunas do teclado
char keys[ROWS][COLS] = { //declaracao dos caracteres do teclado
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS] = { 9, 8, 7, 6 }; // declaracao do pinos das linhas
byte colPins[COLS] = { 5, 4, 3, 2 }; //declaracao do pino das colunas
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {

  pinMode(ledRed, OUTPUT); //defini a porta do led red como saída
  pinMode(ledGreen, OUTPUT); //defini a porta do led red como saída
  pinMode(buzzer,OUTPUT);
  servoMotor.attach(11); //defini o porta para controle do servo motor
  servoMotor.write(0);
  //lcd.begin(16,2); //inicia o lcd
  lcd.init(); 
  digitalWrite(ledRed, HIGH);
  
  
}


void loop(){
  lcd.setBacklight(HIGH);// luz
  lcd.clear();
  lcd.print("digite a senha");
  String senhaDigitada = "";
  lcd.setCursor(0,1);

  while (senhaDigitada.length() < senha.length()) {
    char key = keypad.getKey();
    
    if (key) {
      senhaDigitada += key;
      lcd.print("*");
    }
  }
  
  if(senhaDigitada == senha) {
    
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
    lcd.clear();
    tone(buzzer,2500);
    delay(100);
    tone(buzzer,900);
    delay(100);
    lcd.print("Aberto");
    servoMotor.write(90);
    noTone(buzzer);
    delay(8000);
    lcd.clear();
    lcd.print("fechado");
    servoMotor.write(0);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    lcd.clear();
  } else {
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    lcd.clear();
    lcd.print("Senha Incorreta");
     tone(buzzer,300);
     delay(700);
     noTone(buzzer);
     delay(700);
     tone(buzzer,300);
     delay(1000);
     noTone(buzzer);
     delay(500);
    lcd.clear();
  }
 
}




		

  

