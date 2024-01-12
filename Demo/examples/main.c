/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"

/* Femtorv32 includes*/
#include <femtorv32.h>
#include <femtoGL.h>

void vTaskFunction( void *pvParameters ) 
{ 
    char *pcTaskName; 
    volatile unsigned long ul; 
    
    pcTaskName = ( char * ) pvParameters; 
    /* As per most tasks, this task is implemented in an infinite loop. */ 
    for( ;; ) 
    { 
        /* Print out the name of this task. */ 
        printf("%s",pcTaskName); 
        /* Delay for a period. */ 
        vTaskDelay( 250 / portTICK_RATE_MS );
    } 
} 
static const char *pcTextForTask1 = "Task 1 is running\r\n"; 
static const char *pcTextForTask2 = "Task 2 is running\t\n"; 

int main( void ) 
{ 
    // femtosoc_tty_init(); // uncomment to print to SSD1351 Screen
    printf("Start to Run FreeRTOS on FemtoRV32\n"); 
    /* Create one of the two tasks. */ 
    xTaskCreate( vTaskFunction, "Task 1", 1024, (void*)pcTextForTask1, 1, NULL ); 
    
    xTaskCreate( vTaskFunction, "Task 2", 1024, (void*)pcTextForTask2, 1, NULL ); 
    /* Start the scheduler so our tasks start executing. */ 
    vTaskStartScheduler(); 
    /* If all is well then main() will never reach here as the scheduler will 
    now be running the tasks. If main() does reach here then it is likely that 
    there was insufficient heap memory available for the idle task to be created. 
    CHAPTER 5 provides more information on memory management. */ 
    for( ;; ); 
} 

