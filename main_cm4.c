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


void TaskRedLedState()
{
   for(;;) {
    Cy_GPIO_Write(RED_PORT, RED_NUM, !Cy_GPIO_Read(RED_PORT,RED_NUM));
    vTaskDelay(pdMS_TO_TICKS(500));
}
}
int main(void)
{
    __enable_irq(); /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    xTaskCreate(TaskRedLedState,"Tache de clignotement",200, NULL,0,NULL);
    
    vTaskStartScheduler();
    
    for(;;)
    {
        /* Place your application code here. */
        

    }
}

/* [] END OF FILE */
