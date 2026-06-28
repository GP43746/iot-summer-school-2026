/**
 * @file spi_setup.ino
 * @author Gauransh Pundir
 * @date 2026-06-28
 * @description Week 2 Q8 - Low-level hardware register configuration for 
 * establishing an SPI Master bus architecture on the ATmega328P.
 */

#include <SPI.h>

void spi_master_init(void) {
  // 1. Set MOSI (Pin 11), SCK (Pin 13), and SS (Pin 10) as Output pins.
  // Set MISO (Pin 12) as an Input pin.
  DDRB |= (1 << DDB3) | (1 << DDB5) | (1 << DDB2); // Pins 11, 13, 10 -> OUTPUT
  DDRB &= ~(1 << DDB4);                            // Pin 12 -> INPUT

  // 2. Configure the SPI Control Register (SPCR):
  // SPE  = 1 : Enable the SPI hardware subsystem
  // MSTR = 1 : Configure the microcontroller as the SPI Master
  // SPR0 = 1 : Set Clock Prescaler to F_CPU / 16 (1 MHz clock signal on a 16MHz board)
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
  
  // 3. Drive the Slave Select (SS) line HIGH to keep the bus idle initially
  PORTB |= (1 << PORTB2); 
}

void spi_transfer_byte(char data) {
  // Pull Slave Select LOW to select the peripheral chip
  PORTB &= ~(1 << PORTB2);

  // Load data byte into the SPI Data Register (SPDR). This automatically starts transmission.
  SPDR = data;

  // Wait / Poll the SPI Status Register (SPSR) until the SPI Interrupt Flag (SPIF) fires HIGH.
  // This indicates that the 8 bits have successfully shifted out over the MOSI line.
  while (!(SPSR & (1 << SPIF))) {
    // Hardware polling barrier
  }

  // De-select the slave by pulling the SS line back HIGH
  PORTB |= (1 << PORTB2);
}

void setup() {
  Serial.begin(9600);
  
  // Initialize the native hardware registers
  spi_master_init();
  
  Serial.println("=== ATMEGA328P SPI MASTER REGISTERS INITIALIZED ===");
}

void loop() {
  Serial.println("Transmitting test character packet 'A' over MOSI...");
  
  // Push data packet out over the physical hardware line
  spi_transfer_byte('A');
  
  delay(2000); // 2-second repeat interval loop
}