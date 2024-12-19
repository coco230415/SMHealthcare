//
//  cal_diets.c
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

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0;


/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

     //파일로부터 다이어트 식단 목록 읽어와 저장  
    while (fscanf(file, "%s %d", diet_list[diet_list_size].food_name, &diet_list[diet_list_size].calories_intake) == 2)                     ) {
    	diet_list_size++; 
    	
        if (diet_list_size >= MAX_DIETS){
        	break;
     	}
    }
    fclose(file);
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice, i;
    
    //선택된 diet 목록 출력  
    printf("The list of diets:\n");
   
    for(i=0;i<diet_list_size;i++){
    printf("%d. Food: %s, Calories intake: %dkcal\n", i+1, diet_list[i].food_name, diet_list[i].calories_intake);
	}
    
	//선택할 diet 식단 입력하기 (번호로) 
    printf("Select the diet you want: ");
	scanf("%d", &choice); 

    //입력한 번호가 0이면 식단선택 종료 
    if(choice == 0){
    	printf("End of diet selection.\n");
    	return;
}
    //입력한 번호가 1보다 작거나  식단 목록개수보다 크면 다시 입력하라고 하기 
    if(choice < 1 || choice > diet_list_size){
        printf("Invalid coice. Try again.\n");
		return; 
}
    //존재하는 번호 입력시 선택된 식단,칼로리 출력되고 health data에 저장됨 
    else if (1 <= choice && choice <= diet_list_size){
    
    //총 칼로리 정의 
    total_calories_intake = diet_list[choice - 1].calories_intake;
    
    
	int j;
	for(j=0;diet_list[choice - 1].food_name[j] != '\0'; j++) {
	health_data->diet[health_data->diet_count].food_name[j] = diet_list[choice - 1].food_name[j];
	}
	
	//문자열 정상적으로 출력되기 위해(끝) null 함수 추가하기 
	health_data->diet[health_data->diet_count].food_name[j] = '\0';
	
	//선택한 식단의 칼로리 저장하기, 칼로리 누적하기  
	health_data->diet[health_data->diet_count].calories_intake = diet_list[choice - 1].calories_intake;
	health_data->total_calories_intake = total_calories_intake;
   
    health_data->diet_count++;	
	
    //누적된 선택한 식단 및 칼로리 전부 출력
	 
    for(j=0; j< health_data->diet_count; j++)
    printf("Food: %s, Calories intake: %dkcal\n", health_data->diet.food_name[j], health_data->diet.total_calories_intake);
    


}

