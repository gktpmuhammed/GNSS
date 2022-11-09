//
// Created by Cezeri Stajyer on 19.08.2021.
//

#include "helperFunctions.h"

bool sbasHelperFunctions::crc_calculation(std::string word_data){
    std::string CRC_Gx = "1100001100100110011111011";
    std::string CRC_pad = "000000000000000000000000";
    std::string CRC_information = word_data.substr(0,226);
    std::string parity = word_data.substr(226,24);
    int CRC_information_length = CRC_information.length();
    CRC_information += CRC_pad;

    while (CRC_information.find('1',0) < CRC_information_length){
        int starting_index = CRC_information.find('1',0);

        for (int i = 0; i < CRC_Gx.length(); ++i) {
            bool poly = CRC_Gx.substr(i,1) == "1";
            bool crc_char = CRC_information.substr(starting_index + i,1) == "1";
            CRC_information.at(starting_index + i) = poly xor crc_char ? '1' : '0';
        }
    }
    std::string new_pad = CRC_information.substr(226,24);

    return new_pad == parity;
}

bool sbasHelperFunctions::create_checksum_data(uint8_t classId,uint8_t msgId,uint8_t length,uint8_t gnssId,uint8_t svId, uint8_t payload[],uint8_t CK_A, uint8_t CK_B) {
    std::vector<uint8_t> checksum_data;
    checksum_data.push_back(classId);
    checksum_data.push_back(msgId);
    checksum_data.push_back(length%256);
    checksum_data.push_back(length/256);
    checksum_data.push_back(gnssId);
    checksum_data.push_back(svId);

    for (int i = 0; i < 42; ++i) {
        checksum_data.push_back(payload[i]);
    }
    uint8_t ck_a = 0;
    uint8_t ck_b = 0;

    for (int i = 0; i < checksum_data.size(); ++i) {
        ck_a = (ck_a + checksum_data[i]);
        ck_b = (ck_b + ck_a);
    }

    if(ck_a == CK_A && ck_b == CK_B)
        return true;
    else
        return false;
}

void sbasHelperFunctions::uint32_birlestir (const uint8_t data[], int& idx, uint32_t& dwdord){
    uint32_dort_byte temp{};
    temp.byte_0 = data[idx + 0];
    temp.byte_1 = data[idx + 1];
    temp.byte_2 = data[idx + 2];
    temp.byte_3 = data[idx + 3];
    dwdord = temp.u32;
}

void sbasHelperFunctions::calculate_time(SbasNavData *satll, uint8_t svId, bool is_week_set, std::string output_file_path, std::vector<svId_RINEX> &rinex_msg){
    auto tem = DateTime(gpst2time(adjgpsweek(satll->utc.messageType12.WN), satll->utc.messageType12.TOW));   // gelen tek msgtype9 datasından Tow değerini kullanarak günü buluyorum.
    int dyy = tem.get_dayOfWeek();                           // haftanın günü numarasını buluyorum.
    int sec = (dyy-1) * 86400 + satll->msg[svId-120].messageType9.t0_geo;    // gün numarasından 1 çıkartıyorum çünkü henüz o gün yaşanmadığı için o kadar saniye geçmemiş oluyor.

    if (is_week_set){
        if (sec != satll->msg[svId-120].svIdRinex.trnms_t){
            satll->msg[svId-120].svIdRinex.trnms_t = sec;
            auto datetime = DateTime(gpst2time(adjgpsweek(satll->utc.messageType12.WN), sec)); // üstte bulduğum haftanın saniysi ile week number kullarak datnın geldiği anı buluyorum.
            satll->msg[svId-120].svIdRinex.datetime = datetime;
            satll->eph[svId-120].messageType9 = satll->msg[svId-120].svIdRinex.messageType9;
            sbasHelperFunctions::set_health(satll, svId);
            sbasHelperFunctions::write_rinex(satll->msg[svId-120].svIdRinex, output_file_path);
        }
    }
    else{
        rinex_msg.push_back(satll->msg[svId-120].svIdRinex);
    }
}

