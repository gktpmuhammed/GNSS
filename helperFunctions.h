//
// Created by Cezeri Stajyer on 19.08.2021.
//

#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "ubxMessage.h"
#include "vector"
#include "map"
#include <iomanip>
#include <bitset>
#include <fstream>

class sbasHelperFunctions{
public:
    static double binary_to_double(std::string bits);

    static double sign_check(std::string bits, int len);

    static void write_rinex_header(std::string outfile_path1);

    static void write_rinex(svId_RINEX rslt, std::string outfile_path1);

    static void set_health(SbasNavData *satll, uint8_t svId);

    static void calculate_time(SbasNavData *satll, uint8_t svId, bool is_week_set, std::string output_file_path, std::vector<svId_RINEX> &rinex_msg);

    static void uint32_birlestir (const uint8_t data[], int& idx, uint32_t& dwdord);

    static bool create_checksum_data(uint8_t classId,uint8_t msgId,uint8_t length,uint8_t gnssId,uint8_t svId, uint8_t payload[],uint8_t CK_A, uint8_t CK_B);

    static bool crc_calculation(std::string word_data);

};

#endif //HELPERFUNCTIONS_H
