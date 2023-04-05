#include <stdio.h>

int number_input(int number[]);
void make_temp_array(int number[], int temp_array[], int size);
void number_print(int number[], int number_size);
void number_factoring(int number_size, int division_buffer[]);

unsigned long divide(unsigned long divisior, int division_buffer[], int number_size);
int return_division_result(unsigned long divisior, int number_size, int division_buffer[]);

int main() {
    int number[100];
    int number_size;
    while((number_size = number_input(number))>=1){
        int division_buffer[number_size];
        make_temp_array(number, division_buffer, number_size);
        printf("Prvociselny rozklad cisla ");
        number_print(number, number_size);
        printf(" je:\n");
        number_factoring(number_size, division_buffer);
    }
    if(number_size == -1){
        return 100;
    }
    return 0;
}

int number_input(int number[]) {
    char c;
    int number_size = 0;
    for (int i = 0; i < 100; i++) {
        if ((c = getchar()) == EOF || (i==0 &&c == '0')){
            return 0;
        } else if((c < '0' || c > '9') && c !=10){
            fprintf(stderr, "Error: Chybny vstup!\n");
            return -1;
        }
        else if (c != '\n') {
            number[i] = (int)c - 48;
        }
        else {
            number_size = i;
            break;
        }
    }
    return number_size;
}

void make_temp_array(int number[], int temp_array[], int size){
    for (int i = 0; i < size; i++){
        temp_array[i] = number[i];
    }
}

void number_print(int number[], int number_size){
    for(int i = 0; i<number_size;i++){
        printf("%d", number[i]);
    }
}
void number_factoring(int number_size, int division_buffer[]) {
    int counter;
    int global_counter = 0;
    int temp_size = number_size;
    if(number_size == 1 && division_buffer[0] == 1){
        printf("1\n");
        return;
    }

    for(int i = 2; i < 1000000; i++){
        counter = 0;
        while((divide(i, division_buffer, temp_size)) == 0){
            global_counter+=1;
            counter +=1;
            if (counter == 1 && global_counter == 1){
                printf("%d", i);
            } else if(counter == 1 && global_counter >1){
                printf(" x %d", i);
            }else if(counter == 2){
                printf("^");
            }
            temp_size = return_division_result(i, temp_size, division_buffer);
        }
        if(counter > 1){
            printf("%d", counter);
        }
    }
    printf("\n");   
}

unsigned long divide(unsigned long divisior, int division_buffer[], int number_size){
    unsigned long divided_number = division_buffer[0];
    int remainder = 0;
    for(int i = 0; i < number_size; i++){
        if(i == (number_size-1)){
            remainder = divided_number % divisior;
        } else if(divided_number/divisior > 0 && i!= (number_size-1)){
            divided_number =(divided_number % divisior)*10 + division_buffer[i+1];
        } else {
            divided_number = divided_number*10 + division_buffer[i+1];
            
        }
    }
    return remainder;
}

int return_division_result(unsigned long divisior, int number_size, int division_buffer[]){
    unsigned long divided_number = division_buffer[0];
    int temp[number_size];
    int counter = 0;
    for(int i = 0; i < number_size; i++){
        if(i == (number_size-1)){
            temp[counter] = divided_number / divisior;
            counter+=1;
        } else if(divided_number/divisior > 0 && i!= (number_size-1)){
            temp[counter] = divided_number / divisior;
            counter+=1;
            divided_number =(divided_number % divisior)*10 + division_buffer[i+1];
        } else {
            divided_number = divided_number*10 + division_buffer[i+1];
            if (counter!=0){
                temp[counter] = 0;
                counter+=1;
            }
            
        }
    }
    number_size = counter;
    make_temp_array(temp, division_buffer, number_size);
    return counter;
}
