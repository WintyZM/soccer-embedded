/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */
#include "../../../Dynamixel_AX-12A_Driver/src/Dynamixel_AX-12A.h"
#include "../../../Dynamixel_AX-12A_Driver/src/Dynamixel_AX-12A.c"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t buffrec[7];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_USART3_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_USART6_UART_Init();
  MX_USART3_UART_Init();

  /* USER CODE BEGIN 2 */
  __HAL_RCC_GPIOF_CLK_ENABLE();

  GPIO_InitTypeDef Data_Control;
  Data_Control.Pin = GPIO_PIN_15;
  Data_Control.Mode = GPIO_MODE_OUTPUT_PP;
  Data_Control.Speed = GPIO_SPEED_FREQ_LOW;
  Data_Control.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &Data_Control);

  //__HAL_UART_ENABLE_IT(&huart6,UART_IT_RXNE); // UART receive interrupt for motor

/*  Dynamixel_HandleTypeDef Motor1;
  Dynamixel_Init(&Motor1, 0x01, &huart6);

  Dynamixel_HandleTypeDef Motor2;
  Dynamixel_Init(&Motor2, 0x02, &huart6);
  Dynamixel_SetGoalPosition(&Motor2, 300);

  Dynamixel_HandleTypeDef Motor3;
  Dynamixel_Init(&Motor3, 0x03, &huart6);

  Dynamixel_HandleTypeDef Motor4;
  Dynamixel_Init(&Motor4, 0x04, &huart6);

  Dynamixel_HandleTypeDef Motor5;
  Dynamixel_Init(&Motor5, 0x05, &huart6);

  Dynamixel_HandleTypeDef MASTER_MOTOR_CONTROL;
  Dynamixel_Init(&MASTER_MOTOR_CONTROL, 0xFE, &huart6);*/


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  unsigned char buff[2] = {0x7F, 0x7F};
	  HAL_UART_Transmit(&huart6, buff, 2, 100);
	  HAL_UART_Transmit(&huart6, buff, 2, 100);
	  //Dynamixel_SetGoalPosition(&Motor1, 150);
	  //Dynamixel_SetGoalPosition(&Motor1, 150);
	  while(1);
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

//	  Dynamixel_SetGoalVelocity(&Motor2, 10);
//	  while(1){
//		  Dynamixel_SetGoalPosition(&Motor2, 150);
//		  HAL_Delay(1500);
//		  Dynamixel_SetGoalPosition(&Motor2, 170);
//		  HAL_Delay(1500);
//	  }

//	  while(1){
//		  Dynamixel_GetPosition(&Motor2);
//		  uint16_t curPos = Motor2._lastPosition;
////		  uint8_t arr[2] = {curPos & 0xFF, (curPos >> 8) &0xFF};
////		  HAL_UART_Transmit(&huart3, arr, 2, 100);
////		  while(1){}
//		  uint16_t nextPos = 0;
//		  if(curPos < 250){
//			  nextPos = curPos + 20;
//		  }
//		  else{
//			  nextPos = curPos - 20;
//		  }
////		  uint8_t arr[2] = {nextPos & 0xFF, (nextPos >> 8) &0xFF};
////		  HAL_UART_Transmit(&huart3, arr, 2, 100);
////		  while(1){}
//		  Dynamixel_SetGoalPosition(&Motor2, nextPos);
//		  Dynamixel_SetGoalVelocity(&Motor2, 10);
//		  HAL_Delay(1500);
//		  Dynamixel_SetGoalPosition(&Motor2, curPos);
//		  HAL_Delay(1500);
//	  }


//	  uint8_t numMotors = 5;
//	  Dynamixel_HandleTypeDef* arrHdynamixel[5] = {&Motor1, &Motor2, &Motor3, &Motor4, &Motor5};

