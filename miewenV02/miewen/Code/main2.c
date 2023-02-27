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
//#define RGB_RED_ON()  P15 = 0;PWM5_P15_OUTPUT_ENABLE
//#define RGB_RED_OFF() P15 = 1;PWM5_P15_OUTPUT_DISABLE

//#define RGB_PUR_ON()  P05 = 0;P15 = 0;PWM2_P05_OUTPUT_ENABLE;PWM5_P15_OUTPUT_ENABLE
//#define RGB_PUR_OFF() P05 = 1;P15 = 1;PWM2_P05_OUTPUT_DISABLE;PWM5_P15_OUTPUT_DISABLE

#define POWER__ON()  (P00 = 1)
#define POWER_OFF()  (P00 = 0)

#define GPIO_RED_ON()  P11 = 0
#define GPIO_RED_OFF() P11 = 1

#define GPIO_BLUE_ON()  P11 = 0;P12 = 0
#define GPIO_BLUE_OFF() P11 = 1;P12 = 1

#define PIN_KEY P01

//uvc 蜂鸣器
#define BEEP_OFF()  P03 =0;PWM5_P03_OUTPUT_DISABLE
#define BEEP__ON()  PWM5_P03_OUTPUT_ENABLE

 #define PWM_HZ 2150  // 1016 0x03F8 当前

//#define PWM_HZ (2000000 / (2730 - 1))  //732

void PWM_Init()
{    
    //pwm 0.5 1.5
    
    PWM5_P03_OUTPUT_ENABLE;//??PWM5,??P03????
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
    
    //PWM2H = (200 >> 8);//500(Dec)				
    //PWM2L = (200 & 0xff);
    
    clr_SFRPAGE;											
    set_LOAD;//????????
    set_PWMRUN;//????PWM    
    
    PWM5_P03_OUTPUT_DISABLE;
    //PWM5_P15_OUTPUT_DISABLE;
    //PWM2_P05_OUTPUT_DISABLE;

}

void GPIO_Init()
{
    	
	//设置推挽模式
	P00_PushPull_Mode; //mcu out
    P04_PushPull_Mode; //uvc io
		
	P03_PushPull_Mode; //beep 蜂鸣器要pwm
    
    P11_PushPull_Mode; //red
    
    P01_Input_Mode;		 //button key
	
}
uint8_t test_mode = 0; // mode 0: befor 10s ,red beep on,    
                       // mode 1: after 10s ,UVC ON

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
        //RED__ON();
        //RGB_RED_ON();
        GPIO_RED_ON();
        //松开才闪烁
        if(test_mode == 0 &&(PIN_KEY!=0))
        {
           BEEP__ON();
        }

    }
    
    if (time_count_i == (20 * 3))
    {
        //RED_OFF();
        //RGB_RED_OFF();
        GPIO_RED_OFF();
    }
    if (time_count_i == (5 * 3))
    {
        BEEP_OFF();
    }
    
    if (test_mode == 0)
    {
        if (time_count_i == 120)
        {
            time_count_i = 0;
        }            
    }

    if (time_count_i == 300)
    {
        time_count_i = 0;
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
        if(PIN_KEY == 1)    //1
            break;
        Timer0_Delay1ms(10);
    }
    
    POWER_OFF();
    Timer0_Delay1ms(1000);
         
}


uint8_t test_mode_2 = 0; // when terun on button released, test_mode_2 = 1;
void main (void) 
{
    //全gpio准双向模式
    
    static int time_count_i = 0;
    static int time_count_s = 0;
    int mode_flag = 0;
    
    Set_All_GPIO_Quasi_Mode;					// Define in Function_define.h
    //test使能定时器
    TIMER0_MODE0_ENABLE;

    
    //pwm
    GPIO_Init();
    
    PWM_Init();
    
    POWER__ON();
    
    RedBlink(1);    
    test_mode = 0;
    //RED_OFF();

    UVC_OFF();
    test_mode_2 = 0;


    while(1)
    {
        
        //RedBlink(0);        
        time_count_i ++;
        
        //回头加模式切换判断
        if((time_count_i % 100) == 0)
        {  
            // + 1s
            time_count_s++;
        }
        
        //if in uvc mode 
//        if(time_count_s == 10)
//        {
//            //after 10s, open UVC
//            UVC__ON();
//            test_mode = 1;
//        }
//        
//        
//        if(time_count_s == (60 * 10))
//        {            
//            // turn off
//            POWER_OFF();
//        }
        
        if(test_mode_2 == 1)
        {
            RedBlink(0);
            //if in uvc mode 
            if(time_count_s == 10)
            {
                //after 10s, open UVC
                UVC__ON();
                test_mode = 1;
            }
        
            if(time_count_s == (60 * 10))
            {            
                // turn off
                POWER_OFF();
            }            
        }
        
        //灭蚊模式
//        if(test_mode_2 == 2)
//        {
//            if(time_count_s == (60 * 60 * 8))
//            {
//                POWER_OFF();
//            }
//        }
            
        if(PIN_KEY == 0)
        {
                               
        }
        
        if(PIN_KEY == 0)
        {
             if(time_count_s >= 1)
              {
                    //mode2 
                    UVC_OFF();
                    GPIO_BLUE_ON();
                    mode_flag = 0;
              }
             if(test_mode_2 == 1)                 
             {
                 Close();
                // 关机
//                BEEP_OFF();
//                //while(PIN_KEY == 0 && (mode_flag == 1));            
//                BEEP__ON();
//                Timer0_Delay1ms(100);
//                BEEP_OFF();    
//                Timer0_Delay1ms(100);
//                BEEP__ON();
//                Timer0_Delay1ms(100);
//                BEEP_OFF();
//                while(PIN_KEY == 0 && (mode_flag == 1)); 
//                POWER_OFF();              
             }else if (test_mode_2 == 2 &&(mode_flag == 2))
             {
                //GPIO_BLUE_OFF();
                Close();
                //while(PIN_KEY == 0 && (mode_flag == 1));            
//                BEEP__ON();
//                Timer0_Delay1ms(100);
//                BEEP_OFF(); 
//                Timer0_Delay1ms(100);
//                BEEP__ON();
//                Timer0_Delay1ms(100);
//                BEEP_OFF();
//                while(PIN_KEY == 0)
//                {
//                    POWER_OFF();
//                }

             }
        }
        else
        {
            if(mode_flag == 0)
            {
            //松开大于1s
                if(time_count_s >= 1)
                {
                    //mode2 
                    test_mode_2 = 2;
                    UVC_OFF();
                    GPIO_BLUE_ON();
                    mode_flag++;
                }else{
                    // 开机时松开切模式
                    test_mode_2 = 1;
                    mode_flag++;
                }      
            }
            //长按松开 蜂鸣器关闭
            if(mode_flag == 1 && (test_mode_2 == 2))
            {
                mode_flag = 2;
                BEEP_OFF();
            }

        }
        Timer0_Delay1ms(10);
    }
}




