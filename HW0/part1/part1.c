#include <stdio.h>
#include <stdlib.h>

//==============================================================================
void printSumOfPowers(int[],int);
//==============================================================================

int main(){
    //get series of numbers and print all the numbers that powers by 2 and
    // their powers, the final message is the sum of all powers
    printf("Enter size of input:\n");
    int size=0;
    if(!(scanf("%d",&size))|| size<1){//check for legal input
        printf("Invalid size\n");
        return 0;
    }
    int *input=(int*)malloc(sizeof(int)*size);//allocating array to input
    if(input==NULL){//handling allocating failure
        printf("Invalid size\n");
        return 0;
    }
    printf("Enter numbers:\n");
    for (int i=0; i<size;++i){//saving to numbers into an array
        if(!scanf("%d",(input+i))){//check for legal input
            printf("Invalid number\n");
            free(input);
            return 0;
        }
    }
    printSumOfPowers(input,size);
    free(input);
    return 0;
}
void  printSumOfPowers(int arr[],int length){
    //get an array of numbers and its length and print all the numbers that
    // power by 2 and their power' the final message is the sum of all powers
    int sumOfAll=0;
    for (int i=0; i<length;++i){
        int temp=arr[i];//save the current number in temp
        int currentPower=0;//default power is 0
        while (temp>0&&temp%2!=1){
            currentPower++;
            temp/=2;//divide the number till the result is 1 ot odd number
        }
        if(temp==1){//if the final result is 1 the number is power by 2
            printf("The number %d is a power of 2: %d = 2^%d\n", arr[i], arr[i],
                   currentPower);
            sumOfAll+=currentPower;//sum current power to the general sum
        }
    }
    printf("Total exponent sum is %d\n",sumOfAll);//final message
    return;
}