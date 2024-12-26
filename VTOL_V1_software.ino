/* project: Software_VTOL */
/* author: David Morales */

#include <SPI.h>
#include <SD.h>
#include "ABlocks_DHT.h"

double temperatura;
double humedad;
double alcohol;
double contador;
double gas;
double sonido;
File sd_file;
DHT dht26(26,DHT11);

void fnc_sd_print_esp32ks(String _f, String _t, boolean _nl){
	sd_file = SD.open(String("/")+_f, FILE_APPEND);
	if(sd_file){
		if(_nl)sd_file.println(_t);
		else sd_file.print(_t);
		sd_file.close();
	}
}

void setup()
{
  	pinMode(26, INPUT);
	pinMode(2, INPUT);
	pinMode(4, INPUT);

	Serial.begin(9600);
	Serial.flush();
	while(Serial.available()>0)Serial.read();

	SPIClass *spi_hspiSD = new SPIClass(HSPI); spi_hspiSD->begin(15, 32, 33, -1); SD.begin(-1, *spi_hspiSD, 40000000); //integrated SD card
	dht26.begin();

	SD.remove(String("/")+String("data_dht11.csv"));
	contador = 0;

}


void loop()
{
	yield();

  	temperatura = dht26.readTemperature();
  	humedad = dht26.readHumidity();
  	alcohol = analogRead(2);
  	gas = analogRead(2);
  	sonido = analogRead(4);
  	fnc_sd_print_esp32ks(String("data_dht11.csv"),String((long)(contador)),false);
  	fnc_sd_print_esp32ks(String("data_dht11.csv"),String(String(";")),false);
  	fnc_sd_print_esp32ks(String("data_dht11.csv"),String((long)(temperatura)),false);
  	fnc_sd_print_esp32ks(String("data_dht11.csv"),String(String(";")),false);
  	fnc_sd_print_esp32ks(String("data_dht11.csv"),String((long)(humedad)),false);
  	fnc_sd_print_esp32ks(String("data_dht11.csv"),String(String(";")),false);
  	fnc_sd_print_esp32ks(String("data_dht11.csv"),String((long)(alcohol)),false);
  	fnc_sd_print_esp32ks(String("data_dht11.csv"),String(String(";")),false);
  	fnc_sd_print_esp32ks(String("data_dht11.csv"),String((long)(gas)),false);
  	fnc_sd_print_esp32ks(String("data_dht11.csv"),String(String(";")),false);
  	fnc_sd_print_esp32ks(String("data_dht11.csv"),String((long)(sonido)),false);
  	Serial.println(String("Paquete:")+String(contador));
  	Serial.println(String("La temperatura es de:")+String(temperatura)+String("ºC"));
  	Serial.println(String("La humedad es de:")+String(humedad)+String("%"));
  	Serial.println(String("El nivel de alcohol es de:")+String(alcohol));
  	Serial.println(String("El nivel de gases es de:")+String(gas));
  	Serial.println(String("El nivel de sonido es de:")+String(sonido));
  	Serial.print(String("temperatura")); Serial.print("="); Serial.println(temperatura);
  	Serial.print(String("humedad")); Serial.print("="); Serial.println(humedad);
  	Serial.print(String("alcohol")); Serial.print("="); Serial.println(alcohol);
  	Serial.print(String("gas")); Serial.print("="); Serial.println(gas);
  	Serial.print(String("sonido")); Serial.print("="); Serial.println(sonido);
  	delay(1000);
  	contador = (contador + 1);   //it prints all the values of the different variables --- humidity, temperature, gases, acohol and sound.

}