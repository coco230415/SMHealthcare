//
//  main.c
//  Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define EXERCISEFILEPATH "exercises.txt"
#define DIETFILEPATH "diets.txt"
#define HEALTHFILEPATH "health_data.txt"

static int choice;

int main() {
	// To initialize the health data object
    HealthData health_data = {0};
    
    // Tocode: to read the list of the exercises and diets
    loadExercises(EXERCISEFILEPATH);
    loadDiets(DIETFILEPATH);

    int remaining_calories;
    remaining_calories = (health_data.total_calories_intake) - BASAL_METABOLIC_RATE - (health_data.total_calories_burned);
    
    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    //모든 칼로리 소비되거나 사용자가 시스템 끝내길 바랄때까지 동작함  
    do {
    	if (remaining_calories == 0){                                     //남아있는 칼로리가 0이 되면 모든 칼로리 소비했다고 출력됨  
            printf("You have consumed all your calories for today! \n");
		} 
		else{                                                             //0이 아니면 옵션 뜸  
			printf("\n=======================================================================\n");
        	printf("[Healthcare Management Systems] \n");
        	printf("1. Exercise \n");
        	printf("2. Diet \n");
        	printf("3. Show logged information \n");
        	printf("4. Exit \n");
        	printf("Select the desired number: ");
        	scanf("%d", &choice);
        	printf("=======================================================================\n");
        }
        
		// ToCode: to run the sysmtem based on the user's choice
		//사용자의 선택에 따른 시스템 동작 
        switch (choice) {
            case 1:
            	inputExercise(&health_data); 
                break;
                
            case 2:
            	inputDiet(&health_data); 
                break;
                
            case 3:
            	printHealthData(&health_data);
		        break;
                
            case 4:
    			printf("Exit the system.\n");
    			printf("=======================================================================\n");
                break;
                
            default:
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n");
        }
    } while (choice != 4);

    return 0;
}

