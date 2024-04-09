/* Universidad del Valle de Guatemala
IE2023:: Programación de Microcontroladores
PRELAB4.c
Autor: Alejandra Cardona
Hardware: ATMEGA328P
Creado: 08/04/2024
Última modificación: 09/04/2024

****************************************************************** */

// LIBRERÍAS

#define F_CPU 16000000 //Frecuencia en la que opera el sistema - 16 MHz

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//Variable: Tipo nombre = Valor
uint8_t contador8bits = 0; ; //Contador de 8 bits en 0

//******************************************************************

void setup(void);

int main(void){ //Función main
	
	setup();
	
	//LOOP 
	while (1){
	
	PORTD = contador8bits; // Muestra en el puerto D lo que hay en el contador

	}
	
}

void setup(void){ //Se utiliza void cuando no se emplean parámetros
	
	cli(); //Deshabilita interrupciones
	
	UCSR0B = 0;
	
	// Puerto D como salidas
	DDRD = 0xFF;
	PORTD = 0;
	
	//Pines PC0 y PC1 como entradas
	DDRC &= ~(1 << PINC0) | ~(1 << PINC1);
	PORTC |= (1 << PINC0) | (1 << PINC1);
	
	// Interrupción
	PCICR |= (1<<PCIE1); // PCIE1 para puerto C
	PCMSK1 |= ((1<<PCINT8)|(1<<PCINT9)); // Habilita la interrupción en el puerto C -- PCMSK1 corresponde al puerto C -- PCINT8-PC0 y PCINT9-PC1
	
	sei(); // Habilita las interrupciones 
	
}

//Interrupción 
ISR(PCINT1_vect){
	
	if (!(PINC & (1 << PINC0))) { 
		// Cuando botón 0 presionado:
		contador8bits++;
		}
	else if (!(PINC & (1 << PINC1))) {
		// Cuando botón 1 presionado:
		contador8bits--;
	}
	else if((!(PINC & (1 << PINC0))) && (contador8bits==255))  {
		//Cuando el contador llegué a su máximo (255) y botón 0 presionado, entonces se suma  y regresa a 0
		contador8bits=0;
	}
	else if((!(PINC & (1 << PINC1))) && (contador8bits==255))  {
		//Cuando el contador llegué a su máximo (255) y botón 1 presionado, entonces se resta y regresa a 254
		contador8bits=254;
	}
	else {
		// De lo contrario
		contador8bits=contador8bits;
	}
}