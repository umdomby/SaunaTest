
//Raspberry 3

//End Raspberry

//Arduino Mega Bluetooth RX1 TX1
 // 1 - INC - Arduino pin 3
 // 2 - U/D - Arduino pin 4
 // 4 - VSS - GND
 // 7 - CS  - Arduino pin 5
 // 8 - VCC - 5V
//#include <DigiPotX9Cxxx.h>
//DigiPot pot(3,4,5);
#define UD  4                          // выходы к которым подключен модуль
#define INC 3
#define CS  5

char customKey;
unsigned long previousMillis = 0;  //включение пара
unsigned long previousMillis2 = 0; //температура
unsigned long previousMillis3 = 0; //приём Serial
unsigned long previousMillis4 = 0; //таймер
unsigned long previousMillis5 = 0; //секундный таймер 
unsigned long previousMillis6 = 0; //душ виши
unsigned long previousMillis7 = 0; //душ виши
unsigned long previousMillis8 = 0; //душ виши     
  
boolean startOnOff = false;  
const long interval = 2000;    
boolean flagVibroStart = true;
boolean dParFlag = false;
boolean vTime = true; //milis(); срабатывает один раз
boolean vTime2 = true;
const int dVodaPar = 50; //датчик воды в парогенераторе
const int dVodaVanna = 48; //датчик воды в ванной
const int dVodaPar2 = 46; //датчик верхний в парогенераторе
int dVodaParData;
int dVodaPar2Data;
int dVodaVannaData;
char incomingbyte; // переменная для приема данных
char incomingbyteChar1,incomingbyteChar2,incomingbyteChar3;
String inData;
String inData3;
int dTUst; // установочная температура
int ustanovDushaVihi = 1;

int intstringData;
#include <OneWire.h>
OneWire ds(2);
OneWire ds2(6);
boolean flagSvet; //флаг кнопки вкл/откл света.
boolean flagVibro; //флаг кнопки вкл/откл света.
boolean flagVent; //флаг кнопки вкл/откл света.
boolean flagTimer; //флаг кнопки вкл/откл света.
boolean flagTimer2 = false; //флаг отображения таймера на дисплее
boolean dParIRFlag = false; //флаг установки температуры пара и IR

boolean flagVihi = false; //флаг кнопки вкл/откл света.
boolean flagVihiStatus = true;
int buttonVihiState;
//int buttonVihi = 51;

int timerTab = 5; //установка таймера
int timerTab2 = 0;
int Temp = 0; //Датчик температуры
int Temp2 = 0; //Датчик температуры воды

int vibro = 0;     //установка вибро
int svetSet = 10;  //установка света
int ustanovitPar = 35;  //установка пара
int ustanovitIR = 40;   //установка IR

boolean starTimer = false;
boolean flagIR = false;
boolean flagOnOff = false;
boolean flagPar = false;
boolean flagSecVishi = false;

unsigned long currentMillis;


//Button massive
String myStrings[] ={"a","b","c","d","e","1",String(Temp2),"g","h","i",String(vibro),String(timerTab),String(timerTab2),
String(Temp),String(ustanovitPar),String(ustanovitIR),"j","k","l","m","n","o","q","r"};
//String myStrings[20];
//String(Temp),String(ustanovitPar),String(ustanovitIR)};
//String myStrings2[]={"a","b","c","d","e","f","F","g","h","i",String(vibro),String(timerTab),String(timerTab2),
//String(Temp),String(ustanovitPar),String(ustanovitIR)};

String SerialData;


//End button massive
 
