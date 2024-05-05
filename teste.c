#include <stdio.h>
#include <string.h>

int main(){
    char string[20] = "";

    printf("%d\n",strlen(string));

    string[strlen(string)] = 'L';
    //string[strlen(string)+1] = '\0';

    printf("%s\n",string);
}