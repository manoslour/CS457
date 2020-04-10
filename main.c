/*************************************************************
 * @file   main.c                                            *
 * @author Lourakis Manos <csd3153@csd.uoc.gr>  	         *
 *                                                    	     *
 * @brief  Main file for the needs of CS457 Assignment 1     *
 ************************************************************/

#include "cs457_crypto.h"

int main(int argc, char **argv){

    FILE *fin;
    int N, circ, len;
    long int textSize;
    char *mode;
    uint8_t *buff, *key, *keyword, *encryptedText, *decryptedText;

    buff = (uint8_t*)malloc(BUFFER_SIZE * sizeof(uint8_t));
    keyword = (uint8_t*)malloc(BUFFER_SIZE * sizeof(uint8_t));

    if(argc != 3){
        printf("Error, Wrong input\n");
        return EXIT_FAILURE;
    }

    if( (fin = fopen(argv[2], "r")) == NULL){
        printf("Cant open file: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    mode = argv[1];
    fgets(buff, BUFFER_SIZE, fin);
    buff[strcspn(buff, "\n")] = 0; //Removes trailing newline char from fgets() input
    textSize = strlen(buff);

    buff = strdup(removeIllegal(buff));
    
    switch (*mode)
    {
        case 'O':
            key = strdup(generateKey(textSize));
            encryptedText = strdup(otp_encrypt(buff, key));
            decryptedText = strdup(otp_decrypt(encryptedText, key));
            break;
        case 'C':
            printf("Enter N: ");
            scanf("%d", &N);
            encryptedText = strdup(caesar_encrypt(buff, N, 1));
            decryptedText = strdup(caesar_decrypt(encryptedText, N));
            break;
        case 'S':
            printf("Enter circ: ");
            scanf("%d", &circ);
            printf("Enter len: ");
            scanf("%d", &len);
            encryptedText = strdup(spartan_encrypt(buff, circ, len));
            decryptedText = strdup(spartan_decrypt(encryptedText, circ, len));
            break;
        case 'V':
            printf("Enter keyword: ");
            scanf("%s", keyword);
            key = strdup(generateVigKey(keyword, textSize));
            encryptedText = vigenere_encrypt(buff, key);
            break;
        default:
            printf("Invalid Mode\n");
            break;
    }

    fclose(fin);
    return 0;
}