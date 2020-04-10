/*************************************************************
 * @file   cs457_crypto.c                                    *
 * @author Lourakis Manos <csd3153@csd.uoc.gr>  	         *
 *                                                    	     *
 * @brief  Source file for the needs of CS457 Assignment 1   *
 ************************************************************/

#include "cs457_crypto.h"

uint8_t* generateKey(long int size){
    int fd;
    uint8_t *buffer = (uint8_t* )malloc(size * sizeof(uint8_t));
    fd = open("/dev/urandom", O_RDONLY);
    read(fd, buffer, size);
    close(fd);
    return buffer;
}

uint8_t* generateVigKey(uint8_t *keyword, long int textsize){
    int i, x = 0;
    uint8_t *key = (uint8_t*)malloc(textsize * sizeof(uint8_t));
    for(i = 0; i < textsize; i++){
        if(keyword[x] == '\0')
            x = 0;
        key[i] = keyword[x];
        x++;
    }
    return key;
}

uint8_t* removeIllegal(uint8_t *plaintext){
    int i, j;
    // Remove illegal characters fron plaintext
    for(i = 0; plaintext[i] != '\0'; i++){
        while(!((plaintext[i] >= 48 && plaintext[i] <= 57) || (plaintext[i] >= 65 && plaintext[i] <= 90) || (plaintext[i] >= 97 && plaintext[i] <= 122) || plaintext[i] == '\0')) {
            for(j = i; plaintext[j] != '\0'; j++){
                plaintext[j] = plaintext[j+1];
            }
            plaintext[j] = '\0';
        }
    }
    return plaintext;
}

uint8_t* otp_encrypt(uint8_t *plaintext, uint8_t *key){
    int i;
    long int textSize;
    uint8_t *encryptedText;
    
    textSize = strlen(plaintext);
    encryptedText = (uint8_t*)malloc(textSize * sizeof(uint8_t));

    printf("\n-------------------- "GREEN"OTP ENCRYPTION"RESET" --------------------\n");
    for(i = 0; i < textSize; i++){
        printf("Key: [%d|%c]\tText: [%d|%c]", key[i], key[i], plaintext[i], plaintext[i]);
        encryptedText[i] = plaintext[i] ^ key[i];
        printf("\tencryptedText: [%d|%c]\n", encryptedText[i], encryptedText[i]);
    }
    return encryptedText;
}

uint8_t* otp_decrypt(uint8_t *ciphertext, uint8_t *key){
    int i;
    long int textSize;
    uint8_t *decryptedText;

    textSize = strlen(ciphertext);
    decryptedText = (uint8_t*)malloc(textSize * sizeof(uint8_t));

    printf("\n-------------------- "YEL"OTP DECRYPTION"RESET" --------------------\n");
    for(i = 0; i < textSize; i++){
        printf("Key: [%d|%c]\tText: [%d|%c]", key[i], key[i], ciphertext[i], ciphertext[i]);
        decryptedText[i] = ciphertext[i] ^ key[i];
        printf("\tdecryptedText: [%d|%c]\n", decryptedText[i], decryptedText[i]);
    }
    return decryptedText;
}

uint8_t* caesar_encrypt(uint8_t *plaintext, unsigned short N, int flag){
    int i;
    long int textSize;
    uint8_t *encryptedtext;

    textSize = strlen(plaintext);
    encryptedtext = (uint8_t*)malloc(textSize * sizeof(uint8_t));

    if(flag == 1)
        printf("\n------------------ "GREEN"CAESARS ENCRYPTION"RESET" ------------------\n");
    for(i = 0; i < textSize; i++){
        if(plaintext[i] >= 48 && plaintext[i] <= 57){
            encryptedtext[i] = (plaintext[i] + N - 48) % 10 + 48;
            if(flag == 1)
                printf("plaintext[%d] = %c \t|\t encryptedtext[%d] = %c\n", i, plaintext[i], i, encryptedtext[i]);
        }
        else if(plaintext[i] >= 65 && plaintext[i] <= 90){
            encryptedtext[i] = (plaintext[i] + N - 65) % 26 + 65;
            if(flag == 1)
                printf("plaintext[%d] = %c \t|\t encryptedtext[%d] = %c\n", i, plaintext[i], i, encryptedtext[i]);
        }
        else{
            encryptedtext[i] = (plaintext[i] + N - 97) % 26 + 97;
            if(flag == 1)
                printf("plaintext[%d] = %c \t|\t encryptedtext[%d] = %c\n", i, plaintext[i], i, encryptedtext[i]);
        }
    }
    return encryptedtext;
}

