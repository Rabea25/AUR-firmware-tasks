#include <avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>

ISR(INT0_vect)
{
    PORTB ^= (1 << PB0);   
}

int main(){
  DDRB |= 1;
  PORTB &= ~(1 << PB0); //init off

  DDRD &= ~(1 << PD2);
  PORTD |= (1 << PD2);

  GICR |= (1 << INT0);
  MCUCR |= (1 << ISC01);
  MCUCR &= ~(1 << ISC00); 

  sei();

  while(1);

}