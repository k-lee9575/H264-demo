#include "pch.h"
#include "NALUnit.h"


CNALUnit::CNALUnit(uint8_t *pnalUnit, uint32_t nalUnitLength)
{
	m_pNalUnit = pnalUnit;
}


CNALUnit::~CNALUnit()
{
}

void CNALUnit::parse_nal_unit()
{
	m_nal_ref_idc = (m_pNalUnit[0] & 0x60) >> 5;
	m_nalType = (nal_unit_type)(m_pNalUnit[0] & 0x1f);
	m_pNalUnit++;
	m_nalUnitLength--;
	cout << "NAL Unit Type: " << m_nalType << endl;
	switch (m_nalType)
	{
	case NOT_DEFINED_1:
		break;
	case SLICE_LAYER_WITHOUT_PARTITIONING_RBSP_NIDR:
		break;
	case SLICE_DATA_PARTITION_A_LAYER_RBSP:
		break;
	case SLICE_DATA_PARTITION_B_LAYER_RBSP:
		break;
	case SLICE_DATA_PARTITION_C_LAYER_RBSP:
		break;
	case SLICE_LAYER_WITHOUT_PARTITIONING_RBSP_IDR:
		break;
	case SEI_RBSP:
		break;
	case SEQ_PARAMETER_SET_RBSP:
		Parse_as_seq_param_set();
		Seq_Param_Set_Info();
		break;
	case PIC_PARAMETER_SET_RBSP:
		Parse_as_pic_param_set();
		Pic_Param_Set_Info();
		break;
	case ACCESS_UNIT_DELIMITER_RBSP:
		break;
	case END_OF_SEQ_RBSP:
		break;
	case END_OF_STREAM_RBSP:
		break;
	case FILLER_DATA_RBSP:
		break;
	case SEQ_PARAMETER_SET_EXTENSION_RBSP:
		break;
	case RESERVE_1:
		break;
	case RESERVE_2:
		break;
	case RESERVE_3:
		break;
	case RESERVE_4:
		break;
	case RESERVE_5:
		break;
	case SLICE_LAYER_WITHOUT_PARTITIONING_RBSP:
		break;
	case RESERVE_6:
		break;
	case RESERVE_7:
		break;
	case RESERVE_8:
		break;
	case RESERVE_9:
		break;
	case NOT_DEFINED_2:
		break;
	case NOT_DEFINED_3:
		break;
	case NOT_DEFINED_4:
		break;
	case NOT_DEFINED_5:
		break;
	case NOT_DEFINED_6:
		break;
	case NOT_DEFINED_7:
		break;
	case NOT_DEFINED_8:
		break;
	case NOT_DEFINED_9:
		break;
	default:
		break;
	}

}

