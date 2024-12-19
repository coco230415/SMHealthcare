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

    //���Ϸκ��� � ��� �ҷ����� 
    while (fscanf(file, "%s %d", exercise_list[exercise_list_size].exercise_name, &exercise_list[exercise_list_size].calories_burned_per_minute) == 2) {
    	exercise_list_size++;
    	
        if (exercise_list_size >= MAX_EXERCISES){
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


    //� �ɼ� ��� (%s:��̸�, %d:�Ҹ�� Į�θ�) 
  for(i=0;i<exercise_list_size;i++){
    printf("%d. Exercise: %s, Calories burned: %dkcal\n", i+1, exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute);
	}
    

    //���ϴ� � ��ȣ �Է��ϱ� 
    printf("Select the exercise you want: ");  
	scanf("%d", &choice);

    //��ȣ 0 �Է��ϸ� ������  
    if(choice == 0){
    	printf("End of exercise selection.\n");
    	return;
    }
    //��ȣ�� 1���� �۰ų� �ִ� ��ȣ���� ũ�� �Է��ϸ� �ٽ� �Է��ϱ�
    if(choice < 1 || choice > exercise_list_size){
        printf("Invalid choice. Try again.\n");
		return;
	}
    //��ȣ �ùٸ��� �Է½� ��� �ð� �Է��ϱ�  &  health_data�� ������ ���� �� ���� 
    	else if ( 1 <= choice && choice <= exercise_list_size){
    	printf("Enter the duration of the exercise(in minutes): ");
    	scanf("%d", &duration);
    

    //��� �ð��� ���� Į�θ� �Ҹ� ����ϱ�
	// int total_calories_burned;
	 total_calories_burned = exercise_list[choice - 1].calories_burned_per_minute * duration;
	 
    //������ ��� Į�θ� health data�� �����ϱ� (exercise count�� ������) 
    //������ � �����ϱ�, ������ � count�� ���� 
    int j;
	for(j=0;exercise_list[choice - 1].exercise_name[j] != '\0'; j++) {
		health_data->exercises[health_data->exercise_count].exercise_name[j] = exercise_list[choice - 1].exercise_name[j];
	}
	//���ڿ� ���������� ��µǱ� ���� null �Լ� �߰��ϱ� 
	health_data->exercises[health_data->exercise_count].exercise_name[j] = '\0';
	
	//������ ��� Į�θ� �����ϱ�, Į�θ� �����ϱ�  
	health_data->exercises.calories_burned_per_minute = exercise_list[choice - 1].calories_burned_per_minute;
	health_data->total_calories_burned = total_calories_burned;
   
    health_data->exercise_count++;	
	
	// ��� 
	pritnf("You burned %d calories by %s for %d minutes.\n", total_calories_burned  exercise_list[choice - 1].exercise_name[j], duration);
	
   
