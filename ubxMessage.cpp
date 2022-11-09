//
// Created by Cezeri Stajyer on 19.08.2021.
//

#include "helperFunctions.h"

void ubxSetterFunctions::set_message_type_28(std::string data, SbasNavData *satll, uint8_t svId) {

    satll->msg[(int)svId-120].messageType28.IODP = std::bitset<2>(data.substr(0, 2)).to_ulong();

    for (int i = 0; i < 2; ++i) {
        satll->msg[(int)svId-120].messageType28.type_28[i].PRN_mask_number = std::bitset<6>(data.substr(2 + (i * 105), 6)).to_ulong();
        satll->msg[(int)svId-120].messageType28.type_28[i].Scale_exponent  = std::bitset<3>(data.substr(8 + (i * 105), 3)).to_ulong();
        satll->msg[(int)svId-120].messageType28.type_28[i].E1_1            = std::bitset<9>(data.substr(11 + (i * 105), 9)).to_ulong();
        satll->msg[(int)svId-120].messageType28.type_28[i].E2_2            = std::bitset<9>(data.substr(20 + (i * 105), 9)).to_ulong();
        satll->msg[(int)svId-120].messageType28.type_28[i].E3_3            = std::bitset<9>(data.substr(29 + (i * 105), 9)).to_ulong();
        satll->msg[(int)svId-120].messageType28.type_28[i].E4_4            = std::bitset<9>(data.substr(38 + (i * 105), 9)).to_ulong();
        satll->msg[(int)svId-120].messageType28.type_28[i].E1_2            = sbasHelperFunctions::sign_check(std::bitset<10>(data.substr(47 + (i * 105), 10)).to_string(),10);
        satll->msg[(int)svId-120].messageType28.type_28[i].E1_3            = sbasHelperFunctions::sign_check(std::bitset<10>(data.substr(57 + (i * 105), 10)).to_string(),10);
        satll->msg[(int)svId-120].messageType28.type_28[i].E1_4            = sbasHelperFunctions::sign_check(std::bitset<10>(data.substr(67 + (i * 105), 10)).to_string(),10);
        satll->msg[(int)svId-120].messageType28.type_28[i].E2_3            = sbasHelperFunctions::sign_check(std::bitset<10>(data.substr(77 + (i * 105), 10)).to_string(),10);
        satll->msg[(int)svId-120].messageType28.type_28[i].E2_4            = sbasHelperFunctions::sign_check(std::bitset<10>(data.substr(87 + (i * 105), 10)).to_string(),10);
        satll->msg[(int)svId-120].messageType28.type_28[i].E3_4            = sbasHelperFunctions::sign_check(std::bitset<10>(data.substr(97 + (i * 105), 10)).to_string(),10);
    }
}

void ubxSetterFunctions::set_message_type_27(std::string data, SbasNavData *satll, uint8_t svId) {

    satll->msg[(int)svId-120].messageType27.IODS                         = std::bitset<3>(data.substr(0, 3)).to_ulong();
    satll->msg[(int)svId-120].messageType27.Number_of_service_messages   = std::bitset<3>(data.substr(3, 3)).to_ulong() + 1;
    satll->msg[(int)svId-120].messageType27.Service_message_number       = std::bitset<3>(data.substr(6, 3)).to_ulong() + 1;
    satll->msg[(int)svId-120].messageType27.Number_of_regions            = std::bitset<3>(data.substr(9, 3)).to_ulong();
    satll->msg[(int)svId-120].messageType27.Priority_code                = std::bitset<2>(data.substr(12, 2)).to_ulong();
    satll->msg[(int)svId-120].messageType27.UDRE_indicator_inside        = std::bitset<4>(data.substr(14, 4)).to_ulong();
    satll->msg[(int)svId-120].messageType27.UDRE_indicator_outside       = std::bitset<4>(data.substr(18, 4)).to_ulong();

    for (int i = 0; i < 5; ++i) {
        satll->msg[(int)svId-120].messageType27.regions[i].Coordinate_1_latitude  = sbasHelperFunctions::sign_check(std::bitset<8>(data.substr(22 + (i * 34), 8)).to_string(),8);
        satll->msg[(int)svId-120].messageType27.regions[i].Coordinate_1_longitude = sbasHelperFunctions::sign_check(std::bitset<9>(data.substr(30 + (i * 34), 9)).to_string(),9);
        satll->msg[(int)svId-120].messageType27.regions[i].Coordinate_2_latitude  = sbasHelperFunctions::sign_check(std::bitset<8>(data.substr(39 + (i * 34), 8)).to_string(),8);
        satll->msg[(int)svId-120].messageType27.regions[i].Coordinate_2_longitude = sbasHelperFunctions::sign_check(std::bitset<9>(data.substr(47 + (i * 34), 9)).to_string(),9);
    }
    satll->msg[(int)svId-120].messageType27.Region_shape  = std::bitset<1>(data.substr(196, 1)).to_ulong();
    satll->msg[(int)svId-120].messageType27.spare         = (data.substr(197, 15));
}