int CNALUnit::Parse_as_seq_param_set()
{
	uint8_t bitPosition = 0;
	uint32_t bytePosition = 3;

	m_SPS_DATA.profile_idc = m_pNalUnit[0];
	m_SPS_DATA.level_idc = m_pNalUnit[2];
	m_SPS_DATA.seq_parameter_set_id = Get_uev_code_num(m_pNalUnit, bytePosition, bitPosition);
	if (m_SPS_DATA.profile_idc == 100 ||
		m_SPS_DATA.profile_idc == 110 ||
		m_SPS_DATA.profile_idc == 122 ||
		m_SPS_DATA.profile_idc == 244 ||
		m_SPS_DATA.profile_idc == 44 ||
		m_SPS_DATA.profile_idc == 83 ||
		m_SPS_DATA.profile_idc == 86 ||
		m_SPS_DATA.profile_idc == 118 ||
		m_SPS_DATA.profile_idc == 128)
	{
		m_SPS_DATA.chroma_format_idc = Get_uev_code_num(m_pNalUnit, bytePosition, bitPosition);
		if (m_SPS_DATA.chroma_format_idc == 3)
		{
			m_SPS_DATA.separate_colour_plane_flag = Get_bit_at_position(m_pNalUnit, bytePosition, bitPosition);
		}
		m_SPS_DATA.bit_depth_luma = Get_uev_code_num(m_pNalUnit, bytePosition, bitPosition) + 8;
		m_SPS_DATA.bit_depth_chroma = Get_uev_code_num(m_pNalUnit, bytePosition, bitPosition) + 8;
		m_SPS_DATA.qpprime_y_zero_transform_bypass_flag = Get_bit_at_position(m_pNalUnit, bytePosition, bitPosition);

		m_SPS_DATA.seq_scaling_matrix_present_flag = Get_bit_at_position(m_pNalUnit, bytePosition, bitPosition);
		if (m_SPS_DATA.seq_scaling_matrix_present_flag)
		{
			return -1;//未支持
		}
	}
	m_SPS_DATA.log2_max_frame_num = Get_uev_code_num(m_pNalUnit, bytePosition, bitPosition) + 4;
	m_SPS_DATA.pic_order_cnt_type = Get_uev_code_num(m_pNalUnit, bytePosition, bitPosition);
	if (m_SPS_DATA.pic_order_cnt_type == 0)
	{
		m_SPS_DATA.log2_max_pic_order_cnt = Get_uev_code_num(m_pNalUnit, bytePosition, bitPosition) + 4;
	}
	else //if (m_SPS_DATA.pic_order_cnt_type == 1)
	{
		return -1;//未支持
	}
	m_SPS_DATA.max_num_ref_frames = Get_uev_code_num(m_pNalUnit, bytePosition, bitPosition);
	m_SPS_DATA.gaps_in_frame_num_value_allowed_flag = Get_bit_at_position(m_pNalUnit, bytePosition, bitPosition);

	m_SPS_DATA.pic_width_in_mbs = Get_uev_code_num(m_pNalUnit, bytePosition, bitPosition) + 1;
	m_SPS_DATA.pic_height_in_map_units = Get_uev_code_num(m_pNalUnit, bytePosition, bitPosition) + 1;
	m_SPS_DATA.frame_mbs_only_flag = Get_bit_at_position(m_pNalUnit, bytePosition, bitPosition);
	if (!m_SPS_DATA.frame_mbs_only_flag)
	{
		m_SPS_DATA.mb_adaptive_frame_field_flag = Get_bit_at_position(m_pNalUnit, bytePosition, bitPosition);
	}

	m_SPS_DATA.direct_8x8_inference_flag = Get_bit_at_position(m_pNalUnit, bytePosition, bitPosition);
	m_SPS_DATA.frame_cropping_flag = Get_bit_at_position(m_pNalUnit, bytePosition, bitPosition);
	if (m_SPS_DATA.frame_cropping_flag)
	{
		for (int i = 0; i < 4; i++)
		{
			m_SPS_DATA.frame_crop_offset[i] = Get_uev_code_num(m_pNalUnit, bytePosition, bitPosition);
		}
	}

	m_SPS_DATA.vui_parameters_present_flag = Get_bit_at_position(m_pNalUnit, bytePosition, bitPosition);
	m_SPS_DATA.pic_height_in_mbs = m_SPS_DATA.frame_mbs_only_flag ? m_SPS_DATA.pic_height_in_map_units : m_SPS_DATA.pic_height_in_map_units * 2;

	return 0;
}

