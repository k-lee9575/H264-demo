#pragma once
#include "pch.h"
class CStreamFile
{
public:
	CStreamFile(const string &strFilename);
	~CStreamFile();

	bool read_nalunit(vector<uint8_t> &v);

private:
	enum FileError
	{
		OPEN_FILE_FAILED_ERROR,
	};


	enum read_nalunit_status
	{
		READ_NALUNIT_S0,
		READ_NALUNIT_S1,
		READ_NALUNIT_S2,
		READ_NALUNIT_S3,
		READ_NALUNIT_S4,
	};

	
	bool automachine(read_nalunit_status &p, read_nalunit_status &n, uint8_t c, vector<uint8_t> &v);

	void fileInfo();
	void fileError(FileError e);

	FILE *m_pInputFile;
	string m_strFilename;
};