void sbasHelperFunctions::set_health(SbasNavData *satll, uint8_t svId){
    std::string temp = std::bitset<8>(satll->health[svId-120]).to_string();
    /// satellitelardan health değeri gelmeyen bir uydu olursa aşağıda mapte bulamayacak burayı düşün
    if (temp == "00000000") {
        // not found
    }
    else {
        temp.at(3) = '1';   /// 4.biti değiştirmem gerekiyor 4. bit stringde 3. indise tekabül ediyor.

        if (satll->msg[svId-120].svIdRinex.messageType9.URA == 32767){
            temp.at(2) = '1';   /// 5.biti değiştirmem gerekiyor 5. bit stringde 2. indise tekabül ediyor.
        }
        if (temp.at(3) == '1'){
            temp = temp.substr(0,4) + "1111";
        }
        satll->msg[svId-120].svIdRinex.health = std::bitset<8>(temp).to_ulong();
    }
}

void sbasHelperFunctions::write_rinex_header(std::string outfile_path1){
    std::ofstream outfile(outfile_path1);
    outfile <<  "Sat_Num\tYear\tMonth\tDay\tHour\tMinute\tSecond\tSV_Clock_Bias\tSV_Relative_Frequency_Bias\tMessage_Transmission_Time"
                "\tSat_X_Pos\tSat_X_Velocity\tSat_X_Acc\tSat_Health\tSat_Y_Pos\tSat_Y_Velocity\tSat_Y_Acc"
                "\tURA\tSat_Z_Pos\tSat_Z_Velocity\tSat_Z_Acc\tIODN\n";
    outfile.close();
}

void sbasHelperFunctions::write_rinex(svId_RINEX rslt, std::string outfile_path1){
    std::ofstream outfile(outfile_path1, std::ios_base::app);

    outfile << "S"  << std::to_string(rslt.svId-100)       << "\t" << (rslt.datetime.get_year())              << "\t" << (rslt.datetime.get_month())
    << "\t" << (rslt.datetime.get_day())                   << "\t" << (rslt.datetime.get_hour())              << "\t" << (rslt.datetime.get_minute())
    << "\t" << (rslt.datetime.get_second())                << "\t" << std::setprecision(12)                    << std::scientific
    << (rslt.messageType9.a_gf0)                           << "\t" <<  (rslt.messageType9.a_gf1)              << "\t" << (rslt.trnms_t)
    << "\t" << (rslt.messageType9.location_X) / 1E3        << "\t" << (rslt.messageType9.velocity_X) / 1E3    << "\t" << (rslt.messageType9.acceleration_X)/ 1E3
    << "\t" << (rslt.health)                               << "\t" << (rslt.messageType9.location_Y) / 1E3    << "\t" << (rslt.messageType9.velocity_Y)/ 1E3
    << "\t" << (rslt.messageType9.acceleration_Y) / 1E3    << "\t" << (rslt.messageType9.URA)                 << "\t" << (rslt.messageType9.location_Z)/ 1E3
    << "\t" << (rslt.messageType9.velocity_Z)  / 1E3       << "\t" << (rslt.messageType9.acceleration_Z)/ 1E3
    << "\t" << (rslt.messageType9.reserved)                << "\n";

    outfile.close();
}

double sbasHelperFunctions::binary_to_double(std::string bits){
    double a = 0;
    for (int i = 0; i < bits.length(); ++i) {
        a += pow(2, i) * ((int)bits.at(bits.length()-i-1)-48);
    }
    return a;
}

double sbasHelperFunctions::sign_check(std::string bits, int len){
    double res;
    if (bits.at(0) == '1'){
        for (int i = 0; i < len; ++i) {
            if (bits.at(i) == '0')
                bits.at(i) = '1';
            else
                bits.at(i) = '0';
        }
        res = (binary_to_double(bits) + 1) * -1;
    }
    else
        res = binary_to_double(bits);
    return res;
}