int CNALUnit::Parse_as_pic_param_set()
{
	uint8_t bitPosition = 0;
	uint32_t bytePosition = 0;
	m_PPS_DATA.pic_parameter_set_id = Get_uev_code_num(m_pNalUnit, bytePosition, bitPosition);
	m_PPS_DATA.seq_parameter_set_id = Get_uev_code_num(m_pNalUnit, bytePosition, bitPosition);
	m_PPS_DATA.entropy_coding_mode_flag = Get_bit_at_position(m_pNalUnit, bytePosition, bitPosition);
	m_PPS_DATA.pic_order_present_flag = Get_bit_at_position(m_pNalUnit, bytePosition, bitPosition);
	m_PPS_DATA.num_slice_groups = Get_sev_code_num(m_pNalUnit, bytePosition, bitPosition) + 1;
	if (m_PPS_DATA.num_slice_groups > 1)
	{
		return -1;
	}

	m_PPS_DATA.num_ref_idx_10_active = Get_uev_code_num(m_pNalUnit, bytePosition, bitPosition) + 1;
	m_PPS_DATA.num_ref_idx_11_active = Get_uev_code_num(m_pNalUnit, bytePosition, bitPosition) + 1;
	m_PPS_DATA.weighed_pred_flag = Get_bit_at_position(m_pNalUnit, bytePosition, bitPosition);
	m_PPS_DATA.weighted_bipred_idc = Get_uint_code_num(m_pNalUnit, bytePosition, bitPosition, 2);
	m_PPS_DATA.pic_init_qp = Get_sev_code_num(m_pNalUnit, bytePosition, bitPosition) + 26;
	m_PPS_DATA.pic_init_qs = Get_sev_code_num(m_pNalUnit, bytePosition, bitPosition) + 26;
	m_PPS_DATA.chroma_qp_index_offset = Get_sev_code_num(m_pNalUnit, bytePosition, bitPosition);

	m_PPS_DATA.deblocking_filter_control_present_flag = Get_bit_at_position(m_pNalUnit, bytePosition, bitPosition);
	m_PPS_DATA.constrained_intra_pred_flag = Get_bit_at_position(m_pNalUnit, bytePosition, bitPosition);
	m_PPS_DATA.redundant_pic_cnt_present_flag = Get_bit_at_position(m_pNalUnit, bytePosition, bitPosition);

}

void CNALUnit::Seq_Param_Set_Info()
{
	cout << "==========Sequence Paramater Set==========" << endl;
	cout << "Profile: " << to_string(m_SPS_DATA.profile_idc) << endl;
	cout << "Level: " << to_string(m_SPS_DATA.level_idc) << endl;
	cout << "SPS ID: " << to_string(m_SPS_DATA.seq_parameter_set_id) << endl;
	if (m_SPS_DATA.profile_idc == 100 || 
		m_SPS_DATA.profile_idc == 110 || 
		m_SPS_DATA.profile_idc == 122 || 
		m_SPS_DATA.profile_idc == 244 || 
		m_SPS_DATA.profile_idc == 44 ||
		m_SPS_DATA.profile_idc == 83 || 
		m_SPS_DATA.profile_idc == 86 || 
		m_SPS_DATA.profile_idc == 118 || 
		m_SPS_DATA.profile_idc == 128)
	{
		cout << "chroma_format_idc: " << to_string(m_SPS_DATA.chroma_format_idc) << endl;
		if (m_SPS_DATA.chroma_format_idc == 3)
		{
			cout << "separate_colour_plane_flag: " << to_string(m_SPS_DATA.separate_colour_plane_flag) << endl;
		}
		cout << "bit_depth_luma: " << to_string(m_SPS_DATA.bit_depth_luma) << endl;
		cout << "bit_depth_chroma: " << to_string(m_SPS_DATA.bit_depth_chroma) << endl;
		cout << "qpprime_y_zero_transform_bypass_flag: " << to_string(m_SPS_DATA.qpprime_y_zero_transform_bypass_flag) << endl;
		cout << "seq_scaling_matrix_present_flag: " << to_string(m_SPS_DATA.seq_scaling_matrix_present_flag) << endl;
	}
	cout << "log2_max_frame_num: " << to_string(m_SPS_DATA.log2_max_frame_num) << endl;
	cout << "pic_order_cnt_type: " << to_string(m_SPS_DATA.pic_order_cnt_type) << endl;
	if (m_SPS_DATA.pic_order_cnt_type == 0)
	{
		cout << "log2_max_poc_cnt: " << to_string(m_SPS_DATA.log2_max_pic_order_cnt) << endl;
	}
	cout << "log2_max_num_ref_frames: " << to_string(m_SPS_DATA.max_num_ref_frames) << endl;
	cout << "gaps_in_frame_num_value_allowed_flag: " << to_string(m_SPS_DATA.gaps_in_frame_num_value_allowed_flag) << endl;
	cout << "pic_width_in_mbs_minus1: " << to_string(m_SPS_DATA.pic_width_in_mbs) << endl;
	cout << "pic_height_in_map_units_minus1: " << to_string(m_SPS_DATA.pic_height_in_map_units) << endl;
	cout << "(picture resolution: " << to_string(m_SPS_DATA.pic_width_in_mbs * 16) << " x " << to_string(m_SPS_DATA.pic_height_in_mbs * 16) << ")" << endl;
	cout << "frame_mbs_only_flag: " << to_string(m_SPS_DATA.frame_mbs_only_flag) << endl;
	if (!m_SPS_DATA.frame_mbs_only_flag)
	{
		cout << "mb_adaptive_frame_field_flag: " << to_string(m_SPS_DATA.mb_adaptive_frame_field_flag) << endl;
	}
	cout << "direct_8x8_inference_flag: " << to_string(m_SPS_DATA.direct_8x8_inference_flag) << endl;
	cout << "frame_cropping_flag: " << to_string(m_SPS_DATA.frame_cropping_flag) << endl;
	if (m_SPS_DATA.frame_cropping_flag)
	{
		cout << "frame_crop_left_offset: " << to_string(m_SPS_DATA.frame_crop_offset[0]) << endl;
		cout << "frame_crop_right_offset: " << to_string(m_SPS_DATA.frame_crop_offset[1]) << endl;
		cout << "frame_crop_top_offset: " << to_string(m_SPS_DATA.frame_crop_offset[2]) << endl;
		cout << "frame_crop_bottum_offset: " << to_string(m_SPS_DATA.frame_crop_offset[3]) << endl;
	}
	cout << "vui_parameters_present_flag: " << to_string(m_SPS_DATA.vui_parameters_present_flag) << endl;
	cout << "==========================================" << endl;
	cout.flush();
}

