/**
 * @file    : Ublox-Driver 
 * @authors : MEHMET AKSU
 * @note    : mehmet.aksu@cezeri.com
 * @date    : 12 / Nisan / 2021
 * @code    : navigation_engine.cpp file
 * @details : 
 */

#include <bitset>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include "navigation_engine.hpp"

/*void NavEng<SatelliteSystem::GPS>::yakala_subframe_data_LNAV (const std::uint32_t(&word)[10], std::uint8_t svId)
{
    std::cout << "GPS LNAV PRN : " << std::setw(3) <<  UINT32{svId} << " Subframe Id " << UINT32{HOW{.word = word[1]}.subframe_id} << std::endl;

    switch (as_subframe(HOW{.word = word[1]}.subframe_id))
    {
        case Subframe::one:
        {
            L1_Subframe1.coz(word);
            L1_Subframe1.anlamlandir(&data, svId);
            yeni_subframe_map[svId].new_nav_msg.sbfrm1 = 1;
            week_geldi = true;
            break;
        }
        case Subframe::two:
        {
            L1_Subframe2.coz(word);
            L1_Subframe2.anlamlandir(&data, svId);
            yeni_subframe_map[svId].new_nav_msg.sbfrm2 = 1;
            break;
        }
        case Subframe::three:
        {
            L1_Subframe3.coz(word);
            L1_Subframe3.anlamlandir(&data, svId);
            yeni_subframe_map[svId].new_nav_msg.sbfrm3 = 1;
            break;
        }
        case Subframe::four:
        {
            L1_Subframe4.coz(word);
            L1_Subframe4.anlamlandir(&data);
            if (L1_Subframe4.pageId == SUBFRAME_4_ALMANAC_PAGE)
                yeni_subframe_map[L1_Subframe4.svId].new_nav_msg.sbfrm4 = 1;
            break;
        }
        case Subframe::five:
        {
            L1_Subframe5.coz(word);
            L1_Subframe5.anlamlandir(&data);
            if (L1_Subframe5.pageId == SUBFRAME_5_PAGE_1_THRU_24)
                yeni_subframe_map[L1_Subframe5.svId].new_nav_msg.sbfrm5 = 1;
            break;
        }
        default:
            break;
    }


    std::for_each(yeni_subframe_map.begin(), yeni_subframe_map.end(),
                  [&](auto& pair)
                  {
                      if (pair.second.new_nav_msg.sbfrm1 == 1 &&
                          pair.second.new_nav_msg.sbfrm2 == 1 &&
                          pair.second.new_nav_msg.sbfrm3 == 1   )
                      {
                          pair.second.new_nav_msg.ephemeris = 1;
                          pair.second.new_nav_msg.sbfrm1   = 0;
                          pair.second.new_nav_msg.sbfrm2   = 0;
                          pair.second.new_nav_msg.sbfrm3   = 0;

                          std::cout << "PRN : " << pair.first << " ephemeris geldi." << std::endl;
                      }
                      else
                      {
                          pair.second.new_nav_msg.ephemeris = 0;
                      }


                      if ((pair.second.new_nav_msg.sbfrm4 == 1  ||
                           pair.second.new_nav_msg.sbfrm5 == 1) && week_geldi )
                      {
                          pair.second.new_nav_msg.almanac  = 1;
                          pair.second.new_nav_msg.sbfrm4   = 0;
                          pair.second.new_nav_msg.sbfrm5   = 0;

                          std::cout << "PRN : " << pair.first << " almanac geldi." << std::endl;
                      }
                      else
                      {
                          pair.second.new_nav_msg.almanac  = 0;
                      }

                  });
}

void NavEng<::SatelliteSystem::GPS>::yakala_subframe_data_CNAV (const std::uint32_t(&word)[10], std::uint8_t svId)
{
//    std::cout << "GPS CNAV PRN : " << std::setw(3) <<  TLM_CNAV{.word = word[0]}.prn << std::endl;

}

void NavEng<SatelliteSystem::Glonass>::yakala_glonass_nav_string (const std::uint32_t(&word)[10], std::uint8_t svId)
{
    std::string str = std::bitset<32>{word[0]}.to_string() +
                      std::bitset<32>{word[1]}.to_string() +
                      std::bitset<32>{word[2]}.to_string() +
                      std::bitset<32>{word[3]}.to_string();


    UINT8 str_num          =  std::stoi(str.substr(1, 4), nullptr, 2);
    UINT32 frame_num       =  std::stoi(str.substr(120, 8), nullptr, 2);
    UINT32 super_frame_num =  std::stoi(str.substr(96, 16), nullptr, 2);

    if (!GlonassUtility::check_hamming_code(str))
        return;

    std::cout << "Glonass PRN  : " << std::setw(3) <<  int{svId} << " Frame Id " << frame_num << std::endl;

    if (str_num == 1)
    {
        GlonassUtility::parse_type1_str(str, superframes, svId); new_data_map[svId].str1 = 1;
    }
    else if (str_num == 2)
    {
        GlonassUtility::parse_type2_str(str, superframes, svId);
        new_data_map[svId].str2 = 1;
    }
    else if (str_num == 3)
    {
        GlonassUtility::parse_type3_str(str, superframes, svId);
        new_data_map[svId].str3 = 1;
    }
    else if (str_num == 4)
    {
        GlonassUtility::parse_type4_str(str, superframes, svId);
        new_data_map[svId].str4 = 1;
    }
    else if (str_num == 5)
    {
        GlonassUtility::parse_type5_str(str, superframes);
        new_data_map[svId].str5 = 1;
    }
    else if (str_num % 2 == 0)
    {
        GlonassUtility::parse_type6_str(str, superframes, frame_num, str_num);
        auto sat_index = (frame_num - 1) * 5 + (str_num - 6) / 2;
        new_data_map[sat_index + 1].almstr1 = 1;
    }
    else if (str_num % 2 == 1)
    {
        GlonassUtility::parse_type7_str(str, superframes, frame_num, str_num, svId);
        auto sat_index = (frame_num - 1) * 5 + (str_num - 7) / 2;
        new_data_map[sat_index + 1].almstr2 = 1;

    }

    if (new_data_map[svId].str1     == 1 &&
        new_data_map[svId].str2     == 1 &&
        new_data_map[svId].str3     == 1 &&
        new_data_map[svId].str4     == 1 &&
        new_data_map[svId].str5     == 1 )
    {
        new_data_map[svId].ephemeris = 1;
        new_data_map[svId].str1      = 0;
        new_data_map[svId].str2      = 0;
        new_data_map[svId].str3      = 0;
        new_data_map[svId].str4      = 0;
        new_data_map[svId].str5      = 0;
    }
    else
    {
        new_data_map[svId].ephemeris = 0;
    }

    std::for_each(new_data_map.begin(), new_data_map.end(),
                  [&](auto& pair)
                  {
                        if (pair.second.almstr1 == 1 && pair.second.almstr2 == 1)
                        {
                            pair.second.almanac = 1;
                            pair.second.almstr1 = 0;
                            pair.second.almstr2 = 0;
                        }
                        else
                            pair.second.almanac = 0;
                  });
}

time_t NavEng<SatelliteSystem::Glonass>::zaman_damgasi_al (UINT32 curYear, UINT16 curMonth, UINT32 curDay, UINT32 tb_mins)
{
    std::tm t{};
    std::stringstream ss_time{};

    ss_time << curYear << '-' <<
            std::setw(2) << std::setfill('0') << curMonth               << '-' <<
            std::setw(2) << std::setfill('0') << curDay                 << 'T' <<
            std::setw(2) << std::setfill('0') << tb_mins/MINS_IN_HOUR   << ':' <<
            std::setw(2) << std::setfill('0') << tb_mins % MINS_IN_HOUR << ":00";

    ss_time >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S");
    if (ss_time.fail())
    {
        throw std::runtime_error{"failed to parse time string"};
    }
    std::cerr << ss_time.str() << std::endl;
    return mktime(&t);
}

void NavEng<SatelliteSystem::Glonass>::tarih_saat_hesapla (INT32& curYear, INT32& curMonth, INT32& curDay, INT32& tb_mins, size_t gelen_ephemeris_satId) const
{
    static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    static const int leap_days[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    //!< Calculation given in GLONASS ICD
    //!< Be careful about the bug in 2016 edition
    //!< (Nt-3)/25 part should not be included!!!
    double JD0 = DAYS_IN_FOUR_YEARS*( superframes.time_offset.N4_years_u32 - 1) + superframes.time_offset.N_days_u16 + 2450082.5;
    double JDN = JD0 + 0.5;
    int64_t a  = JDN + 32044;
    int64_t b  = (4*a + 3)/146097;
    int64_t c  = a - (146097 * b)/4;
    int64_t d  = (4 * c + 3)/DAYS_IN_FOUR_YEARS;
    int64_t e  = c - (DAYS_IN_FOUR_YEARS * d)/4;
    int64_t m  = (5*e + 2)/153;

    curDay   = e - (153*m+2)/5 + 1;
    curMonth = m + 3 - 12*(m/10);
    curYear  = 100 * b + d - 4800 + (m/10);

    tb_mins = superframes.eph[gelen_ephemeris_satId - 1].tb_minutes_u32;
    INT32 tb_hours = (tb_mins / MINS_IN_HOUR) - GLONASS_HOUR_OFFSET;

    if (tb_hours < 0)
    {
        tb_hours += HOURS_IN_DAY;
        curDay--;
        if (curDay == 0)
        {
            if (curYear % 4 == 0)
            {
                curDay = leap_days[curMonth--];
            }
            else
            {
                curDay = days[curMonth--];
            }
            if (curMonth == 0)
            {
                curYear--;
                curMonth = DECEMBER;
            }
        }
    }
}*/

