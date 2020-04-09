#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char number[10] = {
    0x3F,           //0
    0x06,           //1
    0x5B,           //2
    0x4F,           //3
    0x66,           //4
    0x6D,           //5
    0x7D,           //6
    0x07,           //7
    0x7F,           //8
    0x6F            //9
};
long int i = 0;
long int temp;
unsigned char digit_on = 0;

ISR(TIMER0_OVF_vect)
{
    TCNT0 = 48;                 //255 - 8000000 / 64 / (100 / 6)
    PORTA = 0x00;
    PORTD = 0xFF & ~(1 << digit_on);
    PORTA = number[temp % 10];
    temp /= 10;
    digit_on++;
    if (digit_on == 6){
        digit_on = 0;
        i = (i + 1) % 1000000;
        temp = i;
    }        
    
}

int main(void)
{
    DDRA = 0xFF;
    DDRD = 0xFF;
    PORTD = 0xFF; 
    temp = i;
    
    TCCR0 = 0x04;       // F_CPU / 64
    TCNT0 = 255;
    TIMSK |= (1 << TOIE0);
    sei();
    
    while (1) 
    {
        // 100hz - 10ms/number - 10/6ms = 1.667ms/digit
    }      
}