void ubxSetterFunctions::set_message_type_26(std::string data, SbasNavData *satll, uint8_t svId) {

    satll->msg[(int)svId-120].messageType26.IGP_band_identifier   = std::bitset<4>(data.substr(0, 4)).to_ulong();
    satll->msg[(int)svId-120].messageType26.IGP_block_identifier  = std::bitset<4>(data.substr(4, 4)).to_ulong();

    for (int i = 0; i < 15; ++i) {
        satll->msg[(int)svId-120].messageType26.grid_point[i].IGP_vertical_delay_estimate = std::bitset<9>(data.substr(8 + (i * 13), 9)).to_ulong() * 0.125;
        satll->msg[(int)svId-120].messageType26.grid_point[i].GIVEI_i                     = std::bitset<4>(data.substr(17 + (i * 13), 4)).to_ulong();
    }
    satll->msg[(int)svId-120].messageType26.IODI_k        = std::bitset<2>(data.substr(203, 2)).to_ulong();
    satll->msg[(int)svId-120].messageType26.spare         = (data.substr(205, 7));

    /*int i,j,block,delay,give,band=satll->msg[(int)svId-120].messageType26.IGP_band_identifier;

    if (band>MAXBAND||sbsion[band].iodi!=(int)satll->msg[(int)svId-120].messageType26.IODI_k) return ;

    block=satll->msg[(int)svId-120].messageType26.IGP_block_identifier;

    for (i=0;i<15;i++) {
        if ((j=block*15+i)>=sbsion[band].nigp) continue;
        give=(int)satll->msg[(int)svId-120].messageType26.grid_point[i].GIVEI_i;
        delay=(int)satll->msg[(int)svId-120].messageType26.grid_point[i].IGP_vertical_delay_estimate;
        sbsion[band].igp[j].t0=gpst2time(msg->week,msg->tow);
        sbsion[band].igp[j].delay=delay==0x1FF?0.0f:delay*0.125f;
        sbsion[band].igp[j].give=give+1;

        if (sbsion[band].igp[j].give>=16) {
            sbsion[band].igp[j].give=0;
        }
    }*/

}

