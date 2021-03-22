/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "params.h"
#include "queue.h"
#include <string.h>
#include <stdio.h>

SemaphoreHandle_t Semaphore ;
bool isPressed = false;


void TaskRedLedState(){
   for(;;) {
    Cy_GPIO_Write(RED_PORT, RED_NUM, !Cy_GPIO_Read(RED_PORT,RED_NUM));
    vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void isr_bouton(void){

    xSemaphoreGiveFromISR(Semaphore,NULL);

    CyDelay(20);
    
    
    isPressed = !isPressed; //on inverse l'etat du bouton
    Cy_GPIO_ClearInterrupt(Bouton_0_PORT, Bouton_0_NUM);
    NVIC_ClearPendingIRQ(Bouton_ISR_cfg.intrSrc);
       
}

void bouton_task(){
    
    for (;;){
       
        if(xSemaphoreTake(Semaphore,100) == pdTRUE){
            
            //indicateur de bouton (variable) = isPressed
            if(isPressed){
                UART_PutString("bouton appuye \r\n");
            }
            else{
                UART_PutString("bouton relache \r\n");
            }
            
        }  
    }
}




int main(void)
{
    __enable_irq(); /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    Semaphore = xSemaphoreCreateBinary();
    UART_Start();
    
    Cy_SysInt_Init(&Bouton_ISR_cfg, isr_bouton);
    NVIC_ClearPendingIRQ(Bouton_ISR_cfg.intrSrc);
    NVIC_EnableIRQ(Bouton_ISR_cfg.intrSrc);
    
    xTaskCreate(TaskRedLedState,"Tache de clignotement",200, NULL,1,NULL);
    xTaskCreate(bouton_task,"Bouton",1000,NULL,1,NULL);
    vTaskStartScheduler();
    
    
  
    
    for(;;)
    {
       /* Place your application code here. */
    

    }
}

/* [] END OF FILE */
