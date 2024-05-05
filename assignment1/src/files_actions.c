#include "../header/files_actions.h"

void backtrack(FILE* file){
    fseek(file, -1, SEEK_CUR);
}

void write_token(FILE* file, char* token, char* token_class){
    fprintf(file, "%s,%s\n", token, token_class);

}

