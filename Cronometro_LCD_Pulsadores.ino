  
  // Importar librerías

  #include <LiquidCrystal.h>
  //#include <Ultrasonic.h>
//Ultrasonic ultrasonic(22, 23);  
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
  
  // Variables para los cálculos internos del cronómetro
  int horas = 0;
  int minutos = 0;
  int segundos = 0;
  int decimas = 0;
  long milisegundos = 0;
  
  int pulsador_inicio = 10; // pulsador_inicio en PIN digital 10
  int pulsador_pausa = 9; // pulsador_pausa en PIN digital 9

  int anterior=0;
  int encender=0;
  int estado=0;
  //int distancia;
  void setup()
  {
    Serial.begin(9600); // Comienzo de la comunicación serie
    pinMode(pulsador_inicio, INPUT); // Pin digital 10 como entrada
    pinMode(pulsador_pausa, INPUT); // Pin digital 9 como entrada
  
    // Inicializamos el LCD
    lcd.begin(16,2);
    lcd.clear();
    lcd.print("Tiempo Estudio: ");
 
  }
  
  void loop()/////////////////////////////////////////////////////////////
        
    {
     /*distancia=ultrasonic.distanceRead();
      Serial.print("Distancia  en CM: ");
      Serial.println(distancia);*/
    estado=digitalRead(pulsador_inicio);
    if (estado && anterior == 0)     // Comprobamos si el anterior era sin pulsar y el estado actual es pulsado
  {
    encender = 1 - encender;       // Asignamos el estado contrario
    delay(30);                     // Anti-rebote
  }
    anterior=estado;   // Guardamos el estado actual para posteriores comprobaciones
   
    if(encender == 1 )// Si presionamos el pulsador de inicio se pone todo a cero
    {
      horas = 0;
      minutos = 0;
      segundos = 0;
      decimas = 0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Tiempo Estudio: ");
      lcd.setCursor(0,1);
      lcd.print("00:00:00(0)");
      delay(200);
      while(pulsador_inicio==LOW);
      delay(200);
 
    }
    
    // Si presionamos el pulsador de pausa se congela el tiempo hasta que lo volvamos a presionar
    if(digitalRead(pulsador_pausa) == HIGH)
    {
      delay(200);
      while(digitalRead(pulsador_pausa) ==LOW);
      delay(200);
     
    }
 
        
    // Se cuentan los milisegundos transcurridos
    milisegundos = millis();
     // Si el tiempo transcurrido es mayor a una décima de segundo 
    if(milisegundos % 100 == 0)
    {
      decimas++;
      // Si han pasado 10 décimas de segundo se cuenta un segundo
      if(decimas == 10)
      { 
        decimas = 0;
        segundos++;
      }
      // Si han pasado 60 segundos se cuenta un minuto
      if(segundos == 60)
      { 
        segundos = 0;
        minutos++;
      }
      // Si han pasado 60 minutos se cuenta una hora
      if(minutos == 60)
      {
        minutos = 0;
        horas++;
      }
      
      // Mostramos el tiempo a través del LCD
      lcd.setCursor(0,1);
      if(horas < 10)
      {
        lcd.print("0");
      }
      lcd.print(horas);
      lcd.print(":");
      lcd.setCursor(3,1);
      if(minutos < 10)
      {
        lcd.print("0");
      }
      lcd.print(minutos);
      lcd.print(":");
      lcd.setCursor(6,1);
      if(segundos < 10)
      {
        lcd.print("0");
      }
      lcd.print(segundos);
      lcd.print("(");
      lcd.setCursor(9,1);
      lcd.print(decimas);
      lcd.print(")");
    }
    
    
    }    
  
  

