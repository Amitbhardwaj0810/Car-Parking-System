#include <lpc214x.h>
#include <stdlib.h>
#include <string.h>

#define SLAVE_ADDR 0x4E
#define MAX 10
#define AA 2
#define SI 3
#define STO 4
#define STA 5
#define I2EN 6

#define PIR (IOPIN1 & (1 << 24))

unsigned int count = 0;

char string[35] = "INTRUDER DETECTED";
char string1[35] = "The vehicle is parked.\n";
char string2[35] = "The parking lot is full\n";

void wait(int count);

void serial_init()
{
    PINSEL0 |= 0x00000005;
    U0LCR = 0x83;
    U0DLL = 0x61;
    U0DLM = 0x00;
    U0LCR = 0x03; // DLAB = 0
}

void transmit(const char *str)
{
    IOSET0 = 0XFFFFFFFF;
    wait(2000);
    IOCLR0 = 0XFFFFFFFF;
    while (*str)
    {
        while (!(U0LSR & (1 << 5)))
            ; // Wait until the THR is empty
        U0THR = *str++;
    }
    while (!(U0LSR & (1 << 5)))
        ;         // Wait until the THR is empty
    U0THR = '\n'; // Send newline character
}

void wait(int count)
{
    int tmp = count;
    while (tmp--)
        ;
}

void I2C_Init(void)
{
    PINSEL0 |= 0x00000050; // Set P0.2 and P0.3 to SDA and SCL
    I2C0SCLH = 0x18;       // 50% duty cycle, I2CFreq = 100KHz, PCLK = 30MHz
    I2C0SCLL = 0x12;
    I2C0CONSET = (1 << I2EN); // Enable I2C module
}

void I2C_Start()
{
    I2C0CONCLR = 1 << STO;
    I2C0CONCLR = 1 << SI;
    I2C0CONSET = 1 << STA;
    while (!(I2C0CONSET & (1 << SI)))
        ; // Wait for SI to set
}

void I2C_Stop()
{
    I2C0CONSET = 1 << STO;
    I2C0CONCLR = 1 << SI | 1 << STA;
}

void I2C_Write(char data)
{
    I2C0DAT = data;
    I2C0CONCLR = 1 << SI;
    while (!(I2C0CONSET & (1 << SI)))
        ; // Wait for SI to set
}

void LCD_Command(char cmnd)
{
    I2C_Start();
    I2C_Write(SLAVE_ADDR);           // SLA+W
    I2C_Write((cmnd & 0xF0) | 0x04); // Send upper nibble
    I2C_Write((cmnd & 0xF0));        // Clear upper nibble
    I2C_Write((cmnd << 4) | 0x04);   // Send lower nibble
    I2C_Write((cmnd << 4));          // Clear lower nibble
    I2C_Stop();
    wait(2000); // Wait for the command to process
}

void LCD_Char(char char_data)
{
    I2C_Start();
    I2C_Write(SLAVE_ADDR);                // SLA+W
    I2C_Write((char_data & 0xF0) | 0x05); // Send upper nibble
    I2C_Write((char_data & 0xF0) | 0x01); // Clear upper nibble
    I2C_Write((char_data << 4) | 0x05);   // Send lower nibble
    I2C_Write((char_data << 4) | 0x01);   // Clear lower nibble
    I2C_Stop();
    wait(2000); // Wait for the character to process
}

void LCD_String(char *str)
{
    while (*str != '\0')
    {
        LCD_Char(*str++);
    }
}

void LCD_Init()
{
    I2C_Init();
    LCD_Command(0x02); // Initialize LCD in 4-bit mode
    LCD_Command(0x28); // 2 lines, 5x7 matrix
    LCD_Command(0x0C); // Display on, cursor off
    LCD_Command(0x06); // Increment cursor
    LCD_Command(0x01); // Clear display
    wait(2000);        // Wait for the initialization to complete
}

void LCD_Clear()
{
    LCD_Command(0x01); // Clear display
    wait(2000);        // Wait for the clear command to process
}

int main()
{
    serial_init();
    IODIR0 = 0x000F0FFF; // Set lower 12 bits of PORT0 as output (for the LCD)
    IODIR1 = 0x00000000; // Set PORT1 as input (for the PIR sensor)
    LCD_Init();          // Initialize LCD

    while (1)
    {
        if (count < MAX)
        {
            if (PIR == 0)
            { // PIR sensor detects obstacle
                transmit(string1);
                count++;
                LCD_Clear();
                LCD_String(string);
                IOPIN1 = (1 << 24); // Just setting the input pin as an example (Not recommended)
            }
            else
            { // No obstacle detected
                LCD_Clear();
            }
            wait(2000000); // Short delay to debounce the sensor
        }
        else
        {
            transmit(string2);
            IOSET0 = 0x000F0000; // Turn on buzzer
            wait(400000);
            IOCLR0 = 0x000F0000; // Turn off buzzer
            wait(400000);
        }
    }
}