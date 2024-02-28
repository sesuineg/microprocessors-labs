#include "cmsis_boot/stm32f4xx.h"
#include "cmsis_lib/include/stm32f4xx_gpio.h"
#include "cmsis_lib/include/stm32f4xx_rcc.h"
#include "cmsis_lib/include/stm32f4xx_tim.h"
#include "cmsis_lib/include/misc.h"

void Delay(uint32_t nCount) {
    while (nCount--) {
    }
}

static int a = 0;


static void resetLed(int a) {
    switch (a % 4) {
        case 0:
            GPIO_SetBits(GPIOD, GPIO_Pin_12);
            GPIO_ResetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

            break;
        case 1:
            GPIO_SetBits(GPIOD, GPIO_Pin_13);
            GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15);
            break;

        case 2:
            GPIO_SetBits(GPIOD, GPIO_Pin_14);
            GPIO_ResetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_12 | GPIO_Pin_15);
            break;

        case 3:
            GPIO_SetBits(GPIOD, GPIO_Pin_15);
            GPIO_ResetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_12 | GPIO_Pin_14);
            break;
    }
}

void TIM2_IRQHandler(void) {
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        a++;
        resetLed(a);

        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//        GPIOD->ODR ^= GPIO_Pin_13;
    }
}

void INTTIM_Config(void) {
    RCC_ClocksTypeDef   RCC_ClocksStatus;
    RCC_GetClocksFreq(&RCC_ClocksStatus);

    NVIC_InitTypeDef nvic_struct;
    nvic_struct.NVIC_IRQChannel = TIM2_IRQn;
    nvic_struct.NVIC_IRQChannelPreemptionPriority = 0;
    nvic_struct.NVIC_IRQChannelSubPriority = 1;
    nvic_struct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_struct);
    TIM_TimeBaseInitTypeDef tim_struct;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    tim_struct.TIM_Period = 10000 - 1;
    tim_struct.TIM_Prescaler = (RCC_ClocksStatus.PCLK1_Frequency/10000-1);
    tim_struct.TIM_ClockDivision = 0;
    tim_struct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &tim_struct);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}

void GPIO_Setup() {
    GPIO_InitTypeDef gpioConf;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    gpioConf.GPIO_Pin = GPIO_Pin_0;
    gpioConf.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(GPIOA, &gpioConf);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    // инициализация входа, подключенного к светодиоду
    gpioConf.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15;
    gpioConf.GPIO_Mode = GPIO_Mode_OUT;
    gpioConf.GPIO_Speed = GPIO_Speed_100MHz;
    gpioConf.GPIO_OType = GPIO_OType_PP;
    gpioConf.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(GPIOD, &gpioConf);
}

int main(void) {

    GPIO_Setup();
    INTTIM_Config();

    while (1) {}
}