void setup() 
 {
  //Rasspberry
  //END Rasspberry
   Serial.begin(9600); 
   Serial1.begin(9600); 
   Serial2.begin(9600);
   Serial3.begin(9600);
   pinMode(dVodaPar, INPUT);
   pinMode(dVodaPar2, INPUT);
   pinMode(dVodaVanna, INPUT);
   //pinMode(buttonVihi, INPUT_PULLUP); //кнопка душа виши
   pinMode(22, OUTPUT);
   pinMode(23, OUTPUT);
   pinMode(24, OUTPUT);
   pinMode(25, OUTPUT);
   pinMode(26, OUTPUT);
   pinMode(27, OUTPUT);
   pinMode(28, OUTPUT);
   pinMode(29, OUTPUT);
   pinMode(30, OUTPUT);
   pinMode(31, OUTPUT);
   pinMode(32, OUTPUT);
   pinMode(33, OUTPUT);
   pinMode(34, OUTPUT);
   pinMode(35, OUTPUT);
   pinMode(36, OUTPUT);
   pinMode(37, OUTPUT);
   pinMode(52, OUTPUT);
   pinMode(53, OUTPUT);
   digitalWrite(22,HIGH);
   digitalWrite(23,HIGH);
   digitalWrite(24,HIGH);
   digitalWrite(25,HIGH);
   digitalWrite(26,HIGH);
   digitalWrite(27,HIGH);
   digitalWrite(28,HIGH);
   digitalWrite(29,HIGH);
   digitalWrite(30,HIGH);
   digitalWrite(31,HIGH);
   digitalWrite(32,HIGH);
   digitalWrite(33,HIGH);
   digitalWrite(34,HIGH);
   digitalWrite(35,HIGH);
   digitalWrite(36,HIGH);
   digitalWrite(37,HIGH);
   digitalWrite(52,LOW);  //Включение слива, при отключении СПА
   digitalWrite(53,HIGH); //Подача воды в парогенератор
   pinMode(INC, OUTPUT);
   pinMode(UD, OUTPUT);
   pinMode(CS, OUTPUT);


}

