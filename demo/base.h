#pragma once

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

enum nal_unit_type
{
	NOT_DEFINED_1,									//δָ��
	SLICE_LAYER_WITHOUT_PARTITIONING_RBSP_NIDR,		//һ����IDEͼ��ı�������
	SLICE_DATA_PARTITION_A_LAYER_RBSP,				//�����������ݷָ�� A
	SLICE_DATA_PARTITION_B_LAYER_RBSP,				//�����������ݷָ�� B
	SLICE_DATA_PARTITION_C_LAYER_RBSP,				//�����������ݷָ�� C
	SLICE_LAYER_WITHOUT_PARTITIONING_RBSP_IDR,		//IDRͼ��ı�������
	SEI_RBSP,										//������ǿ��Ϣ��SEI��
	SEQ_PARAMETER_SET_RBSP,							//���в�����
	PIC_PARAMETER_SET_RBSP,							//ͼ�������
	ACCESS_UNIT_DELIMITER_RBSP,						//���ʵ�Ԫ�ָ���
	END_OF_SEQ_RBSP,								//���н�β
	END_OF_STREAM_RBSP,								//����β
	FILLER_DATA_RBSP,								//�������
	SEQ_PARAMETER_SET_EXTENSION_RBSP,				//���в�������չ
	RESERVE_1,										//����
	RESERVE_2,										//����
	RESERVE_3,										//����
	RESERVE_4,										//����
	RESERVE_5,										//����
	SLICE_LAYER_WITHOUT_PARTITIONING_RBSP,			//δ�ָ�ĸ�������ͼ��ı�������
	RESERVE_6,										//����
	RESERVE_7,										//����
	RESERVE_8,										//����
	RESERVE_9,										//����
	NOT_DEFINED_2,									//δָ��
	NOT_DEFINED_3,									//δָ��
	NOT_DEFINED_4,									//δָ��
	NOT_DEFINED_5,									//δָ��
	NOT_DEFINED_6,									//δָ��
	NOT_DEFINED_7,									//δָ��
	NOT_DEFINED_8,									//δָ��
	NOT_DEFINED_9,									//δָ��
};


typedef struct seq_parameter_set_data
{
	uint8_t profile_idc;
	uint8_t set_flag_00;
	uint8_t level_idc;
	uint8_t seq_parameter_set_id;

	uint8_t chroma_format_idc;
	bool separate_colour_plane_flag;
	uint8_t bit_depth_luma;
	uint8_t bit_depth_chroma;
	bool qpprime_y_zero_transform_bypass_flag;
	bool seq_scaling_matrix_present_flag;

	uint32_t log2_max_frame_num;
	uint32_t pic_order_cnt_type;
	uint32_t log2_max_pic_order_cnt;
	bool delta_pic_order_always_zero_flag;
	int32_t offset_for_non_ref_pic;
	int32_t offset_for_top_to_bottom_field;
	uint8_t max_num_ref_frames;
	bool gaps_in_frame_num_value_allowed_flag;


	uint16_t pic_width_in_mbs;
	uint16_t pic_height_in_map_units;
	uint16_t pic_height_in_mbs;	// not defined in spec, derived...
	bool frame_mbs_only_flag;
	bool mb_adaptive_frame_field_flag;
	bool direct_8x8_inference_flag;
	bool frame_cropping_flag;
	uint16_t frame_crop_offset[4];
	bool vui_parameters_present_flag;

	seq_parameter_set_data() {

		profile_idc = 0;
		set_flag_00 = 0;
		level_idc = 0;
		seq_parameter_set_id = 0;

		chroma_format_idc = 0;
		separate_colour_plane_flag = false;
		bit_depth_luma = 0;
		bit_depth_chroma = 0;
		qpprime_y_zero_transform_bypass_flag = false;
		seq_scaling_matrix_present_flag = false;

		log2_max_frame_num = 0;
		pic_order_cnt_type = 0;
		log2_max_pic_order_cnt = 0;
		delta_pic_order_always_zero_flag = false;
		offset_for_non_ref_pic = 0;
		offset_for_top_to_bottom_field = 0;
		max_num_ref_frames = 0;
		gaps_in_frame_num_value_allowed_flag = false;

		pic_width_in_mbs = 0;
		pic_height_in_map_units = 0;
		pic_height_in_mbs = 0;	// not defined in spec, derived...
		frame_mbs_only_flag = false;
		mb_adaptive_frame_field_flag = false;
		direct_8x8_inference_flag = false;
		frame_cropping_flag = false;
		memset(frame_crop_offset, 0, sizeof(frame_crop_offset));
		vui_parameters_present_flag = false;
	};
	~seq_parameter_set_data() {
	};
} SPS_DATA;