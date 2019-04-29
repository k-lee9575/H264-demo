#include "pch.h"
#include "stream.h"
#include "NALUnit.h"



CStreamFile::CStreamFile(const string &strFilename)
{
	m_strFilename = strFilename;
	
	fileInfo();

	fopen_s(&m_pInputFile, m_strFilename.c_str(), "rb");
	if (m_pInputFile == NULL)
	{
		fileError(OPEN_FILE_FAILED_ERROR);
	}
}

CStreamFile::~CStreamFile()
{
	if (m_pInputFile)
	{
		fclose(m_pInputFile);
		m_pInputFile = NULL;
	}
}

void CStreamFile::parse_bitstream()
{
	vector<uint8_t> v_nalBytes;
	bool bRet;
	do
	{
		bRet = read_nalunit(v_nalBytes);
		if (v_nalBytes.size())
		{
			CNALUnit NalUnit(&v_nalBytes[0], v_nalBytes.size());
			NalUnit.parse_nal_unit();
		}
	
		//
		//for (auto it = v_nalBytes.begin(); it != v_nalBytes.end(); it++)
		//{
		//	printf("%02x ", *it);
		//}
		//printf("\n");

	} while (bRet);
}

void CStreamFile::fileInfo()
{
	cout << "Filenmae:" << m_strFilename << endl;
}

void CStreamFile::fileError(FileError e)
{
}


bool CStreamFile::read_nalunit(vector<uint8_t> &v)
{
	v.clear();
	read_nalunit_status p = READ_NALUNIT_S0;
	read_nalunit_status n = READ_NALUNIT_S0;
	int c;
	while ((c = fgetc(m_pInputFile)) != EOF)
	{
		if (!automachine(p, n, c, v))
		{
			return true;
		}
	}
	return false;
}


bool CStreamFile::automachine(read_nalunit_status &p, read_nalunit_status &n, uint8_t c, vector<uint8_t> &v)
{
	p = n;
	switch (n)
	{
	case READ_NALUNIT_S0:
		if (c == 0)
		{
			n = READ_NALUNIT_S1;
		}
		else
		{
			v.push_back(c);//状态不变
		}
		break;
	case READ_NALUNIT_S1:
		if (c == 0)
		{
			n = READ_NALUNIT_S2;
		}
		else
		{
			n = READ_NALUNIT_S0;
			v.push_back(0);
			v.push_back(c);
		}
		break;
	case READ_NALUNIT_S2:
		if (c == 0)
		{
			n = READ_NALUNIT_S3;
		}
		else if (c == 1)
		{
			n = READ_NALUNIT_S4;
			return false;
		}
		else
		{
			n = READ_NALUNIT_S0;
			v.push_back(0);
			v.push_back(0);
			if (c != 3)
			{
				v.push_back(c);
			}
		}
		break;
	case READ_NALUNIT_S3:
		if (c == 0)
		{
			v.push_back(c);//状态不变
		}
		else if (c == 1)
		{
			n = READ_NALUNIT_S4;
			return false;
		}
		else
		{
			n = READ_NALUNIT_S0;
			v.push_back(0);
			v.push_back(0);
			v.push_back(0);
			if (c != 3)
			{
				v.push_back(c);
			}
		}
		break;
	case READ_NALUNIT_S4:
		if (c == 0)
		{
			n = READ_NALUNIT_S1;
		}
		else
		{
			n = READ_NALUNIT_S0;
			v.push_back(c);
		}
		break;
	default:
		break;
	}
	return true;
}
