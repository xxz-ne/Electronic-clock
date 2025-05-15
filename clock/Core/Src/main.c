/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "smg.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
uint8_t tdata[6]={0xC0};
uint8_t clock_set[3]={0,0,10};
uint8_t disp[20]={'s','e','t',' ','c','l','o','c','k',':',' ','0','1',':','0','1',':','0','1','\r'};
uint32_t msTicks=0, count_time=0,*pcount=&count_time;
	
uint16_t time[3]={0}; //uint16_t time[0]=hour, time[1]=minute, time[2]=second;

_Bool stop_flag=1,clear_flag=0, INC1=0, DEC1=0;
uint8_t select=0;

_Bool mode_flag=1;	
uint32_t countdown=0,*pdown=&countdown;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
	smg_Display(tdata);
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_UART_Receive_DMA(&huart1,clock_set,3); //接收到的为ASC11码，数字字符;
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		clear_flag=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14);		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   if(GPIO_Pin==GPIO_PIN_11) select=(select+1)%4;
	 else if(GPIO_Pin==GPIO_PIN_12) INC1=1;
	 else if(GPIO_Pin==GPIO_PIN_13) DEC1=1;
	 else if(GPIO_Pin==GPIO_PIN_15) stop_flag=!stop_flag;
	 else if(GPIO_Pin==GPIO_PIN_7) 
	 {
		 mode_flag=!mode_flag;
		 msTicks=0,stop_flag=1;
		 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_RESET),count_time=0;
		 select=0;
		 countdown=clock_set[2]+clock_set[1]*60+clock_set[0]*3600;
	 }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
	
	if(mode_flag) //时钟;
	{
	  if(stop_flag==0)  
		{
			msTicks++;
		  if(msTicks%1000==0) count_time++;
			if(count_time==86400) count_time=0,stop_flag=1;
		}
	  if(msTicks>=86400000) msTicks%=86400000;
	  if(clear_flag) msTicks=0,count_time=0,HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_RESET);
		
	  time[2]=count_time%60;
		time[1]=(count_time/60)%60;
		time[0]=(count_time/60/60)%24;

	  Setnum(pcount, time ,select, INC1, DEC1);
		INC1=0,DEC1=0;
		test_clock(time,clock_set);
	}
	
	else //倒计时
	{
		if(stop_flag==0)  
		{
			msTicks++;
		  if(msTicks%1000==0) countdown--;
			if(countdown==0) stop_flag=1, HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_SET);
		}
		if(msTicks>=86400000) msTicks%=86400000;
	  if(clear_flag) msTicks=0, countdown=clock_set[2]+clock_set[1]*60+clock_set[0]*3600, HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_RESET);
		
		time[2]=countdown%60;
		time[1]=(countdown/60)%60;
		time[0]=(countdown/60/60)%24;
	
	  Setnum(pdown, time ,select, INC1, DEC1);
		INC1=0,DEC1=0;
	}
		setdata(time,select,tdata);
		smg_Display(tdata);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
//		HAL_SPI_DMAStop(&hspi1);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	clock_set[0]=(clock_set[0]-0x30)%24;
	disp[11]= 0x30+clock_set[0]/10;
	disp[12]= 0x30+clock_set[0]%10;
	clock_set[1]=(clock_set[1]-0x30)%60;
	disp[14]= 0x30+clock_set[1]/10;
	disp[15]= 0x30+clock_set[1]%10;
	clock_set[2]=(clock_set[2]-0x30)%60;
	disp[17]= 0x30+clock_set[2]/10;
	disp[18]= 0x30+clock_set[2]%10;
	if(mode_flag==0) countdown=clock_set[2]+clock_set[1]*60+clock_set[0]*3600;
	HAL_UART_Transmit_DMA(&huart1,disp, 20);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
