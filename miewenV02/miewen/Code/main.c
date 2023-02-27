/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2017 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Jan/21/2017
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: N76E003 GPIO demo code
//***********************************************************************************************************
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include "ws2812.h"


#define UVC__ON() (P04 = 1)
#define UVC_OFF() (P04 = 0)
 
//#define RED__ON()  (P04 = 1)
//#define RED_OFF()  (P04 = 0)

//xyq
#define GPIO_RED_ON()  P11 = 0
#define GPIO_RED_OFF() P11 = 1

#define GPIO_BLUE_ON()  P11 = 0;P12 = 0
#define GPIO_BLUE_OFF() P11 = 1;P12 = 1

#define POWER__ON()  (P00 = 1)
#define POWER_OFF()  (P00 = 0)

#define RGB_PUR_ON()  P11 = 0;P12 = 0;PWM1_P11_OUTPUT_ENABLE;PWM0_P12_OUTPUT_ENABLE
#define RGB_PUR_OFF() P11 = 1;P12 = 1;PWM1_P11_OUTPUT_DISABLE;PWM0_P12_OUTPUT_DISABLE

#define PIN_KEY   P01
#define KEY_DOWN() PIN_KEY == 0
#define KEY___UP() PIN_KEY != 0

//uvc ???
#define BEEP_OFF()  P03 =0;PWM5_P03_OUTPUT_DISABLE
#define BEEP__ON()  PWM5_P03_OUTPUT_ENABLE

#define PWM_HZ 2150  // 1016 0x03F8 ??

void Close();

void PWM_Init()
{    
    //pwm 0.5 1.5
    
    PWM5_P03_OUTPUT_ENABLE;//??PWM5,??P03????
    PWM1_P11_OUTPUT_ENABLE;
    PWM0_P12_OUTPUT_ENABLE;
    //PWM5_P15_OUTPUT_ENABLE;
    //PWM2_P05_OUTPUT_ENABLE;

    clr_PWMTYP;//??????
    clr_PWMMOD0;//?????????
    clr_PWMMOD1;
    PWM_CLOCK_DIV_8;//8????
    PWMPH = (PWM_HZ >> 8);//
    //1999(Dec) 4000&  250  4000 50 4000 30
    PWMPL = (PWM_HZ & 0xff);
    set_SFRPAGE;//PWM4 and PWM5 duty seting is in SFP page 1
    PWM5H = (PWM_HZ / 2 >> 8);//500(Dec)				
    PWM5L = (PWM_HZ / 2 & 0xff);
    
    PWM1H = (5 >> 8);//500(Dec)					
    PWM1L = (5 & 0xff); 
    
    PWM0H = (1800 >> 8);//500(Dec)					
    PWM0L = (1800 & 0xff);
    
    clr_SFRPAGE;											
    set_LOAD;//????????
    set_PWMRUN;//????PWM    
    
    PWM5_P03_OUTPUT_DISABLE;
    PWM1_P11_OUTPUT_DISABLE;
    PWM0_P12_OUTPUT_DISABLE;
    //PWM2_P05_OUTPUT_DISABLE;

}

void GPIO_Init()
{
    	
	//??????
	P00_PushPull_Mode; //mcu out
    P04_PushPull_Mode; //uvc io
		
	P03_PushPull_Mode; //beep 
    
    P11_PushPull_Mode; //red
    P12_PushPull_Mode;  
    
    P01_Input_Mode;	   //button key
	
}



uint8_t test_mode_2 = 0; // when terun on button released, test_mode_2 = 1;

uint8_t power_on_is_released = 0;
uint8_t uvc_on_pre_10s = 0;

void RedBlink(uint8_t f)
{
    static uint16_t time_count_i;
    if (f)
    {
        time_count_i = 0;
        return;
    }

    time_count_i++;
    if (time_count_i == 1)
    {
        GPIO_RED_ON();
        
        if(uvc_on_pre_10s)
            BEEP__ON();
    }
    
    if (time_count_i == (20 * 3))
    {
        GPIO_RED_OFF();
    }
    
    if (time_count_i == (5 * 3))
    {
        BEEP_OFF();
    }
    
    if ( time_count_i == 100)
    {
        if(uvc_on_pre_10s) 
            time_count_i = 0;
    }
    
    if (time_count_i == 150)
    {
        time_count_i = 0;
    }
}


void main (void) 
{
    
    static int time_count_i = 0;
    static int time_count_s = 0;
    int i = 0;
    int mode_flag = 0;
    
    Set_All_GPIO_Quasi_Mode;					// Define in Function_define.h
    //test?????
    TIMER0_MODE0_ENABLE;

    
    //pwm
    GPIO_Init();
    PWM_Init();
    
    POWER__ON();
    UVC_OFF();
    GPIO_RED_OFF();
    //GPIO_BLUE_OFF();
    RGB_PUR_OFF();
    BEEP_OFF();
   
    BEEP__ON();
    GPIO_RED_ON();
    Timer0_Delay1ms(100);
    BEEP_OFF();
    GPIO_RED_OFF();

    while(i < 1000)
    {
        i ++;
        if(KEY___UP())
            break;
        Timer0_Delay1ms(1);
        
    }
    //长按
    if(i >= 1000)
    {
        BEEP__ON();
        Timer0_Delay1ms(100);
        BEEP_OFF();
        
        //GPIO_BLUE_ON();
        RGB_PUR_ON();//底部蓝光
        test_mode_2 = 2;
    }
	//短按
    else
    {
        power_on_is_released = 1;//启动1，关机0
        RedBlink(1);//提示灯和beep,未开始杀菌
        test_mode_2 = 1;
        Timer0_Delay1ms(1000);
        uvc_on_pre_10s = 1;//延后10s杀菌标志位
    }
    
    while(1)
    {

        time_count_i ++;//核心计时器，10ms一记
        if(test_mode_2 == 1)
        {
            RedBlink(0);//关闭提示
        }
        
        //加秒
        if((time_count_i % 100) == 0)
        {  
            // + 1s
            time_count_s++;
        }
        
        if(test_mode_2 == 1)
        {
           
            //if in uvc mode 
            if(time_count_s == 10)
            {
                //after 10s, open UVC
                UVC__ON();
                uvc_on_pre_10s = 0;//延后10秒标志位
            }
        
            if(time_count_s == (60 * 10))
            {            
                // turn off
                Close();
            }            
        }
        
        
        if(test_mode_2 == 2)
        {
            if(time_count_s == (60 * 60 * 8))//8小时
            {
                Close();
            }
        }
         //启动状态   
        if(KEY___UP() && !power_on_is_released)
        {
              power_on_is_released = 1;
        }
        //松手关机
        if(KEY_DOWN() && power_on_is_released) // ??
        {             
            Close();                  
        }
        Timer0_Delay1ms(10);
    }
}

void Close()
{
    BEEP__ON();
    Timer0_Delay1ms(100);
    BEEP_OFF();    
    Timer0_Delay1ms(100);
    
    BEEP__ON();
    Timer0_Delay1ms(100);
    BEEP_OFF(); 
    
    while(1)
    {
        if(KEY___UP())
            break;
        Timer0_Delay1ms(10);
    }
    
    POWER_OFF();
    Timer0_Delay1ms(1000);
         
}


