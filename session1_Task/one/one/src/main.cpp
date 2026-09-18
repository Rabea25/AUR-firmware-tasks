#include <avr/io.h>
#include<util/delay.h>

int main(){
  DDRB |= 1;
  TCCR0 = (1 << WGM01); //timer mode CTC
  OCR0 = 124; //after prescaler each tick becomes 8 us, stop at 125 ticks = 1 ms;
  TCCR0 |= (1 << CS01) | (1 << CS00); //prescaler set to 64
  int counter = 0;
  while(1){
    if(TIFR & (1<<OCF0)){
      TIFR |= (1<<OCF0);
      counter++;
      if(counter >= 500){
        counter = 0;
        PORTB ^= (1 << PB0);
      }
    }
  }
}