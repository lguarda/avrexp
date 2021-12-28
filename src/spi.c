/*
#define P_SCK PB5
#define P_MISO PB4
#define P_MOSI PB3
#define P_SS PB2

#define DDR_SPI DDRB
#define DD_SCK DDB5
#define DD_MISO DDB4
#define DD_MOSI DDB3
#define DD_SS DDB2

static inline void SPI_MasterInit(void){
    // Set MOSI and SCK output, all others input
    DDR_SPI |= (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
    DDR_SPI &= ~(_BV(P_MISO));
    // Enable SPI, Master, set clock rate fck/16
    //SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
    // Enable SPI, Master, set clock rate fck/2
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
    SPSR = (1<<SPI2X);

    PORTB |= _BV(P_SS) | _BV(P_MISO);
}

static inline void SPI_MasterTransmit(char cData)
{
    // Start transmission
    SPDR = cData;
    // Wait for transmission complete
    while(!(SPSR & (1<<SPIF)));
}

static inline void chip_select(void) {
    PORTB &= ~(_BV(P_SS));
}

static inline void chip_unselect(void) {
    PORTB |= _BV(P_SS);
}

static inline void spi_transmit(uint8_t opcode, uint8_t addr, uint8_t bit) {
    chip_select();
    SPI_MasterTransmit(opcode);
    SPI_MasterTransmit(addr);
    SPI_MasterTransmit(bit);
    chip_unselect();
}

void SPI_tests(void) {
    SPI_MasterInit();
    spi_transmit(MCP23S08_ADDR, IODIR, 0b00000000); // all as output

    while (1) {
        spi_transmit(MCP23S08_ADDR, GPIO, 0b11111111);
        PORTB ^= _BV(PB1);
        //_delay_ms(100);
        spi_transmit(MCP23S08_ADDR, GPIO, 0b00000000);
        PORTB ^= _BV(PB1);
        //_delay_ms(100);
    }
}
*/
