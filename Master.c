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



sbit relay1 at TRISD0_bit;
sbit relay2 at TRISD1_bit;
sbit relay3 at TRISD3_bit;

sbit led at TRISD2_bit;
  


char temp1[] = "0.00";
char temp2[] = "0.00";
char temp3[] = "0.00";

char stemp1[] = "0.00";
char stemp2[] = "0.00";
char stemp3[] = "0.00";
unsigned int i;
char uart_rd;
unsigned int ADC_Value, Factor;
unsigned long temp;
unsigned count=0;
void main()
{
    ADCON1=0x80;
    CMCON=0x00;
    TRISB=0x00;
    TRISA=0xFF;
    TRISD0_bit=0;
    TRISD1_bit=0;
    TRISD2_bit=0;
    TRISD3_bit=0;
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);        // Clear display
    Lcd_Cmd(_LCD_CURSOR_OFF);     // Cursdhhdor off
    Lcd_Out(1, 1, "CPC Polytechnic");
    Lcd_Out(2, 5, "Mysore");
    delay_ms(2000);
 /*    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Out(1, 5, "Wireless ");
    Lcd_Out(2, 3, "Differential  ");
    delay_ms(2000);
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Out(1, 1, "Protection Using");
    Lcd_Out(2, 1, "Microcontrollers");
    delay_ms(3000);    */
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Out(1, 4, "Guided By");
    Lcd_Out(2, 1, "Smt.Sharadha H K");
    delay_ms(3000);
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Out(1, 1, "M:");
    Lcd_Out(2, 1, "S:");
    delay_ms(2000);
    relay1=0;
    delay_ms(1000);
    relay2=0;
    delay_ms(1000);
    relay3=1;
    delay_ms(1000);
    Lcd_Out(2, 3, stemp1);
    delay_ms(2000);
    Lcd_Out(2, 8, stemp2);
    delay_ms(2000);
    Lcd_Out(2, 13, stemp3);
    delay_ms(2000);
    UART1_Init(4800);
    delay_ms(2000);            // Initialize LCD
    count=0;

    while(1)
    {
        // Read multiple samples for better accuracy

        if(count>1)
          count=2;
        ADC_Value =0;
        ADC_Value = ADC_Read(0);
         ADC_Value = ADC_Value + ADC_Read(0);
        ADC_Value = ADC_Value + ADC_Read(0);
        ADC_Value = ADC_Value/3;

         temp1[0]   = ADC_Value/1000 + 48;
         temp1[2]   = (ADC_Value/100)%10 + 48;
         temp1[3]   = (ADC_Value/10)%10  + 48;
         LCD_Out(1, 3, temp1);
        
        ADC_Value =0;
        ADC_Value = ADC_Read(1);
        ADC_Value = ADC_Value + ADC_Read(1);
        ADC_Value = ADC_Value + ADC_Read(1);
        ADC_Value = ADC_Value/3;

        
        temp2[0]   = ADC_Value/1000 + 48;
         temp2[2]   = (ADC_Value/100)%10 + 48;
         temp2[3]   = (ADC_Value/10)%10  + 48;
         LCD_Out(1, 8, temp2);


        
        ADC_Value =0;
        ADC_Value = ADC_Read(2);
        ADC_Value = ADC_Value + ADC_Read(2);
        ADC_Value = ADC_Value + ADC_Read(2);
        ADC_Value = ADC_Value/3;


        temp3[0]   = ADC_Value/1000 + 48;
         temp3[2]   = (ADC_Value/100)%10 + 48;
         temp3[3]   = (ADC_Value/10)%10  + 48;
         LCD_Out(1, 13, temp3);
         led=1;
         if(count>1)
         {
                if((stemp1[0]!=temp1[0]) ||(stemp1[2]!=temp1[2]))
                  {
                   Lcd_Cmd(_LCD_CLEAR);
                   Lcd_Out(1, 3, "Unhealthy at ");
                   Lcd_Out(2, 5, "R Phase ");
                   relay1=1;
                   delay_ms(1000);
                   relay2=1;
                   delay_ms(1000);
                   relay3=0;
                   delay_ms(1000);
                   while(1);
                  }

                  else if((stemp2[0]!=temp2[0]) ||(stemp2[2]!=temp2[2]))
                  {
                   Lcd_Cmd(_LCD_CLEAR);
                   Lcd_Out(1, 3, "Unhealthy at ");
                   Lcd_Out(2, 5, "Y Phase ");
                   relay1=1;
                   delay_ms(1000);
                   relay2=1;
                   delay_ms(1000);
                   relay3=0;
                   delay_ms(1000);
                   while(1);
                  }

                  else if((stemp3[0]!=temp3[0]) ||(stemp3[2]!=temp3[2]))
                  {
                   Lcd_Cmd(_LCD_CLEAR);
                   Lcd_Out(1, 3, "Unhealthy at ");
                   Lcd_Out(2, 5, "B Phase ");
                   relay1=1;
                   delay_ms(1000);
                   relay2=1;
                   delay_ms(1000);
                   relay3=0;
                   delay_ms(1000);
                   while(1);
                  }
        }
        while (UART1_Data_Ready()==0)     ;       //if(UART1_Data_Ready())
        uart_rd = UART1_Read();     // read the received data,
         if(uart_rd=='a')
        {
           led=0;
           
           while(1)
           {
              for(i=0;i<4;i++)
              {

                while (UART1_Data_Ready()==0)     ;          //if(UART1_Data_Ready())
                if(i==1)
                   i=2;
                stemp1[i]=   UART1_Read();

              }
              Lcd_Out(2, 3, stemp1);       // and send data via UART

              break;
           }
        }
        if(uart_rd=='b')
        {
           led=0;
           while(1)
           {
              for(i=0;i<4;i++)
              {

                while (UART1_Data_Ready()==0)     ;          //if(UART1_Data_Ready())
                if(i==1)
                   i=2;
                stemp2[i]=   UART1_Read();

              }
              Lcd_Out(2, 8, stemp2);       // and send data via UART

              break;
           }
        }
        if(uart_rd=='d')
        {
           led=0;
           count++;
           while(1)
           {
              for(i=0;i<4;i++)
              {

                while (UART1_Data_Ready()==0)     ;          //if(UART1_Data_Ready())
                if(i==1)
                   i=2;
                stemp3[i]=   UART1_Read();

              }
              Lcd_Out(2, 13, stemp3);       // and send data via UART

              break;
           }
        }
        



    }
}
