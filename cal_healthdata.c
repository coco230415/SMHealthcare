//
//  cal_healthdata.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"


/*
    description : enter the exercise and diet history in "health_data.txt" 
    input parameters : health_data - data object in which the selected exercise and diet is stored
    return value : No
    
    operation : 1. save the chosen exercise and total calories burned 
    			2. save the chosen diet and total calories intake 
    			3. save the total remaining calrories
*/

void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {
	int i;
    FILE* file = fopen(HEALTHFILEPATH, "w");
    if (file == NULL) {
        printf("There is no file for health data.\n");
        return;
    }


    //선택한 운동과 소모한 누적 칼로리 저장 
    fprintf(file, "[Exercises] \n");
    for(i=0; i<health_data->exercise_count; i++){
    	fprintf(file, "Exercise: %s, Calories burned per minute: %d kcal\n", health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute);
}
    //총 소모한 운동 칼로리 출력 
        fprintf(file, "Total calories burned: %d kcal\n", health_data->total_calories_burned);
    
    
    
    //선택한 식단과 섭취한 칼로리  
	fprintf(file, "\n[Diets] \n");
    
	for(i=0; i< health_data->diet_count; i++){
        fprintf(file, "Food: %s, Calories intake: %d kcal\n", 
		health_data->diet[i].food_name, health_data->diet[i].calories_intake);
	}
    // 총 섭취한 식단 칼로리 출력 
	    fprintf(file, "Total calories intake: %d kcal\n", health_data->total_calories_intake);
    

    // ToCode: to save the total remaining calrories
    //남은 칼로리  (섭취 칼로리-기초대사량-소모된 칼로리) 
    int remaining_calories;
    int Basal_Metabolic_Rate;
    
    fprintf(file, "\n[Total] \n");
    remaining_calories = (health_data->total_calories_intake) - Basal_Metabolic_Rate - (health_data->total_calories_burned);
    fprintf(file, "Basal Metabolic Rate: %d kcal\n", 1300);
    fprintf(file, "Total calories burned: %d kcal\n", health_data->total_calories_burned);
    fprintf(file, "Total calories intake: %d kcal\n", health_data->total_calories_intake);
    fprintf(file, "The remaing calories: %d kcal\n", remaining_calories);
    
    fclose(file);   
}

/*
    description : print the history of exercised and diets
    input parameters : health_data - data object in which the history of the exercise and diet is to be printed
    return value : No
    
    operation : 1. print out the saved history of exercises
    			2. print out the saved history of diets
    			3. print out the saved history of calories
*/

void printHealthData(const HealthData* health_data) {
	int i;
	int remaining_calories;
	// ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
    for(i=0; i<health_data->exercise_count; i++){
        printf("Exercise: %s, Calories burned per minute: %d kcal\n",  
     	health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute); 
    }
    printf("=======================================================================\n");


    // ToCode: to print out the saved history of diets
    printf("============================= History of Diet =========================\n");
    for(i=0; i< health_data->diet_count; i++){
        printf("Food: %s, Calories intake: %d kcal\n", 
		health_data->diet[i].food_name, health_data->diet[i].calories_intake);
    }
    printf("=======================================================================\n");


	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// total calories burned, total calories intake, and the remaining calories
	printf("============================== Total Calories =========================\n");
    printf("Basal Metabolic Rate: %d kcal\n", 1300);
    printf("Total calories burned: %d kcal\n", health_data->total_calories_burned);
    printf("Total calories intake: %d kcal\n", health_data->total_calories_intake);
    printf("The remaing calories: %d kcal\n", remaining_calories);
 
    printf("=======================================================================\n \n");
    
	  
    // 사용자에게 추천 사항 제공 (남은 칼로리 0인 경우, <0인 경우, >0 인 경우) 
	if(remaining_calories == 0){
    	printf("You have consumed all your calories for today!\n");
	}else if(remaining_calories < 0){
        printf("[Warning] Too few calories!\n");
        if(health_data->total_calories_intake == DAILY_CALORIE_GOAL){
            printf("Your total calorie intake for today has reached your goal!\n");
        }else if(health_data->total_calories_intake < DAILY_CALORIE_GOAL){
	     	printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n");        
        }else  {
            printf( "You have eaten more calories than planned today, but you have exercised too much!\n");	
		}
    } 
    else{
        printf("Please exercise for your health!\n");
        if (health_data->total_calories_intake == DAILY_CALORIE_GOAL) {
            printf("Your total calorie intake for today has reached your goal!\n");  
        }else if(health_data->total_calories_intake < DAILY_CALORIE_GOAL){
        	printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n");
        }
    }

	 printf("=======================================================================\n");
}
