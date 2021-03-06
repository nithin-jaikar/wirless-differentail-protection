// LCD module connections
sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D4 at RB2_bit;
sbit LCD_D5 at RB3_bit;
sbit LCD_D6 at RB4_bit;
sbit LCD_D7 at RB5_bit;

sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB4_bit;
sbit LCD_D7_Direction at TRISB5_bit;
// End LCD module connections

sbit led at TRISD2_bit;

unsigned int ADC_Value, Factor;
unsigned long temp;

char temp1[] = "0.00";
char temp2[] = "0.00";
char temp3[] = "0.00";

void main()
{
    ADCON1=0x80;
    CMCON=0x00;
    TRISD2_bit=0;
    TRISB=0x00;
    TRISA=0xFF;
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);        // Clear display
    Lcd_Cmd(_LCD_CURSOR_OFF);     // Cursdhhdor off

    Lcd_Out(1, 3, "Sub Station");
    UART1_Init(4800);
    delay_ms(2000);            // Initialize LCD
    Factor = 264;       // To conver Count into current
    led=0;
    while(1)
    {
        // Read multiple samples for better accuracy
        ADC_Value =0;
        ADC_Value = ADC_Read(0);
        ADC_Value = ADC_Value + ADC_Read(0);
        ADC_Value = ADC_Value + ADC_Read(0);
        ADC_Value = ADC_Value/3;


         temp1[0]   = ADC_Value/1000 + 48;
         temp1[2]   = (ADC_Value/100)%10 + 48;
         temp1[3]   = (ADC_Value/10)%10  + 48;
         LCD_Out(2, 3, temp1);
         Delay_ms(1000);

        ADC_Value =0;
        ADC_Value = ADC_Read(1);
        ADC_Value = ADC_Value + ADC_Read(1);
        ADC_Value = ADC_Value + ADC_Read(1);
        ADC_Value = ADC_Value/3;


        temp2[0]   = ADC_Value/1000 + 48;
         temp2[2]   = (ADC_Value/100)%10 + 48;
         temp2[3]   = (ADC_Value/10)%10  + 48;
         LCD_Out(2, 8, temp2);

        Delay_ms(1000);

        ADC_Value =0;
        ADC_Value = ADC_Read(2);
        ADC_Value = ADC_Value + ADC_Read(2);
        ADC_Value = ADC_Value + ADC_Read(2);
        ADC_Value = ADC_Value/3;


        temp3[0]   = ADC_Value/1000 + 48;
         temp3[2]   = (ADC_Value/100)%10 + 48;
         temp3[3]   = (ADC_Value/10)%10  + 48;
         LCD_Out(2, 13, temp3);

        Delay_ms(1000);
        Delay_ms(2000);
        led=0;
        UART1_Write('a');
        while (UART1_Tx_Idle() == 0);
        UART1_Write(temp1[0] );
        while (UART1_Tx_Idle() == 0);
        UART1_Write(temp1[2] );
        while (UART1_Tx_Idle() == 0);
        UART1_Write(temp1[3] );
        while (UART1_Tx_Idle() == 0);
        Delay_ms(2000);
        led=1;
        Delay_ms(2000);
        led=0;
        Delay_ms(2000);
        Delay_ms(2000);
        UART1_Write('b');
        while (UART1_Tx_Idle() == 0);
        UART1_Write(temp2[0] );
        while (UART1_Tx_Idle() == 0);
        UART1_Write(temp2[2] );
        while (UART1_Tx_Idle() == 0);
        UART1_Write(temp2[3] );
        while (UART1_Tx_Idle() == 0);
        Delay_ms(2000);
        led=1;
        Delay_ms(2000);
        led=0;
        Delay_ms(2000);
        Delay_ms(2000);
        UART1_Write('d');
        while (UART1_Tx_Idle() == 0);
        UART1_Write(temp3[0] );
        while (UART1_Tx_Idle() == 0);
        UART1_Write(temp3[2] );
        while (UART1_Tx_Idle() == 0);
        UART1_Write(temp3[3] );
        while (UART1_Tx_Idle() == 0);
        Delay_ms(2000);
        led=1;
        Delay_ms(2000);

        led=0;
        Delay_ms(2000);
        Delay_ms(2000);

    }
}