uint8_t* caesar_decrypt(uint8_t *ciphertext, unsigned short N){
    int i;
    long int textSize;
    uint8_t *decryptedtext;

    textSize = strlen(ciphertext);
    decryptedtext = (uint8_t*)malloc(textSize * sizeof(uint8_t));

    printf("\n------------------ "YEL"CAESARS DECRYPTION"RESET" ------------------\n");
    for(i = 0; i < textSize; i++){
        if(ciphertext[i] >= 48 && ciphertext[i] <= 57){
            decryptedtext[i] = (ciphertext[i] + (10 - N) - 48) % 10 + 48;
            printf("ciphertext[%d] = %c \t|\t decryptedtext[%d] = %c\n", i, ciphertext[i], i, decryptedtext[i]);
        }
        else if(ciphertext[i] >= 65 && ciphertext[i] <= 90){
            decryptedtext[i] = (ciphertext[i] + (26 - N) - 65) % 26 + 65;
            printf("ciphertext[%d] = %c \t|\t decryptedtext[%d] = %c\n", i, ciphertext[i], i, decryptedtext[i]);
        }
        else{
            decryptedtext[i] = (ciphertext[i] + (26 - N) - 97) % 26 + 97;
            printf("ciphertext[%d] = %c \t|\t decryptedtext[%d] = %c\n", i, ciphertext[i], i, decryptedtext[i]);
        }
    }
    return decryptedtext;
}

uint8_t* spartan_encrypt(uint8_t *plaintext, unsigned short circ, unsigned short len){
    int i, j, z;
    long int textSize;
    uint8_t *ciphertext;
    uint8_t encryptedtext[circ][len];

    z = 0;
    textSize = strlen(plaintext);
    ciphertext = (uint8_t*)malloc( (circ * len) * sizeof(uint8_t));

    printf("\n------------------ "GREEN"SCYTALE ENCRYPTION"RESET" ------------------\n");
    while(z < textSize){
        for(i = 0; i < circ; i++){
            for(j = 0; j < len; j++){
                if(plaintext[z] == '\0')
                    encryptedtext[i][j] = '#';
                else
                    encryptedtext[i][j] = plaintext[z];
                z++;
            }
        }
    }

    z = 0;
    for(j = 0; j < len; j++){
        for(i = 0; i < circ; i++){
            ciphertext[z] = encryptedtext[i][j];
            z++;
        }
    }

    printf("\n");
    for(i = 0; i < circ; i++){
        printf("|");
        for(j = 0; j < len; j++){
            printf("%c|", encryptedtext[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Ciphertext = %s\n", ciphertext);
    return ciphertext;
}

uint8_t* spartan_decrypt(uint8_t *ciphertext, unsigned short circ, unsigned short len){
    int i, j, z;
    long int textSize;
    uint8_t *finaltext;
    uint8_t decryptedtext[circ][len];

    z = 0;
    textSize = strlen(ciphertext);
    finaltext = (uint8_t*)malloc( (circ * len) * sizeof(uint8_t));

    printf("\n------------------ "YEL"SCYTALE DECRYPTION"RESET" ------------------\n");
    while(z < textSize){
        for(j = 0; j < len; j++){
            for(i = 0; i < circ; i++){
                if(ciphertext[z] == '\0')
                    decryptedtext[i][j] = '#';
                else
                    decryptedtext[i][j] = ciphertext[z];
                z++;
            }
        }
    }

    z = 0;
    for(i = 0; i < circ; i++){
        for(j = 0; j < len; j++){
            finaltext[z] = decryptedtext[i][j];
            z++;
        }
    }

    printf("\n");
    for(i = 0; i < circ; i++){
        printf("|");
        for(j = 0; j < len; j++){
            printf("%c|", decryptedtext[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Decryptedtext = %s\n", finaltext);
    return finaltext;
}

uint8_t* vigenere_encrypt(uint8_t *plaintext, uint8_t *key){

    int i, j, row, col;
    uint8_t tabula_recta[26][26];
    long int textsize = strlen(plaintext);
    uint8_t *letter = (uint8_t*)malloc(sizeof(uint8_t));
    uint8_t *finaltext = (uint8_t*)malloc(textsize * sizeof(uint8_t));

    for(i = 0; i < 26; i++){
        for(j = 0; j < 26; j++){
            letter[0] = (uint8_t)(i + 65);
            letter = caesar_encrypt(letter, j, 0);
            tabula_recta[i][j] = letter[0];
        }
    }

    printf("\n-------"YEL"TABULA RECTA"RESET"-------\n");
    for(i = 0; i < 26; i++){
        for(j = 0; j < 26; j++){
            printf("%c", tabula_recta[i][j]);
        }
        printf("\n");
    }

    printf("\n------------------ "GREEN"VIGENERE'S ENCRYPTION"RESET" ------------------\n");
    for(i = 0; i < textsize; i++){
        row = (int)key[i] - 65;
        col = (int)plaintext[i] - 65;
        printf("Column[%d] \t|\t Row[%d]\n", col, row);
        finaltext[i] = (int)tabula_recta[row][col];
    }

    printf("\nCiphertext = %s\n", finaltext);
    return finaltext;
}