#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

// Function to configure GPIO settings
void GPIO_config()
{
    RCC->AHB1ENR = 0x00000009;  // Enable clock for GPIOA and GPIOD
    GPIOD->MODER = 0x55000000;  // Set GPIOD pins 12, 13, 14, 15 to output mode
    GPIOD->OTYPER = 0x00000000; // Set output type to push-pull
    GPIOD->OSPEEDR = 0xFF000000; // Set GPIO speed to high
    GPIOD->PUPDR = 0x00000000;  // No pull-up/pull-down resistors
}

// Function to configure EXTI (External Interrupt) settings
void EXTI_config()
{
    RCC->APB2ENR = 0x00004000;  // Enable clock for SYSCFG
    SYSCFG->EXTICR[0] = 0x00000000; // Configure EXTI line 1 to use GPIOA
    NVIC_EnableIRQ(EXTI1_IRQn); // Enable EXTI1 interrupt in NVIC
    EXTI->IMR = 0x00000002;    // Enable interrupt for EXTI line 1
    EXTI->RTSR = 0x00000002;   // Enable rising edge trigger for EXTI line 1
    EXTI->FTSR = 0x00000002;   // Enable falling edge trigger for EXTI line 1
}

// Interrupt service routine for EXTI line 1
void EXTI1_IRQHandler()
{

    if (EXTI->PR & 0x00000002) // Check if interrupt pending bit is set
    {
        if (GPIOA->IDR & 0x00000002) // Check the status of GPIOA pin 1
        {
            GPIOD->ODR = 0x00000000; // Turn off LEDs on GPIOD
        }
        else
        {
            GPIOD->ODR = 0x0000F000; // Turn on LEDs on GPIOD
        }
        EXTI->PR = 0x00000002; // Clear the pending bit for EXTI line 1
    }
}

int main(void)
{
    GPIO_config();   // Initialize GPIO settings
    EXTI_config();   // Initialize EXTI settings
    while (1)
    {
        // Main loop - program runs indefinitely
    }
}

// Callback function for audio transfer complete
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
    /* TODO, implement your code here */
    return;
}

// Callback function used by stm324xg_eval_audio_codec.c
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
    /* TODO, implement your code here */
    return -1;
}
