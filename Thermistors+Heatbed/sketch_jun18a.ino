#include <math.h>
int ThermistorPin = A1;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
float temp2;

void setup() {

Serial.begin(9600);

}

void loop() {
  
  double val=analogRead(A0);
  double fenya=(val/1023)*5;
  double r = (5-fenya)/fenya*4700;
  temp2 = 1/(  log(r/10000) /3950 + 1/(25+273.15))-273.15 ;
  



  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;
  //Tc = Tc + 0.7; // Kompenzace pro desku. (idk jestli správně)
  Tf = (Tc * 9.0)/ 5.0 + 32.0; 
  
  //serialPrint(); //Pro debugging.

  dataCollect(); //Pro sbírání dat.

  delay(1000);
}

void serialPrint() {

    Serial.println("--------------------");
  Serial.print("Deska: ");
  Serial.print(Tc);
  Serial.println(" °C");
  Serial.print("Senzor: ");
  Serial.print(temp2);
  Serial.println(" °C");
  Serial.print("Rozdíl: ");
  Serial.print(abs(Tc-temp2));
  Serial.println(" °C");
  Serial.print("Průměr: ");
  Serial.print((Tc+temp2)/2);
  Serial.println(" °C");
  Serial.println("--------------------");

}

void dataCollect() {

    Serial.print(Tc);
  Serial.print(",");
  Serial.print(temp2);
  Serial.print(",");
  Serial.print(abs(Tc-temp2));
  Serial.print(",");
  Serial.print((Tc+temp2)/2);
  Serial.println(",");

}