//trabalho de sensores
//igor viana portella conrado lopes

#include <LiquidCrystal.h>

float vazao;          //Variável para armazenar o valor em L/min
double custo =0;      //Variável para o custo
float media = 0;      //Variável para fazer a média
int contaPulso;       //Variável para a quantidade de pulsos
int i = 0;            //Variável para segundos
int Min = 00;         //Variável para minutos
float metrocubico = 0; //Variável para Quantidade de agua m^3
float Litros = 0;     //Variável para Quantidade de agua L
float MiliLitros = 0; //Variavel para Conversão
int buzzer = 10;


//LiquidCrystal lcd(8, 7, 6, 5, 4, 3);
LiquidCrystal lcd(13, 12, 6, 5, 4, 3);

void setup()
{ 
  Serial.begin(9600);
  pinMode(buzzer,OUTPUT);  
  pinMode(8,OUTPUT); //vermelho
  pinMode(9,OUTPUT); //verde
  lcd.begin(16, 2);
  lcd.setCursor( 0, 0);
  lcd.print("Sensoriamento de");
  lcd.setCursor( 0, 1);
  lcd.print(" fluxo de Agua  ");
  delay(3000);
  lcd.clear();
  pinMode(2, INPUT);
  attachInterrupt(0, incpulso, RISING); //Configura o pino 2(Interrupção 0) interrupção
}


void loop ()
{
  vazao = contaPulso / 5.5; //Converte para L/min
  media = media + vazao;    //Soma a vazão para o calculo da media
  i++;

  MiliLitros = vazao / 60;
  Litros = Litros + MiliLitros;
  metrocubico = Litros / 1000;
  custo = metrocubico * 3.07;
  
  contaPulso = 0;//Zera a variável
  sei();         //Habilita interrupção
  delay (1000);  //Aguarda 1 segundo
  cli();         //Desabilita interrupção

  if (vazao == 0)
  {
  digitalWrite(8,HIGH); //vermelho
  digitalWrite(9,LOW);  //verde

  tone(buzzer,261);  
  
  lcd.setCursor(0,0);
  lcd.print(vazao);        //Escreve no display o valor da vazão
  lcd.print("L/min ");    //Escreve L/min
  lcd.print(""); 
  lcd.setCursor(10,0);
  lcd.print(Litros);        //Escreve no display o valor da vazão
  lcd.print("L");           //Escreve

  lcd.setCursor(0,1);
  lcd.print(metrocubico);
  //lcd.print(":");         //Escreve :
  //lcd.print(i);           //Escreve a contagem i (segundos)
  lcd.print("M^3"); 
  
  //lcd.setCursor(0,1);
  //lcd.print(Min);
  //lcd.print(":");         //Escreve :
  //lcd.print(i);           //Escreve a contagem i (segundos)
  //lcd.print("Min");    //Escreve :
  
  lcd.print(" "); 
  lcd.setCursor(10,10);
  lcd.print(custo);
  lcd.print("R$");
  }
  else
  {
  digitalWrite(9,HIGH);//verde
  digitalWrite(8,LOW); //vermelho
noTone(buzzer); 
  
  
  lcd.setCursor(0,0);
  lcd.print(vazao);        //Escreve no display o valor da vazão
  lcd.print("L/min ");    //Escreve L/min
  lcd.print(""); 
  lcd.setCursor(10,0);
  lcd.print(Litros);        //Escreve no display o valor da vazão
  lcd.print("L");           //Escreve

  lcd.setCursor(0,1);
  lcd.print(metrocubico);
  //lcd.print(":");         //Escreve :
  //lcd.print(i);           //Escreve a contagem i (segundos)
  lcd.print("M^3"); 
  
  //lcd.setCursor(0,1);
  //lcd.print(Min);
  //lcd.print(":");         //Escreve :
  //lcd.print(i);           //Escreve a contagem i (segundos)
  //lcd.print("Min");    //Escreve :
  
  lcd.print(" "); 
  lcd.setCursor(10,10);
  lcd.print(custo);
  lcd.print("R$");
  }
  
  
  

//  vazao = contaPulso / 5.5; //Converte para L/min
//  media = media + vazao;    //Soma a vazão para o calculo da media
//  i++;
//
//  MiliLitros = vazao / 60;
//  Litros = Litros + MiliLitros;
//  metrocubico = Litros / 1000;
//  custo = metrocubico * 3.07;
  

  
  }
  
 

  
  
// Neste conjunto de linhas fizemos a média das leituras obtidas a cada 1 minuto
//  if (i == 60)
//  {
//    Min++;
//    lcd.print(Min);
//
//    if (Min >= 60)
//    {
//      Min = 0;
//    }
//    media = media / 60;                    //faz a média
//    Serial.print("\nMedia por minuto = "); //Imprime a frase Media por minuto =
//    Serial.print(media);                   //Imprime o valor da media
//    Serial.println("L/min -");           //Imprime L/min
//    media = 0;                             //Zera a variável media para uma nova contagem
//    i = 0;                                 //Zera a variável i para uma nova contagem
//  }
   

void incpulso ()
{
  contaPulso++; //Incrementa a variável de pulsos
}