void NavEng<SatelliteSystem::SBAS>::yakala_sbas_nav_data (const std::uint32_t(&word)[10], std::uint8_t svId)
{
    std::string word_data;
    for (int i = 0; i < 9; ++i)
    {
        word_data += std::bitset<32>(word[i]).to_string();
    }

    uint8_t preamble    = std::bitset<8>(word_data.substr(0,8)).to_ulong();
    uint8_t msg_type    = std::bitset<6>(word_data.substr(8,6)).to_ulong();
    std::string data    = word_data.substr(14,212);
    std::string parity  = word_data.substr(226,24);
    std::string pad     = word_data.substr(250,6);

    bool resulting_pad = sbasHelperFunctions::crc_calculation(word_data);

    if (resulting_pad){
        sbasNavData.msg[svId-120].svIdRinex.svId = svId;
        switch (msg_type) {
            /// Type 0 “Do Not Use” message and Type 63 null message
            case type_0_and_63:
            case 63:
                ubxSetterFunctions::set_message_type_0_and_63(data, &sbasNavData, svId);
                break;
                /// Type 1 PRN mask message
            case type_1:
                ubxSetterFunctions::set_message_type_1(data, &sbasNavData, svId);
                break;
                /// Types 2 to 5 fast correction message
            case type_2to5:
            case 3:
            case 4:
            case 5:
                ubxSetterFunctions::set_message_type_2to5(data, &sbasNavData, svId);
                break;
                /// Type 6 integrity message
            case type_6:
                ubxSetterFunctions::set_message_type_6(data, &sbasNavData, svId);
                break;
                /// Type 7 fast correction degradation factor message
            case type_7:
                ubxSetterFunctions::set_message_type_7(data, &sbasNavData, svId);
                break;
                /// Type 9 ranging function message
            case type_9:
                ubxSetterFunctions::set_message_type_9(data, &sbasNavData, svId);
                sbasHelperFunctions::calculate_time(&sbasNavData, svId, is_week_set, output_file_path, rinex_msg);
                break;
                /// Type 10 degradation parameter message
            case type_10:
                ubxSetterFunctions::set_message_type_10(data, &sbasNavData, svId);
                break;
                /// Type 12 SBAS network time/UTC message
            case type_12:
                ubxSetterFunctions::set_message_type_12(data, &sbasNavData, svId);
                sbasNavData.utc.messageType12 = sbasNavData.msg[svId-120].messageType12;
                is_week_set = true;
                if (is_week_set and time_ok){
                    for (int i = 0; i < rinex_msg.size(); i++) {
                        sbasHelperFunctions::calculate_time(&sbasNavData, rinex_msg[i].svId, is_week_set, output_file_path, rinex_msg);
                    }
                    time_ok = false;
                }
                break;
                /// Type 17 GEO almanac message
            case type_17:
                ubxSetterFunctions::set_message_type_17(data, &sbasNavData, svId);
                break;
                /// Type 18 IGP mask message
            case type_18:
                ubxSetterFunctions::set_message_type_18(data, &sbasNavData, svId);
                sbasNavData.iono[svId-120].messageType18 = sbasNavData.msg[svId-120].messageType18;
                break;
                /// Type 24 mixed fast/long-term satellite error correction message
            case type_24:
                ubxSetterFunctions::set_message_type_24(data, &sbasNavData, svId);
                break;
                /// Type 25 long-term satellite error correction half message
            case type_25:
                ubxSetterFunctions::set_message_type_25(data, &sbasNavData, svId);
                break;
                /// Type 26 Ionospheric delay message
            case type_26:
                ubxSetterFunctions::set_message_type_26(data, &sbasNavData, svId);
                sbasNavData.iono[svId-120].messageType26 = sbasNavData.msg[svId-120].messageType26;
                break;
                /// Type 27 SBAS service message
            case type_27:
                ubxSetterFunctions::set_message_type_27(data, &sbasNavData, svId);
                break;
                /// Type 28 clock-ephemeris covariance matrix
            case type_28:
                ubxSetterFunctions::set_message_type_28(data, &sbasNavData, svId);
                break;
        }
    }
}
