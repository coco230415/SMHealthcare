//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0;
 

/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    //파일로부터 운동 목록 불러오기 (운동과 분당 소모한 칼로리) 
    while (fscanf(file, "%s %d", exercise_list[exercise_list_size].exercise_name, &exercise_list[exercise_list_size].calories_burned_per_minute) == 2) {
    	exercise_list_size++;
    	
        if (exercise_list_size >= MAX_EXERCISES){    //만약 운동 목록 개수 초과하면 break 
        	break;
		}
    }

    fclose(file);
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    // ToCode: to provide the options for the exercises to be selected
    printf("The list of exercises: \n");


    //운동 옵션 출력 (%d:번호, %s:운동이름, %d:소모된 칼로리) (i=0부터 시작하는데 번호 1번부터 있는것으로 하려고 i+1) 
  for(i=0;i<exercise_list_size;i++){
    printf("%d. Exercise: %s, Calories burned: %dkcal\n", i+1, exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute);
	}
    

    //원하는 운동 번호 입력하기 
    printf("Select the exercise you want: ");  
	scanf("%d", &choice);

    //번호 0 입력하면 끝내기 (번호 1부터 시작이므로) 
    if(choice == 0){
    	printf("End of exercise selection.\n");
    	return;
    }
    //번호가 1보다 작거나 최대 번호보다 크게 입력하면 다시 입력하기
    if(choice < 1 || choice > exercise_list_size){
        printf("Invalid choice. Try again.\n");
		return;  
	}
    //번호(choice)올바르게 입력시 운동할 시간(분당) 입력하기  &  health_data에 데이터 저장 및 누적 
    	printf("Enter the duration of the exercise(in minutes): ");
    	scanf("%d", &duration); 
    

    //운동한 시간에 따른 칼로리 소모 계산하기
	int total_calories_burned;                                                               //소모한 모든 칼로리의 합  
	total_calories_burned = exercise_list[choice - 1].calories_burned_per_minute * duration; //합=분당 소모하는 칼로리*운동한 시간(분) 
	 
    //선택한 운동과 칼로리 health data에 저장하기 (exercise count로 계속 누적함) 
    //선택한 운동 저장하기, 선택한 운동 count로 누적 
    int j;
	for(j=0;exercise_list[choice - 1].exercise_name[j] != '\0'; j++) {
		health_data->exercises[health_data->exercise_count].exercise_name[j] = exercise_list[choice - 1].exercise_name[j];
	}
	//문자열 정상적으로 출력되기 위해 null 함수 추가하기 (문자열 끝나는 것을 표시하기 위함) 
	health_data->exercises[health_data->exercise_count].exercise_name[j] = '\0';
	
	//선택한 운동의 소모하는 분당 칼로리 health_data에 저장하기, 칼로리 누적하기(total)  
	health_data->exercises[health_data->exercise_count].calories_burned_per_minute = exercise_list[choice - 1].calories_burned_per_minute;
	health_data->total_calories_burned = total_calories_burned;
   
    health_data->exercise_count++;	
	
	// 사용자에게 출력되는 메시지  
	printf("You burned %d calories by eating %s for %d minutes.\n", total_calories_burned, exercise_list[choice - 1].exercise_name, duration);
}
