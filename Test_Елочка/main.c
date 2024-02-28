#include "cmsis_boot/stm32f4xx.h"
#include "cmsis_lib/include/stm32f4xx_gpio.h"
#include "cmsis_lib/include/stm32f4xx_rcc.h"

void Delay(uint32_t nCount) {
    while (nCount--) {
    }
}

static void resetLed(int a) {
    switch (a % 4) {
        case 0:
            GPIO_SetBits(GPIOD, GPIO_Pin_12);
            GPIO_ResetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

            break;
        case 1:
            GPIO_SetBits(GPIOD, GPIO_Pin_13);
            GPIO_ResetBits(GPIOD,  GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15);
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

int main(void) {
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

    static int a = 0;

    while (1) {
        resetLed(0);
        Delay(100000);
        resetLed(1);
        Delay(100000);
        resetLed(2);
        Delay(100000);
        resetLed(3);
        Delay(100000);
        GPIO_ResetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15| GPIO_Pin_12);

//        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0) {
//            Delay(5000);
//            a++;
//            resetLed(a);
//            while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0);
//            Delay(2000);
//        }
    }
}