void ubxSetterFunctions::set_message_type_25(std::string data, SbasNavData *satll, uint8_t svId) {
    
    ///(VELOCITY CODE = 0)
    satll->msg[(int)svId-120].messageType25.Velocity_Code_0                       = std::bitset<1>(data.substr(0, 1)).to_ulong();
    for (int i = 0; i < 2; ++i) {
        satll->msg[(int)svId-120].messageType25.type_25_zero[i].PRN_mask_number   = std::bitset<6>(data.substr(1 + (i * 51), 6)).to_ulong();
        satll->msg[(int)svId-120].messageType25.type_25_zero[i].IOD_i             = std::bitset<8>(data.substr(7 + (i * 51), 8)).to_ulong();
        satll->msg[(int)svId-120].messageType25.type_25_zero[i].x_i               = sbasHelperFunctions::sign_check(std::bitset<9>(data.substr(15 + (i * 51), 9)).to_string(),9) * 0.125;
        satll->msg[(int)svId-120].messageType25.type_25_zero[i].y_i               = sbasHelperFunctions::sign_check(std::bitset<9>(data.substr(24 + (i * 51), 9)).to_string(),9) * 0.125;
        satll->msg[(int)svId-120].messageType25.type_25_zero[i].z_i               = sbasHelperFunctions::sign_check(std::bitset<9>(data.substr(33 + (i * 51), 9)).to_string(),9) * 0.125;
        satll->msg[(int)svId-120].messageType25.type_25_zero[i].a_i               = sbasHelperFunctions::sign_check(std::bitset<10>(data.substr(42 + (i * 51), 10)).to_string(),10) * pow(2,-31);
    }
    satll->msg[(int)svId-120].messageType25.IODP                                  = std::bitset<2>(data.substr(103, 2)).to_ulong();
    satll->msg[(int)svId-120].messageType25.spare                                 = (data.substr(105, 1));
    ///(VELOCITY CODE = 1)
    satll->msg[(int)svId-120].messageType25.type_25_one.Velocity_Code_1   = std::bitset<1>(data.substr(106, 1)).to_ulong();
    satll->msg[(int)svId-120].messageType25.type_25_one.PRN_mask_number   = std::bitset<6>(data.substr(107, 6)).to_ulong();
    satll->msg[(int)svId-120].messageType25.type_25_one.IOD_i             = std::bitset<8>(data.substr(113, 8)).to_ulong();
    satll->msg[(int)svId-120].messageType25.type_25_one.x_i               = sbasHelperFunctions::sign_check(std::bitset<11>(data.substr(121, 11)).to_string(),11) * 0.125;
    satll->msg[(int)svId-120].messageType25.type_25_one.y_i               = sbasHelperFunctions::sign_check(std::bitset<11>(data.substr(132, 11)).to_string(),11) * 0.125;
    satll->msg[(int)svId-120].messageType25.type_25_one.z_i               = sbasHelperFunctions::sign_check(std::bitset<11>(data.substr(143, 11)).to_string(),11) * 0.125;
    satll->msg[(int)svId-120].messageType25.type_25_one.a_i_f0            = sbasHelperFunctions::sign_check(std::bitset<11>(data.substr(154, 11)).to_string(),11) * pow(2,-31);
    satll->msg[(int)svId-120].messageType25.type_25_one.v_x_i             = sbasHelperFunctions::sign_check(std::bitset<8>(data.substr(165, 8)).to_string(),8) * pow(2,-11);
    satll->msg[(int)svId-120].messageType25.type_25_one.v_y_i             = sbasHelperFunctions::sign_check(std::bitset<8>(data.substr(173, 8)).to_string(),8) * pow(2,-11);
    satll->msg[(int)svId-120].messageType25.type_25_one.v_z_i             = sbasHelperFunctions::sign_check(std::bitset<8>(data.substr(181, 8)).to_string(),8) * pow(2,-11);
    satll->msg[(int)svId-120].messageType25.type_25_one.a_i_f1            = sbasHelperFunctions::sign_check(std::bitset<8>(data.substr(189, 8)).to_string(),8) * pow(2,-39);
    satll->msg[(int)svId-120].messageType25.type_25_one.t_i_LT            = std::bitset<13>(data.substr(197, 13)).to_ulong() * 16;
    satll->msg[(int)svId-120].messageType25.type_25_one.IODP              = std::bitset<2>(data.substr(210, 2)).to_ulong();
}

void ubxSetterFunctions::set_message_type_24(std::string data, SbasNavData *satll, uint8_t svId) {

    for (int i = 0; i < 6; ++i) {
        satll->msg[(int)svId-120].messageType24.FC[i]         = sbasHelperFunctions::sign_check(std::bitset<12>(data.substr(i * 12, 12)).to_string(),12) * 0.125;
    }

    for (int i = 0; i < 6; ++i) {
        satll->msg[(int)svId-120].messageType24.UDREI[i]      = std::bitset<4>(data.substr(72 + (i * 4), 4)).to_ulong();
    }
    satll->msg[(int)svId-120].messageType24.IODP              = std::bitset<2>(data.substr(96, 2)).to_ulong();
    satll->msg[(int)svId-120].messageType24.FCTI              = std::bitset<2>(data.substr(98, 2)).to_ulong();
    satll->msg[(int)svId-120].messageType24.IODF_j            = std::bitset<2>(data.substr(100, 2)).to_ulong();
    satll->msg[(int)svId-120].messageType24.Spare             = (data.substr(102, 4));
    satll->msg[(int)svId-120].messageType24.Type_25_half_msg  = (data.substr(106, 106));
}

