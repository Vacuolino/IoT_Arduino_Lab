/**********************************************************************************************************************
 * Sketch created by Edoardo Viola - GitHub Account: @edovio - Email: edoardo@edovio.in - http://edovio.in            *
 *            This code is under Creative Commons - Attribution 4.0 International (CC BY 4.0)                         *
 *              For any information about the project or to contribute follow it on GitHub                            *                 
 * *******************************************************************************************************************/


//Librerie per il sensore DHT11
#include <Adafruit_Sensor.h>
#include "DHT.h"

//Libreria per le connessioni WiFi del ESP8266
#include <ESP8266WiFi.h>


//Conversione PIN per ESP8266
#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15
#define D9 3
#define D10 1

//PIN di connessione dei Sensori
#define buzzer D2
#define led D3

//Stringhe per utilizzare Bootstrap via Internet
String bootstrap = "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css' integrity='sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm' crossorigin='anonymous'>";
String jQuery = "<script src='https://code.jquery.com/jquery-3.2.1.slim.min.js' integrity='sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN' crossorigin='anonymous'></script>";
String cdnjs = "<script src='https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js' integrity='sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q' crossorigin='anonymous'></script>";
String bootstrapJs = "<script src='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js' integrity='sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl' crossorigin='anonymous'></script>";

//Informazioni per l'accesso alla WiFi Locale
const char* ssid = "YOUR WiFi SSID";
const char* password = "YOUR WiFi PASSWORD";

//Variabili per i Sensori e l'Humidex
int h_index = -100;
float t_temp = -100;
float h_temp = -100;
float t = -100;
float h = -100;

//Definizione dei Pin per il sensore di Temperatura DHT11
#define DHTPIN D1
#define DHTTYPE DHT11

//Inizializzazione sensore di Temperatura
DHT dht(DHTPIN, DHTTYPE);

//Inizializzazione Server
WiFiServer server(80);

void setup() {
  //Configurazione dei Pin della scheda in Ingresso e Uscita
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(DHTPIN, INPUT);
  Serial.begin(115200);
  delay(10);

  //Stampa nella porta seriale le informazioni di connessione alla WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  //Attende la connessione alla WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");

  // Avvia il Server
  server.begin();
  Serial.println("Server started");

  // Stampa l'indirizzo IP
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  
//Inizializzazione delle variabili del sensore e controllo dei dati raccolti
  //Se i valori non sono buoni non aggiorna il loro valore 
  if((!isnan(dht.readTemperature()))&& (!isnan(dht.readHumidity()))){
    t = dht.readTemperature();
    h = dht.readHumidity();
    t_temp = t;
    h_temp = h;
  }
  else{
    t = t_temp;
    h = h_temp;
  }

  /*************************************************
    CODICE DA SCRIVERE A LIVELLO MEDIO
  *************************************************/
  /*******************************************************************************************************************************************************
    Calcolo dell'Indice Humidex. Determinare la formula dell'indice. Cercare in Internet le informazioni 
    Sull'indice. Possibile fonte: http://www.centrometeo.com/articoli-reportage-approfondimenti/climatologia/5008-indici-humidex-temperatura-equivalente 
  *******************************************************************************************************************************************************/
      /* Inserire il CODICE DOPO QUESTA RIGA */
        
        //h_index;

      /* INSERIRE IL CODICE PRIMA DI QUESTA RIGA */

  //Stampa i valori di temperarua e umidità nella porta seriale
  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.println(" °C");
  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.println(" %");

  //Richiama la funzione Allarmi
  alarm(t, h, h_index);

  //Richiama la funzione di creazione della Pagina Web
  createServer(t, h, h_index);
}

/**********************************************************************************************************
*   Questa funzione attiva il LED e il Buzzer ad intermittenza producendo un suono a 440 Hz (A Tone)      *
*                                    Se si verificano delle condizioni                                    *
**********************************************************************************************************/
  /*************************************************
    CODICE DA SCRIVERE A LIVELLO DIFFICILE
  *************************************************/

void alarm(float t, float h, float h_index) {
  /******************************************************************************************************
   * Scrivere una funzione che attivi ad intermittenza il Buzzer e il Led sotto le condizioni indicate  *
  *******************************************************************************************************/
        /* Inserire il CODICE DOPO QUESTA RIGA */
        


      /* INSERIRE IL CODICE PRIMA DI QUESTA RIGA */
}


