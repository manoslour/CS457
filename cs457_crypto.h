/*************************************************************
 * @file   cs457_crypto.h                                    *
 * @author Lourakis Manos <csd3153@csd.uoc.gr>  	         *
 *                                                    	     *
 * @brief  Library file for the needs of CS457 Assignment 1  *
 ************************************************************/

#ifndef _CS457_CRYPTO_H_
#define _CS457_CRYPTO_H_

#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define GREEN "\x1B[32m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"
#define BUFFER_SIZE 1024

uint8_t* generateKey(long int size);
uint8_t* removeIllegal(uint8_t *plaintext);
uint8_t* generateVigKey(uint8_t *keyword, long int size);

// One-Time Pad (OTP)
uint8_t* otp_encrypt(uint8_t *plaintext, uint8_t *key);
uint8_t* otp_decrypt(uint8_t *ciphertext, uint8_t *key);

// Caesar's cipher
uint8_t* caesar_encrypt(uint8_t *plaintext, unsigned short N, int flag);
uint8_t* caesar_decrypt(uint8_t *ciphertext, unsigned short N);

// Spartan's cipher - Scytale
uint8_t* spartan_encrypt(uint8_t *plaintext, unsigned short circ, unsigned short len);
uint8_t* spartan_decrypt(uint8_t *ciphertext, unsigned short circ, unsigned short len);

// Vigenere's cipher
uint8_t* vigenere_encrypt(uint8_t *plaintext, uint8_t *key);
uint8_t* vigenere_decrypt(uint8_t *ciphertext, uint8_t *key);

#endif