#pragma once
#include "pch.h"
class CStreamFile
{
public:
	CStreamFile(const string &strFilename);
	~CStreamFile();
	void parse_bitstream();
	

private:
	bool read_nalunit(vector<uint8_t> &v);//��ȡʱ�Ѿ���ebsp ת��sodb �����ٴ�ת��
	
	bool automachine(read_nalunit_status &p, read_nalunit_status &n, uint8_t c, vector<uint8_t> &v);

	void fileInfo();
	void fileError(FileError e);

	FILE *m_pInputFile;
	string m_strFilename;
};

