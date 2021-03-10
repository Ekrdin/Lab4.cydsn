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


void ReverseRedLedState()
{
    
    Cy_GPIO_Write(RED_PORT,RED_NUM,1);
    CyDelay(500);
    Cy_GPIO_Write(RED_PORT,RED_NUM,0);
    CyDelay(500);

}
int main(void)
{
    __enable_irq(); /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    
    for(;;)
    {
        /* Place your application code here. */
        
     ReverseRedLedState();
     vTaskDelay(pdMS_TO_TICKS(500));
    }
}

/* [] END OF FILE */
