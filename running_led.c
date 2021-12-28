/*
 * basics.c
 *
 * Created: 12-Jun-20 11:17:25 PM
 * Author : Suffiyan
 */ 
/*#define F_CPU 16000000*/
#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(PCINT2_vect)
{
    // Read PD2 using the Port D Pin Input Register (PIND)
    if (PIND & _BV(PIND2))
    {
        for (unsigned char i = 0;i < 30;i++) {
            PORTB ^= (1 << 1);
            _delay_ms(100);
            PORTB ^= (1 << 1);
            _delay_ms(100);
        }
    }
}

int main(void)
{
    // Configure PD2 as an input using the Data Direction Register D (DDRD)
    DDRD &= ~_BV(DDD2);

    // Enable the pull-up resistor on PD2 using the Port D Data Register (PORTD)
    PORTD |= _BV(PORTD2);

    // Enable pin change interrupt on the PCINT18 pin using Pin Change Mask Register 2 (PCMSK2)
    PCMSK2 |= _BV(PCINT18);

    // Enable pin change interrupt 2 using the Pin Change Interrrupt Control Register (PCICR)
    PCICR |= _BV(PCIE2);

    sei();

    DDRB=0xFF;
    /*DDRB |= 0b00000001;*/
    /*DDRB |= _BV(PB5);*/
    while(1)
    {
        /*for(z=0;z<255;z++)*/
        /*{*/
            /*PORTB=z;*/
            /*_delay_ms(1000);*/
        /*}*/
        /*PORTB = ~(PORTB);*/
        /*_delay_ms(500);*/
        /*PORTB &= 0b11111111;*/
        PORTB ^= (1 << 1);
        _delay_ms(400);
        PORTB ^= (1 << 1);
        _delay_ms(800);
    }
    return 0;
}