void ubxSetterFunctions::set_message_type_18(std::string data, SbasNavData *satll, uint8_t svId) {

    satll->msg[(int)svId-120].messageType18.Number_of_IGP_bands   = std::bitset<4>(data.substr(0, 4)).to_ulong();
    satll->msg[(int)svId-120].messageType18.IGP_band_identifier   = std::bitset<4>(data.substr(4, 4)).to_ulong();
    satll->msg[(int)svId-120].messageType18.IODI_k                = std::bitset<2>(data.substr(8, 2)).to_ulong();
    for (int i = 0; i < 201; ++i) {
        satll->msg[(int)svId-120].messageType18.IGP_mask_value[i] = std::bitset<1>(data.substr(10 + i, 1)).to_ulong();
    }
    satll->msg[(int)svId-120].messageType18.spare                 = (data.substr(211, 1));

/*    const sbsigpband_t *p;

    int i,j,n,m,band=satll->msg[(int)svId-120].messageType18.IGP_band_identifier;
    if (0<=band&&band<= 8) {
        p=igpband1[band  ];
        m=8;
    }
    else if (9<=band&&band<=10) {
        p=igpband2[band-9];
        m=5;
    }
    else{
        return;
    }

    sbsion[band].iodi=(int16_t)satll->msg[(int)svId-120].messageType18.IODI_k;

    for (i=1,n=0;i<=201;i++) {
        if (!satll->msg[(int)svId-120].messageType18.IGP_mask_value[i-1]) continue;
        for (j=0;j<m;j++) {
            if (i-1<p[j].bits||p[j].bite<i-1) continue;
            sbsion[band].igp[n].lat=band<=8?p[j].y[i-p[j].bits]:p[j].x;
            sbsion[band].igp[n++].lon=band<=8?p[j].x:p[j].y[i-p[j].bits];
            break;
        }
    }
    sbsion[band].nigp=n;*/

}

void ubxSetterFunctions::set_message_type_17(std::string data, SbasNavData *satll, uint8_t svId) {

    for (int i = 0; i < 3; ++i) {
        satll->msg[(int)svId-120].messageType17.satellites[i].reserved            = std::bitset<2>(data.substr(0 + (i * 67), 2)).to_ulong();
        satll->msg[(int)svId-120].messageType17.satellites[i].PRN_code_number     = std::bitset<8>(data.substr(2 + (i * 67), 8)).to_ulong();
        satll->msg[(int)svId-120].messageType17.satellites[i].Health_and_status   = std::bitset<8>(data.substr(10 + (i * 67), 8)).to_ulong();
        satll->msg[(int)svId-120].messageType17.satellites[i].location_X_G_A      = sbasHelperFunctions::sign_check(std::bitset<15>(data.substr(18 + (i * 67), 15)).to_string(),15) * 2600;
        satll->msg[(int)svId-120].messageType17.satellites[i].location_Y_G_A      = sbasHelperFunctions::sign_check(std::bitset<15>(data.substr(33 + (i * 67), 15)).to_string(),15) * 2600;
        satll->msg[(int)svId-120].messageType17.satellites[i].location_Z_G_A      = sbasHelperFunctions::sign_check(std::bitset<9>(data.substr(48 + (i * 67), 9)).to_string(),9) * 26000;
        satll->msg[(int)svId-120].messageType17.satellites[i].velocity_X_G_A      = sbasHelperFunctions::sign_check(std::bitset<3>(data.substr(57 + (i * 67), 3)).to_string(),3) * 10;
        satll->msg[(int)svId-120].messageType17.satellites[i].velocity_Y_G_A      = sbasHelperFunctions::sign_check(std::bitset<3>(data.substr(60 + (i * 67), 3)).to_string(),3) * 10;
        satll->msg[(int)svId-120].messageType17.satellites[i].velocity_Z_G_A      = sbasHelperFunctions::sign_check(std::bitset<4>(data.substr(63 + (i * 67), 4)).to_string(),4) * 60;

        satll->health[(int)satll->msg[(int)svId-120].messageType17.satellites[i].PRN_code_number-120] = satll->msg[(int)svId-120].messageType17.satellites[i].Health_and_status;
    }
    satll->msg[(int)svId-120].messageType17.t_almanac = std::bitset<11>(data.substr(201, 11)).to_ulong() * 64;
    for(int i = 0; i < 3; ++i){
        int uydu_num = satll->msg[(int)svId-120].messageType17.satellites[i].PRN_code_number;
        if (uydu_num-120 >= 0 and uydu_num - 120 <= 38){
            satll->alm[uydu_num-120].reserved = satll->msg[(int)svId-120].messageType17.satellites[i].reserved;
            satll->alm[uydu_num-120].PRN_code_number   = satll->msg[(int)svId-120].messageType17.satellites[i].PRN_code_number  ;
            satll->alm[uydu_num-120].Health_and_status = satll->msg[(int)svId-120].messageType17.satellites[i].Health_and_status;
            satll->alm[uydu_num-120].location_X_G_A    = satll->msg[(int)svId-120].messageType17.satellites[i].location_X_G_A   ;
            satll->alm[uydu_num-120].location_Y_G_A    = satll->msg[(int)svId-120].messageType17.satellites[i].location_Y_G_A   ;
            satll->alm[uydu_num-120].location_Z_G_A    = satll->msg[(int)svId-120].messageType17.satellites[i].location_Z_G_A   ;
            satll->alm[uydu_num-120].velocity_X_G_A    = satll->msg[(int)svId-120].messageType17.satellites[i].velocity_X_G_A   ;
            satll->alm[uydu_num-120].velocity_Y_G_A    = satll->msg[(int)svId-120].messageType17.satellites[i].velocity_Y_G_A   ;
            satll->alm[uydu_num-120].velocity_Z_G_A    = satll->msg[(int)svId-120].messageType17.satellites[i].velocity_Z_G_A   ;
        }
    }
    satll->alm[(int)svId-120].messageType17 = satll->msg[(int)svId-120].messageType17;
}

