#include "main.h"
#include "cmsis_os.h"

osThreadId defaultTaskHandle;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void StartDefaultTask_DOWN(void const * argument);
void StartDefaultTask_RIGHT(void const * argument);
void StartDefaultTask_UP(void const * argument);
void StartDefaultTask_LEFT(void const * argument);

int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();

  osThreadDef(defaultTask, StartDefaultTask_DOWN, osPriorityNormal, 1, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

	osThreadDef(defaultTask_1, StartDefaultTask_RIGHT, osPriorityNormal, 1, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask_1), NULL);

	osThreadDef(defaultTask_2, StartDefaultTask_UP, osPriorityNormal, 1, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask_2), NULL);

	osThreadDef(defaultTask_3, StartDefaultTask_LEFT, osPriorityNormal, 1, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask_3), NULL);

  osKernelStart();

}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}


static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOD_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_15 | GPIO_PIN_14 | GPIO_PIN_13 | GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15 | GPIO_PIN_14 | GPIO_PIN_13 | GPIO_PIN_12, GPIO_PIN_RESET);

}

void StartDefaultTask_DOWN(void const * argument)
{
	for(;;)
  {
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
    osDelay(100);															// I don't understand how counted this delay ???
	}
}

void StartDefaultTask_RIGHT(void const * argument)
{
	for(;;)
  {
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
    osDelay(100);															// I don't understand how counted this delay ???
	}
}

void StartDefaultTask_UP(void const * argument)
{
	for(;;)
  {
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
    osDelay(100);															// I don't understand how counted this delay ???
	}
}

void StartDefaultTask_LEFT(void const * argument)
{
	for(;;)
  {
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
    osDelay(100);															// I don't understand how counted this delay ???
	}
}


void Error_Handler(void)
{

}

#ifdef  USE_FULL_ASSERT

void assert_failed(char *file, uint32_t line)
{ 

}
#endif /* USE_FULL_ASSERT */
