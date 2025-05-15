#include "smg.h"
#include "spi.h"
#include "gpio.h"
uint16_t display_flag=0;
uint16_t clock_time=0;

void Setnum(uint32_t *pcount, uint16_t* time, uint8_t select, _Bool INC1, _Bool DEC1)
{
    if(select>0&&(INC1||DEC1))
		{			
			if(select==1) 
			{
				if(time[2]==59&&INC1&&(!DEC1)) time[2]=0,*pcount=*pcount-59;
			  else if(time[2]==0&&(!INC1)&&DEC1) time[2]=59,*pcount=*pcount+59;
				else time[2]=time[2]+INC1-DEC1, *pcount=*pcount+INC1-DEC1;
			}
			else if(select==2) 
			{
				if(time[1]==59&&INC1&&(!DEC1)) time[1]=0,*pcount=*pcount-59*60;
			  else if(time[1]==0&&(!INC1)&&DEC1) time[1]=59,*pcount=*pcount+59*60;
				else time[1]=time[1]+INC1-DEC1, *pcount=*pcount+60*INC1-60*DEC1;
			}
			else 
			{
				if(time[0]==23&&INC1&&(!DEC1)) time[0]=0,*pcount=*pcount+3600;
			  else if(time[0]==0&&(!INC1)&&DEC1) time[0]=23,*pcount=*pcount+23*3600;
				else time[0]=time[0]+INC1-DEC1,*pcount=*pcount+3600*INC1-3600*DEC1;
			}
			//  INC1=0,DEC1=0; C语言函数传递的为参数的复制；
			//  改变的为参数副本的值，而非参数本身的值，故需要引入地址间接改变参数值；
			//  故包括这两个布尔值在内的参数需要以地址的形式拿过来，再以地址副本指向原参数内容；
	  }
}

void setdata(uint16_t *time, uint8_t select, uint8_t* pdata)
{
	pdata[5]=*(NUM_USE+time[2]%10);
	pdata[4]=*(NUM_USE+time[2]/10);
	pdata[3]=*(NUM_USE+time[1]%10);
	pdata[2]=*(NUM_USE+time[1]/10);
	pdata[1]=*(NUM_USE+time[0]%10);
	pdata[0]=*(NUM_USE+time[0]/10);
	if(select>0)  //闪烁;
	{
		if(display_flag++<100) pdata[6-select*2]=zz,pdata[6-select*2+1]=zz;
		else display_flag%=500;
	}
}

void smg_Display(uint8_t* pdata)
{
	HAL_SPI_Transmit_DMA(&spi_handle,pdata,smg_num);
}

void test_clock(uint16_t *time, uint8_t* pdata)
{
	if(pdata[0]==time[0])
		if(pdata[1]==time[1])
		{
			if(pdata[2]==time[2])  clock_time=time[2],HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_SET);
			else if((time[2]+60-clock_time)%60==5) clock_time=0, HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_RESET);
		}
}


