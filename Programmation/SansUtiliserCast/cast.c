#include <stdio.h>
#include <stdio.h>

int cast(char * date){
    int resultat=0;
    int i=0;
    while(date[i]!='\0'){
        resultat=resultat*10 + (date[i]-'0');
        i++;
    }
    return resultat;
}

int age(int result,char *  date){

    int resultat=cast(date);
    int sum=result-resultat;
    return sum;
    
}
int main(){
    char * date="2020";
    int result = 2024;
    int resultat=age(result,date);
    printf("%d",resultat);
}