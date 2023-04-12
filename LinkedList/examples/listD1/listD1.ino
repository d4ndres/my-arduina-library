#include <LinkedList.h>

int freeRam()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void setup() {
    Serial.begin(9600);

    LinkedList<int> list;
    int initFreeRam = freeRam();

    Serial.print("Sise of init Memory: ");
    Serial.println(initFreeRam);

    Serial.print( list.length() );

    if( list.count(23) )
    {
        Serial.println( "List contains 23" );
    }
    else 
    {
        Serial.println( "List does not contains 23" );
    }
    
    for (int i = 0; i < 10; i++)
    {
        list.append(i*i);
    }
    

 
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
