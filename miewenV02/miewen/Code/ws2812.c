//#include "fy_ws2812b.h"
// 
///*
//?????n76e003?? @16M
//1?nop 		??87ns
//while(1)	??194ns
//????		??570ns
//??????,???????,??16??????????16?,
//???????????????,??????????
//*/
// 
///*??????????????*/
////#define BYTE_0(n)                 ((u8)((n) & (u8)0xFF))        /*!< Returns the low byte of the 32-bit value */
////#define BYTE_1(n)                 ((u8)(BYTE_0((n) >> (u8)8)))  /*!< Returns the second byte of the 32-bit value */
////#define BYTE_2(n)                 ((u8)(BYTE_0((n) >> (u8)16))) /*!< Returns the third byte of the 32-bit value */
////#define BYTE_3(n)                 ((u8)(BYTE_0((n) >> (u8)24)))
////#define enableInterrupts()	EA=1
////#define disableInterrupts()	EA=0
// 
// 
//#define delay1NOP()	_nop_();
//#define delay2NOP()	delay1NOP();_nop_();
//#define delay3NOP()	delay2NOP();_nop_();
//#define delay4NOP()	delay3NOP();_nop_();
//#define delay5NOP()	delay4NOP();_nop_();
//#define delay6NOP()	delay5NOP();_nop_();
//#define delay7NOP()	delay6NOP();_nop_();
//#define delay8NOP()	delay7NOP();_nop_();
//#define delay9NOP()	delay8NOP();_nop_();
//#define delay10NOP()	delay9NOP();_nop_();
//#define delay11NOP()	delay10NOP();_nop_();
//#define delay12NOP()	delay11NOP();_nop_();
//#define delay13NOP()	delay12NOP();_nop_();
//#define delay14NOP()	delay13NOP();_nop_();
//#define delay15NOP()	delay14NOP();_nop_();
// 
// 
// 
//#define RGB_PIN_H() P06 = 1
//#define RGB_PIN_L() P06 = 0
// 
//void Ws2812b_Configuration(void)
//{
//    P0M1 &= ~(1<<6);
//    P0M2 |= (1<<6);
//    RGB_PIN_L();
//}
// 
//#if 0
//static void Ws2812b_Write0(void)
//{
//    RGB_PIN_H();
//    delay6NOP();
//    RGB_PIN_L();
//    
//}
// 
//static void Ws2812b_Write1(void)
//{
//    RGB_PIN_H();
//    delay12NOP();
//    
//    RGB_PIN_L();
//}
// 
//static void Ws2812b_WriteByte(u8 byte)
//{
//	if(byte & 0x80)
//		Ws2812b_Write1();
//	else
//		Ws2812b_Write0();
//	if(byte & 0x40) 
//		Ws2812b_Write1();
//	else
//		Ws2812b_Write0();
//	if(byte & 0x20)
//		Ws2812b_Write1();
//	else
//		Ws2812b_Write0();
//	if(byte & 0x10)
//		Ws2812b_Write1();
//	else
//		Ws2812b_Write0();
//	if(byte & 0x8)
//		Ws2812b_Write1();
//	else
//		Ws2812b_Write0();
//	if(byte & 0x4)         
//		Ws2812b_Write1();
//	else
//		Ws2812b_Write0();
//	if(byte & 0x2)         
//		Ws2812b_Write1();
//	else
//		Ws2812b_Write0();
//	if(byte & 0x1)         
//		Ws2812b_Write1();
//	else
//		Ws2812b_Write0();
//}
//#else
//static void Ws2812b_WriteByte(u8 byte)
//{
//	if(byte & 0x80){
//        RGB_PIN_H();
//        delay10NOP();
//        RGB_PIN_L();
//    }
//	else{      
//        RGB_PIN_H();
//        delay4NOP();
//        RGB_PIN_L();
//        delay4NOP();
//    }	
//    if(byte & 0x40){
//        RGB_PIN_H();
//        delay10NOP();
//        RGB_PIN_L();
//    }
//	else{      
//        RGB_PIN_H();
//        delay4NOP();
//        RGB_PIN_L();
//        delay4NOP();
//    }	
//	if(byte & 0x20){
//        RGB_PIN_H();
//        delay10NOP();
//        RGB_PIN_L();
//    }
//	else{      
//        RGB_PIN_H();
//        delay4NOP();
//        RGB_PIN_L();
//        delay4NOP();
//    }	
//	if(byte & 0x10){
//        RGB_PIN_H();
//        delay10NOP();
//        RGB_PIN_L();
//    }
//	else{      
//        RGB_PIN_H();
//        delay4NOP();
//        RGB_PIN_L();
//        delay4NOP();
//    }	
//	if(byte & 0x8) {
//        RGB_PIN_H();
//        delay10NOP();
//        RGB_PIN_L();
//    }
//	else{      
//        RGB_PIN_H();
//        delay4NOP();
//        RGB_PIN_L();
//        delay4NOP();
//    }	
//	if(byte & 0x4) {
//        RGB_PIN_H();
//        delay10NOP();
//        RGB_PIN_L();
//    }
//	else{      
//        RGB_PIN_H();
//        delay4NOP();
//        RGB_PIN_L();
//        delay4NOP();
//    }	
//	if(byte & 0x2) {
//        RGB_PIN_H();
//        delay10NOP();
//        RGB_PIN_L();
//    }
//	else{      
//        RGB_PIN_H();
//        delay4NOP();
//        RGB_PIN_L();
//        delay4NOP();
//    }	
//	if(byte & 0x1) {
//        RGB_PIN_H();
//        delay10NOP();
//        RGB_PIN_L();
//    }
//	else{      
//        RGB_PIN_H();
//        delay4NOP();
//        RGB_PIN_L();
//        delay4NOP();
//    }	
//}
// 
//#endif
// 
//void Ws2812b_Write(u32 color)
//{
//    Ws2812b_WriteByte(BYTE_1(color));//green
//    Ws2812b_WriteByte(BYTE_2(color));//red
//    Ws2812b_WriteByte(BYTE_0(color));//blue
//}
// 
///*********************************************?????***********************************************/
// 
////??????
////color:??(????)
////num  :???led??
//void RGB_Refresh(u32 color,u8 num){
//	disableInterrupts();
//	while(num--){
//		Ws2812b_Write(color);
//	}
//	enableInterrupts();
//}
// 
////?????
////color:??(????)
////num  :???led??
////speed:??(??ms)
//void RGB_Cycle(u32 color,u8 num,u16 speed)
//{
//	u8 i;
//	for(i=1;i<=num;i++){		//????		
//		RGB_Refresh(color,i);
//		Delay_ms(speed);
//	}
//	for(i=1;i<=num;i++){		//?
//		RGB_Refresh(0,i);
//		Delay_ms(speed);
//	}
//}
// 
////?????
////color:??(????)
////num  :???led??
////speed:??(??ms)
//void RGB_Wave(u32 color,u8 num,u16 speed)
//{
//	u32 color_step=0;
//	u32 color_temp = color;
//	color_step |= (BYTE_2(color)?0x010000:0x000000);
//	color_step |= (BYTE_1(color)?0x000100:0x000000);
//	color_step |= (BYTE_0(color)?0x000001:0x000000);
// 
//	while(//???????????
//			BYTE_2(color_temp)>=BYTE_2(color_step) &&
//			BYTE_1(color_temp)>=BYTE_1(color_step) &&
//			BYTE_0(color_temp)>=BYTE_0(color_step)
//		){
//		color_temp-=color_step;
//	}
//	
//	while(		//????	
//			BYTE_2(color_temp)<0xff &&
//			BYTE_1(color_temp)<0xff &&
//			BYTE_0(color_temp)<0xff
//		 )	{
//		color_temp+=color_step;
//		RGB_Refresh(color_temp,num);
//		Delay_ms(speed);
//	}	
//	while(//????
//			BYTE_2(color_temp)>=BYTE_2(color_step) &&
//			BYTE_1(color_temp)>=BYTE_1(color_step) &&
//			BYTE_0(color_temp)>=BYTE_0(color_step)
//		){
//		color_temp-=color_step;
//		RGB_Refresh(color_temp,num);
//		Delay_ms(speed);
//	}
//	RGB_Refresh(0,num);
//}
////?????
////color:??(????)
////num  :???led??
////speed:??(??ms)
////cnt  :????
//void RGB_Flash(u32 color,u8 num,u16 speed,u8 cnt)
//{
//	while(cnt--){
//		RGB_Refresh(color,num);
//		Delay_ms(speed);
//		RGB_Refresh(0,num);
//		Delay_ms(speed);
//	}
//}
// 
///*********************************************END OF FILE**********************************************/