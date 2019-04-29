#include "pch.h"

int Get_bit_at_position(uint8_t * buf, uint32_t & bytePosition, uint8_t & bitPosition)
{

	uint8_t val = (buf[bytePosition]>>(7-bitPosition++)) & 1;
	if (bitPosition > 7)
	{
		bytePosition++;
		bitPosition = 0;
	}
	return val;
}

int Get_uev_code_num(uint8_t *buf, uint32_t &bytePosition, uint8_t &bitPosition)
{
	uint8_t val = 0;
	int prefix0Count = 0;
	int prefix = 0;
	int surfix = 0;

	while (true)
	{
		val = Get_bit_at_position(buf, bytePosition, bitPosition);
		if (val == 0)
		{
			prefix0Count++;
		}
		else
		{
			break;
		}
	}
	prefix = (1 << prefix0Count) - 1;
	for (int i = 0; i < prefix0Count; i++)
	{
		val = Get_bit_at_position(buf, bytePosition, bitPosition);
		surfix <<= 1;
		surfix += val;
	}
	return prefix + surfix;
}

int Get_sev_code_num(uint8_t *buf, uint32_t &bytePosition, uint8_t &bitPosition)
{
	int uev = Get_uev_code_num(buf, bytePosition, bitPosition);
	int sign = (uev % 2) ? 1 : -1;
	return sign * ((uev + 1) >> 1);
}

int Get_uint_code_num(uint8_t *buf, uint32_t &bytePosition, uint8_t &bitPosition, uint8_t length)
{
	uint8_t val = 0;
	for (int i = 0; i < length; i++)
	{
		val <<= 1;
		val += Get_bit_at_position(buf, bytePosition, bitPosition);
	}
	return val;
}

int Peek_uint_code_num(uint8_t *buf, uint32_t bytePosition, uint8_t bitPosition, uint8_t length)
{
	return 0;
}

int Get_me_code_num(uint8_t *buf, uint32_t &bytePosition, uint8_t &bitPosition, uint8_t mode)
{
	return 0;
}

int Extract_single_nal_unit(const char* fileName, uint8_t *nalBuf, uint32_t nalLen)
{
	return 0;
}

int block_index_to_position(uint8_t blkIdx, uint8_t &block_pos_row, uint8_t &block_pos_column)
{
	return 0;
}

uint8_t position_to_block_index(uint8_t block_pos_row, uint8_t block_pos_column)
{
	return 0;
}