void ubxSetterFunctions::set_message_type_12(std::string data, SbasNavData *satll, uint8_t svId) {

    satll->msg[(int)svId-120].messageType12.A_1_SNT           = sbasHelperFunctions::sign_check(std::bitset<24>(data.substr(0, 24)).to_string(),24) * pow(2,-50);
    satll->msg[(int)svId-120].messageType12.A_0_SNT           = sbasHelperFunctions::sign_check(std::bitset<32>(data.substr(24, 32)).to_string(),32) * pow(2,-30);
    satll->msg[(int)svId-120].messageType12.t_0t              = std::bitset<8>(data.substr(56, 8)).to_ulong() * 4096;
    satll->msg[(int)svId-120].messageType12.WN_t              = std::bitset<8>(data.substr(64, 8)).to_ulong();
    satll->msg[(int)svId-120].messageType12.deltaT_ls         = sbasHelperFunctions::sign_check(std::bitset<8>(data.substr(72, 8)).to_string(),8);
    satll->msg[(int)svId-120].messageType12.WN_lsf            = std::bitset<8>(data.substr(80, 8)).to_ulong();
    satll->msg[(int)svId-120].messageType12.DN                = std::bitset<8>(data.substr(88, 8)).to_ulong();
    satll->msg[(int)svId-120].messageType12.deltaT_lsf        = sbasHelperFunctions::sign_check(std::bitset<8>(data.substr(96, 8)).to_string(),8);
    satll->msg[(int)svId-120].messageType12.UTC_std_idtf      = std::bitset<3>(data.substr(104, 3)).to_ulong();
    satll->msg[(int)svId-120].messageType12.TOW               = std::bitset<20>(data.substr(107, 20)).to_ulong();
    satll->msg[(int)svId-120].messageType12.WN                = std::bitset<10>(data.substr(127, 10)).to_ulong();
    satll->msg[(int)svId-120].messageType12.glonass_indicator = std::bitset<1>(data.substr(137, 1)).to_ulong() * 2 * pow(10,-31);
    satll->msg[(int)svId-120].messageType12.gamma_a_i_glonass = sbasHelperFunctions::sign_check(std::bitset<24>(data.substr(138, 24)).to_string(),24);
    satll->msg[(int)svId-120].messageType12.spare             = (data.substr(162, 50));
}

