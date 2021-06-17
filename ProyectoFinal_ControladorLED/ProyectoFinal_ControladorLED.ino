/*
 * DESARROLLADO POR LUIS DAVID PINEDA VERGARA 17/06/2021
 * 
Por defecto, analogWrite de Arduino (y consecuentemente pwmWrite () ya que imita analogWrite ()) usa 8 bits
pwm en todos los temporizadores. PWM de 8 bits permite un total de 256 valores posibles. Esta biblioteca tiene algunos métodos
para ajustar la resolución si se necesita una resolución más alta:

void pwmWriteHR (pin uint8_t, deber uint16_t)
  Igual que pwmWrite, excepto que el rango es 0 - 65535 (16 bits) en su lugar
  de 0-255 (8 bits)

float TimerX_GetResolution () (reemplace X con un número de temporizador)
  Obtiene la resolución del temporizador en base 2. El valor devuelto en otras palabras
  representa el número de bits necesarios para representar el rango del temporizador. es decir
  el valor 7 significa que se necesitan 7 bits para representar todas las posibles tareas de los pines en
  esa frecuencia, o resolución de 7 bits. Tenga en cuenta que se devuelve un flotador, no
  un int.

float GetPinResolution (pin uint8_t)
  Devuelve el mismo valor que TimerX_GetResolution (), pero toma un número de pin
  como parámetro para que la persona que llama sea independiente del temporizador.

Hay varias cosas a tener en cuenta al intentar optimizar la resolución:
 -pwmWriteHR () solo es útil para temporizadores de 16 bits, ya que los temporizadores de 8 bits están inherentemente limitados a pwm de 8 bits
 -Cuanto mayor sea la frecuencia, menor será la resolución. pwmWriteHR () asignará automáticamente la entrada al
  resolución real del temporizador
 -La resolución se puede optimizar de esta manera para 2 pines en el Uno (9 y 10) y 11 pines en el Mega (2,
 3, 5, 6, 7, 8, 11, 12, 44, 45 y 46)
  
Utilice el monitor en serie para ver la salida de este programa
*/

#include <PWM.h>

int led = 11; // the pin that the LED is attached to

void setup()
{
  InitTimersSafe(); //Inicializar todos los temporizadores excepto 0, para ahorrar tiempo, funciones de mantenimiento.
  Serial.begin(115200);
  Serial.println();
  
  demonstrateFrequencysEffectOnResolution();
  settingHighResolutionDuty();
}

void demonstrateFrequencysEffectOnResolution()
{
  Serial.println("As frequency increases, resolution will decrease...");
  for(int i = 1; i < 10000; i+=10)
    {
      SetPinFrequency(led, i);  //Se coloca la frecuencia
      
      uint16_t frequency = Timer1_GetFrequency();
      uint16_t decimalResolution = Timer1_GetTop() + 1;
      uint16_t binaryResolution = GetPinResolution(led); //este número será inexactamente bajo porque el float se trunca a un int
      char strOut[75];
      sprintf(strOut, "Frequency: %u Hz\r\n Number of Possible Duties: %u\r\n Resolution: %u bit\r\n", frequency, decimalResolution, binaryResolution );
      
      Serial.println(strOut);
    } 
    
    Serial.println("...Finished");
}

void settingHighResolutionDuty()
{
 SetPinFrequency(led, 10); //Se coloca a una frecuencia de 10 Hz
 Serial.println("\r\npwmWrite() and pwmWriteHR() are identical except for the valid range of inputs.\r\nThe following loop calls both functions to produce the same result on the \r\nLED pin. The pin should to run 10Hz at 50% duty regardless of the function called.\r\n");
 
}

void loop()
{
  // el led debe parpadear (10Hz 50% de servicio) durante 1 segundo antes de llamar
  //la otra función. Esto demuestra el uso de pwmWriteHR () y cómo su
  //el uso es casi idéntico a pwmWrite ()
 while(true)
 {
   //establecer al 50% con pwm de 8 bits. 128 es 1/2 de 256
   pwmWrite(led, 128); 
   Serial.println("8-Bit PWM");
   delay(1000);
   
   //estableciendo el deber al 50% con la resolución más alta posible que
   //se puede aplicar al temporizador (hasta 16 bits). 1/2 de 65536 es 32768.
   pwmWriteHR(led, 32768);
   Serial.println("High Resolution PWM");
   delay(1000);
 }
}
