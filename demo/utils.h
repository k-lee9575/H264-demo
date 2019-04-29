#pragma once
#ifndef _UTILS_H_
#define _UTILS_H_

//********************Parsing Bitstream**********************
// Get bool value from bit position..
int Get_bit_at_position(uint8_t *buf, uint32_t &bytePosition, uint8_t &bitPosition);

// Parse bit stream using Expo-Columb coding
int Get_uev_code_num(uint8_t *buf, uint32_t &bytePosition, uint8_t &bitPosition);

// Parse bit stream using signed-Expo-Columb coding
int Get_sev_code_num(uint8_t *buf, uint32_t &bytePosition, uint8_t &bitPosition);

// Parse bit stream as unsigned int bits
int Get_uint_code_num(uint8_t *buf, uint32_t &bytePosition, uint8_t &bitPosition, uint8_t length);
int Peek_uint_code_num(uint8_t *buf, uint32_t bytePosition, uint8_t bitPosition, uint8_t length);

// Parse bit stream as me(coded_block_pattern)
int Get_me_code_num(uint8_t *buf, uint32_t &bytePosition, uint8_t &bitPosition, uint8_t mode);
//***********************************************************

int Extract_single_nal_unit(const char* fileName, uint8_t *nalBuf, uint32_t nalLen);

int block_index_to_position(uint8_t blkIdx, uint8_t &block_pos_row, uint8_t &block_pos_column);
uint8_t position_to_block_index(uint8_t block_pos_row, uint8_t block_pos_column);
#endif