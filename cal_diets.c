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

     //���Ϸκ��� ���̾�Ʈ �Ĵ� ��� �о�� ����  
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
    
    //���õ� diet ��� ���  
    printf("The list of diets:\n");
   
    for(i=0;i<diet_list_size;i++){
    printf("%d. Food: %s, Calories intake: %dkcal\n", i+1, diet_list[i].food_name, diet_list[i].calories_intake);
	}
    
	//������ diet �Ĵ� �Է��ϱ� (��ȣ��) 
    printf("Select the diet you want: ");
	scanf("%d", &choice); 

    //�Է��� ��ȣ�� 0�̸� �Ĵܼ��� ���� 
    if(choice == 0){
    	printf("End of diet selection.\n");
    	return;
}
    //�Է��� ��ȣ�� 1���� �۰ų�  �Ĵ� ��ϰ������� ũ�� �ٽ� �Է��϶�� �ϱ� 
    if(choice < 1 || choice > diet_list_size){
        printf("Invalid coice. Try again.\n");
		return; 
}
    //�����ϴ� ��ȣ �Է½� ���õ� �Ĵ�,Į�θ� ��µǰ� health data�� ����� 
    else if (1 <= choice && choice <= diet_list_size){
    
    //�� Į�θ� ���� 
    total_calories_intake = diet_list[choice - 1].calories_intake;
    
    
	int j;
	for(j=0;diet_list[choice - 1].food_name[j] != '\0'; j++) {
	health_data->diet[health_data->diet_count].food_name[j] = diet_list[choice - 1].food_name[j];
	}
	
	//���ڿ� ���������� ��µǱ� ����(��) null �Լ� �߰��ϱ� 
	health_data->diet[health_data->diet_count].food_name[j] = '\0';
	
	//������ �Ĵ��� Į�θ� �����ϱ�, Į�θ� �����ϱ�  
	health_data->diet[health_data->diet_count].calories_intake = diet_list[choice - 1].calories_intake;
	health_data->total_calories_intake = total_calories_intake;
   
    health_data->diet_count++;	
	
    //������ ������ �Ĵ� �� Į�θ� ���� ���
	 
    for(j=0; j< health_data->diet_count; j++)
    printf("Food: %s, Calories intake: %dkcal\n", health_data->diet.food_name[j], health_data->diet.total_calories_intake);
    


}