void loop() 
 { 


    if (flagVibroStart == true){
          for (int i=0; i < 100; i++) {
          delay(2);
          digitalWrite(UD, LOW);
          digitalWrite(INC, HIGH);
          digitalWrite(CS, LOW);
          delayMicroseconds(1);
          digitalWrite(INC, LOW);
          delayMicroseconds(1);
          digitalWrite(INC, HIGH);
          delayMicroseconds(1);
          digitalWrite(CS, HIGH);
       } 
         digitalWrite(UD, HIGH);digitalWrite(INC, HIGH);digitalWrite(CS, LOW);delayMicroseconds(1);digitalWrite(INC, LOW);
         delayMicroseconds(1);digitalWrite(INC, HIGH);delayMicroseconds(1);digitalWrite(CS, HIGH);
        
        digitalWrite(UD, HIGH);digitalWrite(INC, HIGH);digitalWrite(CS, LOW);delayMicroseconds(1);digitalWrite(INC, LOW);
        delayMicroseconds(1);digitalWrite(INC, HIGH);delayMicroseconds(1);digitalWrite(CS, HIGH);
          
      flagVibroStart = false;
    }

  
  currentMillis = millis();
  dVodaParData = digitalRead(dVodaPar);
  dVodaPar2Data = digitalRead(dVodaPar2);
  dVodaVannaData = digitalRead(dVodaVanna);

      if(dVodaVannaData == LOW){ 
         digitalWrite(32,HIGH);
         myStrings[18] = "l";
         } 

      if(dVodaParData == LOW && dParFlag == true && startOnOff == true){ 
         digitalWrite(53,LOW);
         }
         
      if(startOnOff == false || dParFlag == false ){ 
         digitalWrite(53,HIGH);
         }
          

      if(dVodaPar2Data == HIGH){ 
         digitalWrite(24,HIGH);
         myStrings[4] = "e";
         dParFlag = false;
         }

       if (buttonVihiState == LOW && flagVihiStatus == true && currentMillis - previousMillis >= 500) 
        {
          if (flagVihi == true) 
          {
          digitalWrite(27,LOW);
          Serial1.println("F");
          }
          else 
          {
          digitalWrite(27,HIGH);
          Serial1.println("f");
          }
          previousMillis = currentMillis;
          flagVihiStatus = false;
        }
          
        if (buttonVihiState == HIGH && flagVihiStatus == false && currentMillis - previousMillis >= 500){      
          flagVihi = !flagVihi;       
          //digitalWrite(27,HIGH);
          previousMillis = currentMillis;
          flagVihiStatus = true;
        }

//  Получить строковые данные от планшета  
  if(Serial1.available() > 0 || Serial2.available() > 0 || Serial3.available() > 0) // есть ли что-то в буфере
  //if(Serial1.available() > 0) // есть ли что-то в буфере
    {
        delay(6);
          incomingbyteChar1 = Serial1.read(); 
          incomingbyteChar2 = Serial2.read(); 
          incomingbyteChar3 = Serial3.read(); 
          
        //общий  
        if (incomingbyteChar1 == 'a' ||  incomingbyteChar2 == 'a' || incomingbyteChar3 == 'a'){    
            digitalWrite(22,HIGH);digitalWrite(23,HIGH);digitalWrite(24,HIGH);digitalWrite(25,HIGH);digitalWrite(26,HIGH);digitalWrite(27,HIGH);
            digitalWrite(28,HIGH);digitalWrite(29,HIGH);digitalWrite(52,LOW);
            digitalWrite(30,HIGH);digitalWrite(31,HIGH);digitalWrite(32,HIGH);digitalWrite(33,HIGH);digitalWrite(34,HIGH);digitalWrite(35,HIGH);
            digitalWrite(36,HIGH);digitalWrite(37,HIGH);
            startOnOff = false;dParFlag = false;flagVihi = false;flagIR = false;
            myStrings[0]= "a";myStrings[1] = "b";myStrings[2] = "c"; myStrings[3] = "d"; myStrings[4] = "e";myStrings[7] = "g";myStrings[8] = "h";
            myStrings[9] = "i";myStrings[16]= "j";myStrings[17] = "k";myStrings[18] = "l";myStrings[19] = "m";
            
        }
        if (incomingbyteChar1 == 'A' ||  incomingbyteChar2 == 'A' || incomingbyteChar3 == 'A'){        
            digitalWrite(22,LOW);digitalWrite(52,HIGH);startOnOff = true;dParFlag = false;
            myStrings[0]= "A";
        }
        //вентилятор
        if (incomingbyteChar1 == 'b' ||  incomingbyteChar2 == 'b' || incomingbyteChar3 == 'b'){   
         digitalWrite(23,HIGH);flagVent = false;
         myStrings[1] = "b";
        }
        if (incomingbyteChar1 == 'B' ||  incomingbyteChar2 == 'B' || incomingbyteChar3 == 'B'){      
         digitalWrite(23,LOW);flagVent = true;
         myStrings[1] = "B";
        }
        //свет
        if (incomingbyteChar1 == 'c' ||  incomingbyteChar2 == 'c' || incomingbyteChar3 == 'c'){   
         digitalWrite(26,HIGH);
         myStrings[2] = "c";
         flagSvet = false;
        }
        if (incomingbyteChar1 == 'C' ||  incomingbyteChar2 == 'C' || incomingbyteChar3 == 'C'){      
         digitalWrite(26,LOW);
         myStrings[2] = "C";
         flagSvet = true;
        }
        //IR
        if (incomingbyteChar1 == 'd' ||  incomingbyteChar2 == 'd' || incomingbyteChar3 == 'd'){ 
         flagIR = false;  
         digitalWrite(25,HIGH);
         myStrings[3] = "d";
        }
        if (incomingbyteChar1 == 'D' ||  incomingbyteChar2 == 'D' || incomingbyteChar3 == 'D'){
          if(flagVihi == false){
         flagIR = true;        
         digitalWrite(25,LOW);
         myStrings[3] = "D";
         dParFlag = false;   
         digitalWrite(24,HIGH);
         myStrings[4] = "e";
         digitalWrite(27,HIGH);
         myStrings[7] = "g";}
        }
        //пар
        if (incomingbyteChar1 == 'e' ||  incomingbyteChar2 == 'e' || incomingbyteChar3 == 'e'){
          flagPar = false;   
         dParFlag = false;   
         digitalWrite(24,HIGH);
         myStrings[4] = "e";
        }
        if (incomingbyteChar1 == 'E' ||  incomingbyteChar2 == 'E' || incomingbyteChar3 == 'E'){
          flagPar = true;      
         dParFlag = true;
         digitalWrite(25,HIGH);
         myStrings[3] = "d";
           if(dVodaParData == LOW && dVodaParData == HIGH){ 
           digitalWrite(53,LOW);
         }  
        }
//        if (incomingbyteChar1 == 'f' ||  incomingbyteChar2 == 'f' || incomingbyteChar3 == 'f'){   
//
//        }
//        if (incomingbyteChar1 == 'F' ||  incomingbyteChar2 == 'F' || incomingbyteChar3 == 'F'){      
//
//        }
        //душ виши
        if (incomingbyteChar1 == 'g' ||  incomingbyteChar2 == 'g' || incomingbyteChar3 == 'g'){   
         digitalWrite(27,HIGH); 
         flagVihi = false;
         myStrings[7] = "g";
        }
        if (incomingbyteChar1 == 'G' ||  incomingbyteChar2 == 'G' || incomingbyteChar3 == 'G'){      
         if(flagIR == false){ 
         digitalWrite(27,LOW);
         flagVihi = true;
         myStrings[7] = "G";
         }
        }
        //вибро
        if (incomingbyteChar1 == 'h' ||  incomingbyteChar2 == 'h' || incomingbyteChar3 == 'h'){   
         digitalWrite(28,HIGH);
         myStrings[8] = "h";
         flagVibro = false;  
         }
        if (incomingbyteChar1 == 'H' ||  incomingbyteChar2 == 'H' || incomingbyteChar3 == 'H'){      
         digitalWrite(28,LOW);
         myStrings[8] = "H";
         flagVibro = true;
        }
        //таймер
        if (incomingbyteChar1 == 'i' ||  incomingbyteChar2 == 'i' || incomingbyteChar3 == 'i'){   
            myStrings[9] = "i";
            starTimer = false;
            vTime2 = true;
            timerTab2 = timerTab;
            myStrings[12] = String(timerTab);
        }
        if (incomingbyteChar1 == 'I' ||  incomingbyteChar2 == 'I' || incomingbyteChar3 == 'I'){      
            myStrings[9] = "I";
            starTimer = true;        
        }
        //ванна хромотерапия
        if (incomingbyteChar1 == 'j' ||  incomingbyteChar2 == 'j' || incomingbyteChar3 == 'j'){   
         digitalWrite(30,HIGH);
         myStrings[16] = "j";
        }
        if (incomingbyteChar1 == 'J' ||  incomingbyteChar2 == 'J' || incomingbyteChar3 == 'J'){      
         digitalWrite(30,LOW);
         myStrings[16] = "J";
        }
        //ванна массаж
        if (incomingbyteChar1 == 'k' ||  incomingbyteChar2 == 'k' || incomingbyteChar3 == 'k'){   
         digitalWrite(31,HIGH);
         myStrings[17] = "k";
        }
        if (incomingbyteChar1 == 'K' ||  incomingbyteChar2 == 'K' || incomingbyteChar3 == 'K'){      
         digitalWrite(31,LOW);
         myStrings[17] = "K";
        }
        //ванна гидромассаж
        if (incomingbyteChar1 == 'l' ||  incomingbyteChar2 == 'l' || incomingbyteChar3 == 'l'){ 
         digitalWrite(32,HIGH);
         myStrings[18] = "l";
        }
        if (incomingbyteChar1 == 'L' ||  incomingbyteChar2 == 'L' || incomingbyteChar3 == 'L'){

         if(dVodaVannaData == HIGH){ 
         digitalWrite(32,LOW);
         myStrings[18] = "L";
         }  

        }
        //ванна пустая функция
        if (incomingbyteChar1 == 'm' ||  incomingbyteChar2 == 'm' || incomingbyteChar3 == 'm'){
         digitalWrite(33,HIGH);
         myStrings[19] = "m";
        }
        if (incomingbyteChar1 == 'M' ||  incomingbyteChar2 == 'M' || incomingbyteChar3 == 'M'){
         digitalWrite(33,LOW);
         myStrings[19] = "M";
        }
        
        //установка душа виши
        if (incomingbyteChar1 == 'n' ||  incomingbyteChar2 == 'n' || incomingbyteChar3 == 'n'){   
         //digitalWrite(34,HIGH);
         if(ustanovDushaVihi > 1){
         ustanovDushaVihi = ustanovDushaVihi-1;
         myStrings[5] = ustanovDushaVihi;}
        }
        if (incomingbyteChar1 == 'N' ||  incomingbyteChar2 == 'N' || incomingbyteChar3 == 'N'){      
         //digitalWrite(34,LOW);
         if(ustanovDushaVihi < 4){
         ustanovDushaVihi = ustanovDushaVihi+1;
         myStrings[5] = ustanovDushaVihi;}
        }
        
//        //установка душа виши 2
//        if (incomingbyteChar1 == 'o' ||  incomingbyteChar2 == 'o' || incomingbyteChar3 == 'o'){   
//         digitalWrite(35,HIGH);
//         myStrings[21] = "o";
//        }
//        if (incomingbyteChar1 == 'O' ||  incomingbyteChar2 == 'O' || incomingbyteChar3 == 'O'){      
//         digitalWrite(35,LOW);
//         myStrings[21] = "O";
//        }
//        //установка душа виши 3
//        if (incomingbyteChar1 == 'q' ||  incomingbyteChar2 == 'q' || incomingbyteChar3 == 'q'){ 
//         digitalWrite(36,HIGH);
//         myStrings[22] = "q";
//        }
//        if (incomingbyteChar1 == 'Q' ||  incomingbyteChar2 == 'Q' || incomingbyteChar3 == 'Q'){
//         digitalWrite(36,LOW);
//         myStrings[22] = "Q";
//        }
//        //установка душа виши 4
//        if (incomingbyteChar1 == 'r' ||  incomingbyteChar2 == 'r' || incomingbyteChar3 == 'r'){
//         digitalWrite(37,HIGH);
//         myStrings[23] = "r";
//        }
//        if (incomingbyteChar1 == 'R' ||  incomingbyteChar2 == 'R' || incomingbyteChar3 == 'R'){
//         digitalWrite(37,LOW);
//         myStrings[23] = "R";
//        }
        //установка вибро
        if (incomingbyteChar1 == 'v' ||  incomingbyteChar2 == 'v' || incomingbyteChar3 == 'v'){
          if(vibro < 10){++vibro; myStrings[10] = String(vibro);
          myStrings[10] = String(vibro);  
          digitalWrite(UD, HIGH);digitalWrite(INC, HIGH);digitalWrite(CS, LOW);delayMicroseconds(1);digitalWrite(INC, LOW);delayMicroseconds(1);
          digitalWrite(INC, HIGH);delayMicroseconds(1);digitalWrite(CS, HIGH);}           
         }
        //установка вибро
        if (incomingbyteChar1 == 'V' ||  incomingbyteChar2 == 'V' || incomingbyteChar3 == 'V'){ 
          if(vibro > 0){vibro--; myStrings[10] = String(vibro);
          digitalWrite(UD, LOW);digitalWrite(INC, HIGH);digitalWrite(CS, LOW);delayMicroseconds(1);digitalWrite(INC, LOW);delayMicroseconds(1);
          digitalWrite(INC, HIGH);delayMicroseconds(1);digitalWrite(CS, HIGH);}   
         }
        //установка таймера
        if (incomingbyteChar1 == 't' ||  incomingbyteChar2 == 't' || incomingbyteChar3 == 't'){
             if (timerTab >= 5) {
             timerTab = timerTab - 5; 
             myStrings[11] = String(timerTab);
            }
         }
        if (incomingbyteChar1 == 'T' ||  incomingbyteChar2 == 'T' || incomingbyteChar3 == 'T'){
            if(timerTab < 100){timerTab = timerTab + 5;
            myStrings[11] = String(timerTab);}
         }
        //установка пара
        if (incomingbyteChar1 == 'p' ||  incomingbyteChar2 == 'p' || incomingbyteChar3 == 'p'){   
             if (ustanovitPar >= 5) {
             ustanovitPar = ustanovitPar - 5; 
             myStrings[14] = String(ustanovitPar);}
        }
        if (incomingbyteChar1 == 'P' ||  incomingbyteChar2 == 'P' || incomingbyteChar3 == 'P'){      
            if(ustanovitPar <= 45)
            {ustanovitPar = ustanovitPar + 5;
            myStrings[14] = String(ustanovitPar);}
        }
        //установка IR
        if (incomingbyteChar1 == 'x' ||  incomingbyteChar2 == 'x' || incomingbyteChar3 == 'x'){   
             if (ustanovitIR >= 5) {
             ustanovitIR = ustanovitIR - 5; 
             myStrings[15] = String(ustanovitIR);}
        }
        if (incomingbyteChar1 == 'X' ||  incomingbyteChar2 == 'X' || incomingbyteChar3 == 'X'){      
            if(ustanovitIR <= 50)
            {ustanovitIR = ustanovitIR + 5;}
            myStrings[15] = String(ustanovitIR);
        }
        //установка света
        if (incomingbyteChar1 == 's' ||  incomingbyteChar2 == 's' || incomingbyteChar3 == 's'){ 
          if(flagSvet == true){  
            digitalWrite(26,HIGH);
            delay(1000);
            digitalWrite(26,LOW);}
        }
  }
             //управление Виши
            if(myStrings[5] == "1" && flagVihi == true){digitalWrite(34,LOW);digitalWrite(35,LOW);digitalWrite(36,LOW);digitalWrite(37,LOW);}
            
            if(flagVihi == false){digitalWrite(34,HIGH);digitalWrite(35,HIGH);digitalWrite(36,HIGH);digitalWrite(37,HIGH);}
  
            if (currentMillis - previousMillis6 >= 1000 && myStrings[5] == "2" && flagVihi == true)
              {    previousMillis6 = currentMillis;
                     if (flagSecVishi == false){digitalWrite(34,HIGH);digitalWrite(35,LOW);}
                     else                      {digitalWrite(34,LOW);digitalWrite(35,HIGH);}  
                     flagSecVishi = !flagSecVishi;
                     digitalWrite(36,HIGH);
                     digitalWrite(37,HIGH);                       
              }

            if (currentMillis - previousMillis7 >= 500 && myStrings[5] == "3" && flagVihi == true)
              {    previousMillis7 = currentMillis;
                     if (flagSecVishi == false){digitalWrite(34,LOW);digitalWrite(35,LOW);}
                     else                      {digitalWrite(34,HIGH);digitalWrite(35,HIGH);}  
                     flagSecVishi = !flagSecVishi;
                     digitalWrite(36,HIGH);
                     digitalWrite(37,HIGH);                       
              }

            if (currentMillis - previousMillis8 >= 333 && myStrings[5] == "4" && flagVihi == true)
              {    previousMillis8 = currentMillis;
                     if (flagSecVishi == false){digitalWrite(34,LOW);digitalWrite(35,LOW);digitalWrite(36,HIGH);digitalWrite(37,HIGH);}
                     else                      {digitalWrite(34,HIGH);digitalWrite(35,HIGH);digitalWrite(36,LOW);digitalWrite(37,LOW);}  
                     flagSecVishi = !flagSecVishi;
                     
              }


              if (currentMillis - previousMillis3 >= 500){
              previousMillis3 = currentMillis;             
                    for (int i = 0; i < 24; i++){        
                    SerialData += myStrings[i];
                    SerialData += ",";   
                    }
                Serial.println(SerialData);
                Serial1.println(SerialData);
                Serial2.println(SerialData);
                Serial3.println(SerialData);
                SerialData = "";
              }

            if(starTimer == true)
              {
                      if (vTime2 == true)
                      {
                            previousMillis4 = currentMillis;
                            timerTab2 = timerTab;
                            vTime2 = false;
                            
                      }
                        
              if (currentMillis - previousMillis4 >= timerTab*1000)
                      {    
                           previousMillis4 = currentMillis;
                           dParFlag = false;
                           flagIR = false; 
                           digitalWrite(23,HIGH);digitalWrite(24,HIGH);digitalWrite(25,HIGH);digitalWrite(26,HIGH);digitalWrite(27,HIGH);
                           digitalWrite(28,HIGH);digitalWrite(29,HIGH);
                           digitalWrite(30,HIGH);digitalWrite(31,HIGH);digitalWrite(32,HIGH);digitalWrite(33,HIGH);
                           digitalWrite(34,HIGH);digitalWrite(35,HIGH);digitalWrite(36,HIGH);digitalWrite(37,HIGH);
                           myStrings[1] = "b";myStrings[2] = "c";myStrings[3] = "d";myStrings[4] = "e";myStrings[7] = "g";myStrings[8] = "h";
                           myStrings[9] = "i";
                           //timerTab = 0;
                           vTime2 = true;
                           starTimer = false;
                           
                      }

         if (currentMillis - previousMillis5 >= 1000){ 
              previousMillis5 = currentMillis;
                      
                      timerTab2--; 
                      if (timerTab2 >= 0) {
                       myStrings[12] = String(timerTab2);
                      }
                }
          }

   if(dVodaParData == HIGH && dParFlag == true && startOnOff == true){ //Включение парогенератора от датчика, с задержкой 2 секунды
        if (vTime == true){
          previousMillis = currentMillis;
          vTime = false;
          }
        if (currentMillis - previousMillis >= interval){ 
          previousMillis = currentMillis;
          digitalWrite(24,LOW);
          digitalWrite(53,HIGH);
          myStrings[4] = "E";
          myStrings[3] = "d";
          vTime == true;
          }
   }
         else {
              vTime = true;    
              digitalWrite(24,HIGH);
              }
   
         if (currentMillis - previousMillis2 >= 3000){ //температура
              previousMillis2 = currentMillis;
              byte data[2];
              ds.reset(); 
              ds.write(0xCC);
              ds.write(0x44);
              delay(200);
              ds.reset();
              ds.write(0xCC);
              ds.write(0xBE);
              data[0] = ds.read(); 
              data[1] = ds.read();
              Temp = (data[1]<< 8)+data[0];
              Temp = Temp>>4;
              //Serial.println(Temp);
              myStrings[13] = String(Temp);

              byte data2[2];
              ds2.reset(); 
              ds2.write(0xCC);
              ds2.write(0x44);
              delay(200);
              ds2.reset();
              ds2.write(0xCC);
              ds2.write(0xBE);
              data2[0] = ds2.read(); 
              data2[1] = ds2.read();
              Temp2 = (data2[1]<< 8)+data2[0];
              Temp2 = Temp2>>4;
              myStrings[6] = String(Temp2);
              //Serial.println(Temp2);
              
//            if(Temp < 10){
//                myStrings[15] = " ";
//                myStrings[16] = String(Temp);
//                }
//            else if (Temp >= 10 && Temp < 99) {
//                
//            }
              //Serial1.print("t");
              //Serial1.println(Temp);
          }

      if (Temp >= ustanovitIR){      
         digitalWrite(25,HIGH);
         //myStrings[3] = "d";
      }

     if (Temp < ustanovitIR && flagIR == true && dParFlag == false && startOnOff == true && flagVihi == false){      
         digitalWrite(25,LOW);
         myStrings[3] = "D";
        }

     if (Temp >= ustanovitPar){      
        digitalWrite(24,HIGH);
      }

     if (Temp < ustanovitPar && flagIR == false && flagPar == true && dParFlag == false && startOnOff == true){

                
         //digitalWrite(24,LOW);//--------------------------------------
         
         //myStrings[4] = "E";
         
         digitalWrite(25,HIGH); 
         myStrings[3] = "d";
           if(dVodaParData == LOW){ 
           digitalWrite(53,LOW);
         } 
      }
              

}//End loop


            







