#include <stdio.h>
#include <stdlib.h>

void xor(char *txt, size_t txt_len, char *key, size_t key_len, char *txt_xor){
    int index = 0;
    if(txt_len > 0 && key_len > 0){
        for(index = 0; index < txt_len; index++)
            txt_xor[index] = txt[index] ^ key[index % key_len];
    }
}