//	  /* Move each motor on the leg in sequence from top to bottom to validate the settings
//	   * of the IDs. */
//	  for(uint8_t i = 0; i < numMotors; i++){
//		  /* Get current position. */
//		  Dynamixel_GetPosition(arrHdynamixel[i]);
//		  uint16_t curPos = arrHdynamixel[i]->_lastPosition;
//
//		  uint16_t nextPos = 0;
//		  if(curPos < 250){
//			  nextPos = curPos + 20;
//		  }
//		  else{
//			  nextPos = curPos - 20;
//		  }
//
//		  /* Move to current position + 20 degrees. */
//		  Dynamixel_SetGoalPosition(arrHdynamixel[i], nextPos);
//		  Dynamixel_TorqueEnable(arrHdynamixel[i], 1);
//		  Dynamixel_SetGoalVelocity(arrHdynamixel[i], 114);
//		  HAL_Delay(400); // Give motor 1.5 s to move to goal position before continuing
//
//		  /* Move back to old position. */
//		  Dynamixel_SetGoalPosition(arrHdynamixel[i], curPos);
//		  HAL_Delay(400); // Give motor 1.5 s to move to goal position before continuing
//	  }

//	  /* Getting up motion. */
//	  uint16_t arrTarget[5] = {150, 150, 150, 150, 150};
//	  for(uint8_t i = 0; i < numMotors; i++){
//		  Dynamixel_SetGoalPosition(arrHdynamixel[i], arrTarget[i]);
//		  Dynamixel_TorqueEnable(arrHdynamixel[i], 1);
//		  Dynamixel_SetGoalVelocity(arrHdynamixel[i], 10);
//	  }
//	  while(1){}
/*
	   Save original position, move up, then return.
	  uint16_t arrTarget[5] = {150, 150, 150, 150, 150};
	  uint16_t arrRecord[5];
	   Record original positions.
	  for(uint8_t i = 0; i < numMotors; i++){
		  Dynamixel_GetPosition(arrHdynamixel[i]);
		  arrRecord[i] = arrHdynamixel[i] -> _lastPosition;
	  }
	  //HAL_UART_Transmit(&huart3, arrRecord, 10, 100);
	  //while(1){}
	  while(1){
		   Getting up motion.
		  for(uint8_t i = 0; i < numMotors; i++){
			  Dynamixel_TorqueEnable(arrHdynamixel[i], 1);
			  if(i == 2){
				  Dynamixel_SetGoalVelocity(arrHdynamixel[i], 20);
			  }
			  Dynamixel_SetGoalVelocity(arrHdynamixel[i], 24);
			  Dynamixel_SetGoalPosition(arrHdynamixel[i], arrTarget[i]);
		  }
		  HAL_Delay(1000);
		   Move to recorded positions.
		  for(uint8_t i = 0; i < numMotors; i++){
			  Dynamixel_SetGoalPosition(arrHdynamixel[i], arrRecord[i]);
			  Dynamixel_SetGoalVelocity(arrHdynamixel[i], 20);
			  if(i == 2){
				  Dynamixel_SetGoalVelocity(arrHdynamixel[i], 50);
			  }
		  }
		  HAL_Delay(1200);
	  }*/

//		Initialize array of motor handles
//		Dynamixel_HandleTypeDef* arrHdynamixel[2] = {&Motor1, &Motor2};
//
//		// Send position data to serial port while alternating between 0 and 300 degrees
//		while(1){
//			Dynamixel_GetPosition(&Motor1);
//			HAL_UART_Transmit(&huart3, &Motor1._lastPosition, 2, 100);
//
//			Dynamixel_SetGoalPosition(&Motor1, 300);
//			for(int i = 0; i < 1000; i++){
//				Dynamixel_GetPosition(&Motor1);
//				HAL_UART_Transmit(&huart3, &Motor1._lastPosition, 2, 100);
//			}
//
//			Dynamixel_SetGoalPosition(&Motor1, 0);
//			for(int i = 0; i < 1000; i++){
//				Dynamixel_GetPosition(&Motor1);
//				HAL_UART_Transmit(&huart3, &Motor1._lastPosition, 2, 100);
//			}
//
//		}
//
//		// Call test function
//		Dynamixel_TestAll(arrHdynamixel, 2);

		// Do nothing until reset or programmed
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLRCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USART3 init function */
static void MX_USART3_UART_Init(void)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART6 init function */
static void MX_USART6_UART_Init(void)
{

  huart6.Instance = USART6;
  huart6.Init.BaudRate = 1000000;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PF15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