void ubxSetterFunctions::set_message_type_10(std::string data, SbasNavData *satll, uint8_t svId) {

    satll->msg[(int)svId-120].messageType10.B_rrc         = std::bitset<10>(data.substr(0, 10)).to_ulong() * 0.002;
    satll->msg[(int)svId-120].messageType10.C_ltc_lsb     = std::bitset<10>(data.substr(10, 10)).to_ulong() * 0.002;
    satll->msg[(int)svId-120].messageType10.C_ltc_v1      = std::bitset<10>(data.substr(20, 10)).to_ulong() * 0.00005;
    satll->msg[(int)svId-120].messageType10.I_ltc_v1      = std::bitset<9>(data.substr(30, 9)).to_ulong();
    satll->msg[(int)svId-120].messageType10.C_ltc_v0      = std::bitset<10>(data.substr(39, 10)).to_ulong() * 0.002;
    satll->msg[(int)svId-120].messageType10.I_ltc_v0      = std::bitset<9>(data.substr(49, 9)).to_ulong();
    satll->msg[(int)svId-120].messageType10.C_geo_lsb     = std::bitset<10>(data.substr(58, 10)).to_ulong() * 0.0005;
    satll->msg[(int)svId-120].messageType10.C_geo_v       = std::bitset<10>(data.substr(68, 10)).to_ulong() * 0.00005;
    satll->msg[(int)svId-120].messageType10.I_geo         = std::bitset<9>(data.substr(78, 9)).to_ulong();
    satll->msg[(int)svId-120].messageType10.C_er          = std::bitset<6>(data.substr(87, 6)).to_ulong() / 2;
    satll->msg[(int)svId-120].messageType10.C_iono_step   = std::bitset<10>(data.substr(93, 10)).to_ulong() * 0.001;
    satll->msg[(int)svId-120].messageType10.I_iono        = std::bitset<9>(data.substr(103, 9)).to_ulong();
    satll->msg[(int)svId-120].messageType10.C_iono_ramp   = std::bitset<10>(data.substr(112, 10)).to_ulong() * 0.000005;
    satll->msg[(int)svId-120].messageType10.RSS_UDRE      = std::bitset<1>(data.substr(122, 1)).to_ulong();
    satll->msg[(int)svId-120].messageType10.RSS_iono      = std::bitset<1>(data.substr(123, 1)).to_ulong();
    satll->msg[(int)svId-120].messageType10.C_covariance  = std::bitset<7>(data.substr(124, 7)).to_ulong() * 0.1;
    satll->msg[(int)svId-120].messageType10.Spare         = (data.substr(131, 81));
}

void ubxSetterFunctions::set_message_type_9(std::string data, SbasNavData *satll, uint8_t svId) {

    satll->msg[(int)svId-120].messageType9.reserved       = std::bitset<8>(data.substr(0, 8)).to_ulong();
    satll->msg[(int)svId-120].messageType9.t0_geo         = std::bitset<13>(data.substr(8, 13)).to_ulong() * 16;
    satll->msg[(int)svId-120].messageType9.URA            = uravalue(std::bitset<4>(data.substr(21, 4)).to_ulong());
    satll->msg[(int)svId-120].messageType9.location_X     = sbasHelperFunctions::sign_check(std::bitset<30>(data.substr(25, 30)).to_string(),30) * 0.08 ;
    satll->msg[(int)svId-120].messageType9.location_Y     = sbasHelperFunctions::sign_check(std::bitset<30>(data.substr(55, 30)).to_string(),30) * 0.08 ;
    satll->msg[(int)svId-120].messageType9.location_Z     = sbasHelperFunctions::sign_check(std::bitset<25>(data.substr(85, 25)).to_string(),25) * 0.4 ;
    satll->msg[(int)svId-120].messageType9.velocity_X     = sbasHelperFunctions::sign_check(std::bitset<17>(data.substr(110, 17)).to_string(),17) * 0.000625 ;
    satll->msg[(int)svId-120].messageType9.velocity_Y     = sbasHelperFunctions::sign_check(std::bitset<17>(data.substr(127, 17)).to_string(),17) * 0.000625 ;
    satll->msg[(int)svId-120].messageType9.velocity_Z     = sbasHelperFunctions::sign_check(std::bitset<18>(data.substr(144, 18)).to_string(),18) * 0.004 ;
    satll->msg[(int)svId-120].messageType9.acceleration_X = sbasHelperFunctions::sign_check(std::bitset<10>(data.substr(162, 10)).to_string(),10) * 0.0000125 ;
    satll->msg[(int)svId-120].messageType9.acceleration_Y = sbasHelperFunctions::sign_check(std::bitset<10>(data.substr(172, 10)).to_string(),10) * 0.0000125 ;
    satll->msg[(int)svId-120].messageType9.acceleration_Z = sbasHelperFunctions::sign_check(std::bitset<10>(data.substr(182, 10)).to_string(),10) * 0.0000625 ;
    satll->msg[(int)svId-120].messageType9.a_gf0          = sbasHelperFunctions::sign_check(std::bitset<12>(data.substr(192, 12)).to_string(),12) * pow(2,-31);
    satll->msg[(int)svId-120].messageType9.a_gf1          = sbasHelperFunctions::sign_check(std::bitset<8>(data.substr(204, 8)).to_string(),8) * pow(2,-40);

    satll->msg[(int)svId-120].svIdRinex.messageType9 = satll->msg[(int)svId-120].messageType9;
}