/**********************************************************************************************************
*                       Questa funzione scrive una pagina HTML che usa Bootstrap 4.0                      *
*                                      quando un client è connesso                                        *
*                Inoltre, crea alert dinamici in virtù delle informazioni ricevute dai sensori            *
**********************************************************************************************************/

void createServer(float t, float h, int h_index) {
  WiFiClient client = server.available();
  delay(1);
  //Se non risulta nessun Client Connesso invia un messaggio alla porta seriale
  if (!client) {
    Serial.println("No Client connected");
    delay(1000);
  }
  //Altrimenti stampa un messaggio alla porta seriale, invia una richiesta HTTP e scrive la pagina HTML
  else {
    Serial.println("E' connesso un Client");

    //Scrive la richiesta HTTP
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); //  do not forget this one
    
    //Inizia a scrivere l'HTML
    client.println("<!DOCTYPE HTML>");
    //Cambia la lingua in base al tuo paese di provenienza
    client.println("<html lang='it-IT'>");
    
    //HEAD della pagina HTML
    client.println("<head>");
    client.println("<meta http-equiv='refresh' content='5'>");
    client.println("<meta charset='utf-8'>");
    client.println("<title>Monitor Temperatura</title>");
    client.println(bootstrap);
    client.println(jQuery);
    client.println(cdnjs);
    client.println(bootstrapJs);
    client.println("</head>");

    //BODY della pagina HTML
      client.println("<body>");

    //Creazione di una NAVBAR 
    client.println("<div class='navbar navbar-expand-lg navbar-dark bg-dark'>");
    client.println("<a class='navbar-brand' href='#'>Monitor Temperatura</a>");
    client.println("</div>");
    client.println("<hr>");

     /**************************************************
      *  CODICE DA SCRIVERE A LIVELLO FACILE           *
      *************************************************/
    //Info Blocco Temperature

      /************************************************************************************************
       *      Creare degli Alert quando la temperatura è maggiore di 45 °C e inferiore a 20 °C        *
       *      Utilizzando il costrutto if per impostare le condizioni e la funzione                   *
       *      client.println() inserendo all'interno sotto forma di stringa il codice html            *
       *      per realizzare degli Alert utilizzando il Framework Bootstrap 4.0                       *
       *      informazioni sull'HTML per Boostrap sono reperibili all'indirizzo                       *
       *      https://getbootstrap.com/docs/4.0/components/alerts/                                    *
       ***********************************************************************************************/
      /* Inserire il CODICE DOPO QUESTA RIGA */
        


      /* INSERIRE IL CODICE PRIMA DI QUESTA RIGA */

    //Info Block Humidity
 
      /************************************************************************************************
       *      Creare degli Alert quando l'umidità è maggiore del 70%                                  *
       *      Utilizzando il costrutto if per impostare le condizioni e la funzione                   *
       *      client.println() inserendo all'interno sotto forma di stringa il codice html            *
       *      per realizzare degli Alert utilizzando il Framework Bootstrap 4.0                       *
       *      informazioni sull'HTML per Boostrap sono reperibili all'indirizzo                       *
       *      https://getbootstrap.com/docs/4.0/components/alerts/                                    *
       ***********************************************************************************************/
      /* Inserire il CODICE DOPO QUESTA RIGA */
        


      /* INSERIRE IL CODICE PRIMA DI QUESTA RIGA */


     /**************************************************
      *  CODICE DA SCRIVERE A LIVELLO MEDIO            *
      *************************************************/
    //Info Block Humidex

      /************************************************************************************************
       *      Creare degli Alert in conformità alle specifiche dell'indice Humidex                    *
       *      Nelle condizioni in cui i dati raccolti rappresentano dei pericoli per l'uomo           *
       *      Utilizzando il costrutto if per impostare le condizioni e la funzione                   *
       *      client.println() inserendo all'interno sotto forma di stringa il codice html            *
       *      per realizzare degli Alert utilizzando il Framework Bootstrap 4.0                       *
       *      informazioni sull'HTML per Boostrap sono reperibili all'indirizzo                       *
       *      https://getbootstrap.com/docs/4.0/components/alerts/                                    *
       ***********************************************************************************************/
      /* Inserire il CODICE DOPO QUESTA RIGA */
        


      /* INSERIRE IL CODICE PRIMA DI QUESTA RIGA */

    //CONTENT
    client.println("<div class='container-fluid'>");

    //Temperature Block (Column 1)
    client.println("<div class ='row justify-content-around'>");
    client.println("<div class='col-5 alert alert-info'>");
    client.println("<p class = 'text-centered'> Actual Temperature: ");
    client.println(t);
    //Badge for Temperature
    //if the Temperature is under 16 °C  than a Danger Badge
    if (t <= 16.00) {
      client.println("Gradi <span class = 'badge badge-danger'>Danger</span> </p> ");
    }
    //if the Temperature is between 16 °C  and 20 °C than an Attention Badge
    if (t > 16.00 && t < 20.00) {
      client.println(" Gradi <span class = 'badge badge-warning'>Attention</span> </p> ");
    }
    //if the Temperature is above of 35 °C  than a Danger Badge
    if ( t > 35.00) {
      client.println(" Gradi <span class = 'badge badge-danger'>Danger</span> </p> ");
    }
    //if the Temperature is between 20 °C  and 25 °C than an Good Badge
    if (t >= 20.00 && t < 25.00) {
      client.println("Gradi <span class = 'badge badge-success'>Good</span> </p> ");
    }
    //if the Temperature is between 25 °C  and 35 °C than an Attention Badge
    if (t >= 25.00 && t <= 35.00) {
      client.println(" Gradi <span class = 'badge badge-warning'>Attention</span> </p> ");
    }
    client.println("</div>");

    //Humidity Block (Column 2)
    client.println("<div class='col-5 alert alert-info'>");
    client.println("<p class = 'text-centered'> Actual Humidity: ");
    client.println(h);
    //if the Humidity is equal or under 40 % than an Attention Badge
    if (h <= 40.00) {
      client.println(" % <span class = 'badge badge-warning'>Attention</span> </p> ");
    }
    //if the Humidity is between 40% and 65% than a Good Badge
    if (h > 40.00 && h < 65.00) {
      client.println(" % <span class = 'badge badge-success'>Good</span> </p> ");
    }
    //if the Humidity is above of 65%  than an Attention Badge
    else if ( h >= 65.00) {
      client.println(" % <span class = 'badge badge-warning'>Attention</span> </p> ");
    }
    client.println("</div>");
    client.println("</div>");

    client.println("<hr>");

    //Humidex Index Block
    client.println("<div class ='row justify-content-around'>");
    client.println(" <div class ='col-11 alert alert-info'>");
    client.println("<p class = 'text-centered'> Humidex Index: ");
    client.println(h_index);
    //If Humidex is under 27 than a Good Badge
    if (h_index < 27) {
      client.println("<span class = 'badge badge-success'>Good</span> </p> ");
    }
    //if the Humidex is between 27 and 30 than an Attention Badge
    if (h_index >= 27 && h_index < 30) {
      client.println("<span class = 'badge badge-warning'>Attention</span></p> ");
    }
    //if the Humidex is between 30 and 40 than an Attention Badge
    if (h_index >= 30 && h_index < 40) {
      client.println("<span class = 'badge badge-warning'>Attenzione</span></p> ");
    }
    //if the Humidex is between 40 and 55 than a Danger Badge
    if (h_index >= 40 && h_index < 55) {
      client.println("<span class = 'badge badge-danger'>Danger</span> </p> ");
    }
    //if the Humidex is above or equal 55 than a Danger Badge
    if (h_index >= 55) {
      client.println("<span class = 'badge badge-danger'>Pericolo</span> </p> ");
    }
    client.println("</div>");
    client.println("</div>");

    client.println("</div>");
    client.println("<hr>");

    //FOOTER
    client.println("<div class='container-fluid'>");
    client.println("<footer> <h5 class='text-centered'>Proudly made by <a href='mailto:edovio@gmail.com'>Edoardo Viola</a></h5></footer>");
    client.println("</div>");
    client.println("</body>");
    client.println("</html>");
    delay(1);
    delay(800);
  }
}


