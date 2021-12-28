#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char z = 0;

ISR(PCINT2_vect)
{
    // Read PD2 using the Port D Pin Input Register (PIND)
    if (PIND & _BV(PIND2))
    {
        // PD2 is high, so button is released

        // Set PB5 low using the Port B Data Register (PORTB)
        /*PORTB &= ~_BV(PORTB5);*/
        /*PORTB = 0;*/
        /*PORTB &= ~_BV(PORTB5);*/
        z += 2;
        PORTB=z;
        _delay_ms(1000);
    }
    else
    {
        // PD2 is low, so button is pressed

        // Set PB5 high using the Port B Data Register (PORTB)
        /*PORTB |= _BV(PORTB5);*/
        /*for (int i = 0; i < 6; i++) {*/
            /*PORTB=z;*/
            /*_delay_ms(1000);*/
            /*z++;*/
        /*}*/
    }
}

int main(void)
{
    pinMode(1, INPUT_PULLUP);
    // Configure PD2 as an input using the Data Direction Register D (DDRD)
    DDRD &= ~_BV(DDD2);

    // Enable the pull-up resistor on PD2 using the Port D Data Register (PORTD)
    PORTD |= _BV(PORTD2);

    // Enable pin change interrupt on the PCINT18 pin using Pin Change Mask Register 2 (PCMSK2)
    PCMSK2 |= _BV(PCINT18);

    // Enable pin change interrupt 2 using the Pin Change Interrrupt Control Register (PCICR)
    PCICR |= _BV(PCIE2);

    // Configure PB5 as an output using the Port B Data Direction Register (DDRB)
    /*DDRB |= _BV(DDB5);*/
    DDRB=0xFF;

    // Enable interrupts
    sei();

    // Loop forever
    while (1)
    {
        // Nothing to do here
        // All work is done in the ISR
    }
}
