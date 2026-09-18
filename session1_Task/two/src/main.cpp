#include <avr/io.h>
#include<util/delay.h>

int main(){
  DDRB |= (1 << PB3);
  TCCR0 = (1 << WGM00) | (1 << WGM01); //timer mode fast pwm
  TCCR0 |= (1 << COM01); //noninverting
  TCCR0 |= (1 << CS01); //prescaler set to 8
  OCR0 = 64; //25% duty cyucle
  int counter = 0;
  while(1){
    for (uint8_t duty = 64; duty < 255; duty++)
        {
            OCR0 = duty;
            _delay_ms(10);
        }

        for (uint8_t duty = 255; duty > 64; duty--)
        {
            OCR0 = duty;
            _delay_ms(10);
        }
  }
}