void ubxSetterFunctions::set_message_type_7(std::string data, SbasNavData *satll, uint8_t svId) {

    satll->msg[(int)svId-120].messageType7.system_latency = std::bitset<4>(data.substr(0, 4)).to_ulong();
    satll->msg[(int)svId-120].messageType7.IODP           = std::bitset<2>(data.substr(4, 2)).to_ulong();
    satll->msg[(int)svId-120].messageType7.spare          = (data.substr(6, 2));

    for (int i = 0; i < 51; ++i) {
        satll->msg[(int)svId-120].messageType7.ai[i]      = std::bitset<4>(data.substr(8 + (i * 4), 4)).to_ulong();
    }
}

void ubxSetterFunctions::set_message_type_6(std::string data, SbasNavData *satll, uint8_t svId) {

    satll->msg[(int)svId-120].messageType6.IODF_2 = std::bitset<2>(data.substr(0, 2)).to_ulong();
    satll->msg[(int)svId-120].messageType6.IODF_3 = std::bitset<2>(data.substr(2, 2)).to_ulong();
    satll->msg[(int)svId-120].messageType6.IODF_4 = std::bitset<2>(data.substr(4, 2)).to_ulong();
    satll->msg[(int)svId-120].messageType6.IODF_5 = std::bitset<2>(data.substr(6, 2)).to_ulong();

    for (int i = 0; i < 51; ++i) {
        satll->msg[(int)svId-120].messageType6.UDREI[i] = std::bitset<4>(data.substr(8 + (i * 4), 4)).to_ulong();
    }
}

void ubxSetterFunctions::set_message_type_2to5(std::string data, SbasNavData *satll, uint8_t svId) {

    satll->msg[(int)svId-120].messageType2To5.IODF = std::bitset<2>(data.substr(0, 2)).to_ulong();
    satll->msg[(int)svId-120].messageType2To5.IODP = std::bitset<2>(data.substr(2, 2)).to_ulong();
    double fc_scale = 0.125;
    for (int i = 0; i < 13; ++i) {
        satll->msg[(int)svId-120].messageType2To5.FC[i] = sbasHelperFunctions::sign_check(std::bitset<12>(data.substr(4 + (i * 12), 12)).to_string(),12) * fc_scale;
    }

    for (int i = 0; i < 13; ++i) {
        satll->msg[(int)svId-120].messageType2To5.UDREI[i] = std::bitset<4>(data.substr(160 + (i * 4), 4)).to_ulong();
    }
}

void ubxSetterFunctions::set_message_type_1(std::string data, SbasNavData *satll, uint8_t svId) {
    for (int i = 0; i < 210; ++i) {
        satll->msg[(int)svId-120].messageType1.PRN_code_numbers[i] = std::bitset<1>(data.substr(i, 1)).to_ulong();
    }
    satll->msg[(int)svId-120].messageType1.IODP = std::bitset<2>(data.substr(210, 2)).to_ulong();
}

void ubxSetterFunctions::set_message_type_0_and_63(std::string data, SbasNavData *satll, uint8_t svId) {
    satll->msg[(int)svId-120].messageType0And63.spare = data.substr(0, 212);
}