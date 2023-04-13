#include <LinkedMatrix.h>

int freeRam()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void setup() {
    Serial.begin(9600);

    LinkedMatrix<int> list;
    int initFreeRam = freeRam();

    Serial.print("Sise of init Memory: ");
    Serial.println(initFreeRam);

    Serial.print( list.length() );
 
    list.initFill( 2,2, 1 );

 
    Serial.println("The before list is: ");
    list.print();
    Serial.println("");

    int currencyFreeRam = initFreeRam - freeRam();

    Serial.print("Capacidad de memoria consumida por el array: ");
    Serial.println(currencyFreeRam);

    list.destroid();

    currencyFreeRam = freeRam();

    Serial.print("Size of currency memory after to destroid list is: ");
    Serial.println(currencyFreeRam); 
}

void loop() {
  

}