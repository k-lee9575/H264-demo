#pragma once
class CNALUnit
{
public:
	CNALUnit(uint8_t *pnalUnit, uint32_t nalUnitLength);
	virtual ~CNALUnit();


	void parse_nal_unit();

private:
	int Parse_as_seq_param_set();
	int Parse_as_pic_param_set();
	void Seq_Param_Set_Info();
	void Pic_Param_Set_Info();


	uint8_t *m_pNalUnit;
	uint32_t m_nalUnitLength;
	uint8_t m_nal_ref_idc;
	nal_unit_type m_nalType;

	SPS_DATA m_SPS_DATA;
	PPS_DATA m_PPS_DATA;
};