void CNALUnit::Pic_Param_Set_Info()
{
	cout << "==========Picture Paramater Set==========" << endl;
	cout << "pic_parameter_set_id: " << to_string(m_PPS_DATA.pic_parameter_set_id) << endl;
	cout << "seq_parameter_set_id: " << to_string(m_PPS_DATA.seq_parameter_set_id) << endl;
	cout << "entropy_coding_mode_flag: " << to_string(m_PPS_DATA.entropy_coding_mode_flag) << endl;
	cout << "bottom_field_pic_order_in_frame_present_flag: " << to_string(m_PPS_DATA.pic_order_present_flag) << endl;
	cout << "num_slice_groups: " << to_string(m_PPS_DATA.num_slice_groups) << endl;
	if (m_PPS_DATA.num_slice_groups == 1)
	{
		cout << "num_ref_idx_l0_default_active: " << to_string(m_PPS_DATA.num_ref_idx_10_active) << endl;
		cout << "num_ref_idx_l1_default_active: " << to_string(m_PPS_DATA.num_ref_idx_11_active) << endl;
		cout << "weighted_pred_flag: " << to_string(m_PPS_DATA.weighed_pred_flag) << endl;
		cout << "weighted_bipred_idc: " << to_string(m_PPS_DATA.weighted_bipred_idc) << endl;
		cout << "pic_init_qp: " << to_string(m_PPS_DATA.pic_init_qp) << endl;
		cout << "pic_init_qs: " << to_string(m_PPS_DATA.pic_init_qs) << endl;
		cout << "chroma_qp_index_offset :" << to_string(m_PPS_DATA.chroma_qp_index_offset) << endl;
		cout << "deblocking_filter_control_present_flag: " << to_string(m_PPS_DATA.deblocking_filter_control_present_flag) << endl;
		cout << "constrained_intra_pred_flag: " << to_string(m_PPS_DATA.constrained_intra_pred_flag) << endl;
		cout << "redundant_pic_cnt_present_flag: " << to_string(m_PPS_DATA.redundant_pic_cnt_present_flag) << endl;
	}
	cout << "==========================================" << endl;
	cout.flush();
}
