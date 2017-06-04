//Mr Estudius 
//Universidad Mariano Galvez
//Rubelsi Andres Lopez Sosa
//Ricardo Bonilla Argueta
#include <LiquidCrystal.h> //Libreria del display LCD
#include <Ultrasonic.h>    // libreria para el sensor ultrasonico
Ultrasonic ultrasonic(22, 23); // los pines a utilizar para el sensor ultrasonico 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // los pines a utilizar para la pantalla lcd
int buzzer = 24;           //Se inicia el buzzer en el pin digital 24
int ahoras = 0;            //Variable a mostrar por LCD de las horas
int aminutos = 0;          //Variable a mostrar por LCD de los minutos
int asegundos = 0;         //Variable a mostrar por LCD de los segundos
int segundostotal = 0;     //Tiempo total
int msg= 0;                //Variable para el mensaje de bienvenida
int start = 28;            //Boton para el inicio en el pin analogo 3
int empieza = 1024;        //Variable para almacenaje del boton de inicio
int buth = 26;             //boton de Horas en el pin analogo 7
int butm = 27;             //boton de Minutos en el pin analogo 2
int buts = 29;             //boton de segundos en el pin analogo 8 
int varbuth = 0;           //Variable para almacenar el valor del boton de horas
int varbutm = 0;           //Variable para almacenar el valor del boton de minutos
int varbuts = 0;           //Variable para almacenar el valor del boton de segundos
int distancia;
void setup() 
{
   lcd.begin(16, 2);         // Configuramos el numero de columnas y filas del LCD.  
   Serial.begin(9600);
   pinMode(buzzer, OUTPUT);  //Pin del buzzer -  Salida
   pinMode(buth, INPUT);     //Pin del boton de horas - Entrada
   pinMode(butm, INPUT);     //Pin del boton de minutos  - Entrada
   pinMode(buts, INPUT);     //Pin del pulsador de segundos -  Entrada
   pinMode(start, INPUT);    //Pin del pulsador de arranque - Entrada
   
   msg = 0;                  //Barrera del mensaje de bienvenida
   empieza = 1024;           //Barrera de arranque
   
   varbuth = 0;              //Seguimos con el mismo valor 
   varbutm = 0;              //Seguimos con el mismo valor 
   varbuts = 0;              //Seguimos con el mismo valor 
}

void loop() 
{        
     if(msg==0)             //Mostramos el mensaje de bienvenida 
     {
       lcd.setCursor(0,0);
       lcd.print("Sonrie Dios");
       lcd.setCursor(1,1);
       lcd.print("Te ama :)");
       delay(4000);
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("MR ESTUDIUS ");
       lcd.print("UMG");
       delay(3000);
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Rubelsi Lopez");
       lcd.setCursor(1,1);
       lcd.print("Ricardo Bonilla");
       delay(3000);
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("4490-17-2123");
       lcd.setCursor(1,1);
       lcd.print("4490-17-566");
       delay(4000);
       msg = 1;
       lcd.clear();
     }
     
    
     // Lecturas de los botones y eleccion del tiempo,bucle infinito hasta que presione el boton start 
     do                   
     {
     
       varbuth = digitalRead(buth);   //Leemos el boton de horas 
       varbutm = digitalRead(butm);   //Leemos el boton de minutos
       varbuts = digitalRead(buts);   //Leemos el boton de segundos
       
       if(varbuth == 1)              //Si el boton ha sido pulsado, aumentamos las horas en 1
       {
        ahoras = ahoras + 1 ;
        delay(250);
       }  
       
        if(varbutm == 1)            //Si el boton ha sido pulsado, aumentamos los minutos en 1
       {
         aminutos = aminutos + 1;
         delay(250);
       }  
       
        if(varbuts == 1)            //Si el boton ha sido pulsado, aumentamos los segundos en 1
       {
         asegundos = asegundos + 1; 
         delay(250);
       }  
             
       lcd.setCursor(0,0);
       lcd.print("Elige el tiempo");  //Muestra mensaje y las hh:mm:ss que vayamos aumentando
       
       lcd.setCursor(4,1);     

      if (ahoras < 10) lcd.print("0");    // Si las horas son menor que 10, pone un "0" delante.
       lcd.print(ahoras);                
       lcd.print(":");

      if (aminutos < 10) lcd.print("0");  // Si los minutos son menor que 10, pone un "0" delante.
       lcd.print(aminutos);             

       lcd.print(":");
      if (asegundos < 10) lcd.print("0"); // Si los segundos son menor que 10, pone un "0" delante.
       lcd.print(asegundos);              
       
       empieza = digitalRead(start);   //Lee el boton de inicio
       
       if (empieza == 1)              //Si el boton de arranque, fue pulsado entonces inicia la cuenta regresiva
       {
        segundostotal = asegundos + (aminutos * 60) + (ahoras * 60 * 60);  //Convierte el tiempo elegido en segundos
       }
             
     } while(empieza != 1);  
       
    // Cuenta regresiva con sensor ultrasonico
      
      while (segundostotal > 0) 
      { 
        distancia=ultrasonic.distanceRead(); //se mide la distancia que se tenga y se imprime en cm
        delay(100);
        Serial.print("Distancia  en CM: ");
        Serial.println(distancia);    
        if (distancia>=90 && distancia<=500){ // si la distancia es mayor o igual a 90 pausa el temporizador y activa la alarma
                lcd.setCursor(0,0);
                lcd.print("VUELVE A ");
                lcd.setCursor(1,1);
                lcd.print("ESTUDIAR");
                digitalWrite(buzzer, HIGH);
                delay(200);
                digitalWrite(buzzer, LOW);
                delay(200);
                segundostotal;
                lcd.clear();
        }
        else{
          delay (1000);          // si la distancia es menor o 90 el temporizador sigue restando el tiempo
          segundostotal--;
           ahoras = ((segundostotal / 60)/ 60);   //Convertimos los segundos totales en horas
           aminutos = (segundostotal / 60) % 60;  //Convertimos los segundos totales en minutos
           asegundos = segundostotal % 60;        //Convertimos los segundos totales en periodos de 60 segundos

        lcd.setCursor(0,0);
        lcd.print("Tiempo restante");        //Mostramos mensaje de tiempo restante
  
        lcd.setCursor(4,1);
        if (ahoras < 10) lcd.print("0");     // Si las horas son menor que 10, pone un "0" delante.
        lcd.print(ahoras);                  
        lcd.print(":");

        if (aminutos < 10) lcd.print("0");   // Si los minutos son menor que 10, pone un "0" delante.
        lcd.print(aminutos);                 

        lcd.print(":");
        if (asegundos < 10) lcd.print("0");  // si el valor de segundo esta por debajo de 9 (unidad) antepone un cero
        lcd.print(asegundos);                
        
          if (segundostotal == 0)            //Si finaliza el tiempo
          {           
             while(1)                        //Bucle infinito mostrando mensaje y haciendo sonar el buzzer
             {               
                  lcd.clear();
                  lcd.setCursor(5,0);
                  lcd.print("Tiempo");
                  lcd.setCursor(3,1);
                  lcd.print("Finalizado");
                  digitalWrite(buzzer, HIGH);
              
             }      
          }
        }
       
     }
      
}
