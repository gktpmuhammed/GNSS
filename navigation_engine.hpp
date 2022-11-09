/**
 * @file    : Ublox-Driver 
 * @authors : Mehmet Aksu, Uzay Uysal, Furkan Pala
 * @note    : mehmet.aksu@cezeri.com
 * @date    : 12 / Nisan / 2021
 * @code    : navigation_engine.hpp file
 * @details : 
 */

#ifndef NAVIGATION_ENGINE_HPP
#define NAVIGATION_ENGINE_HPP

#include <map>
#include <string>
#include "gps_nav.hpp"
/*#include "glonass_nav.hpp"
#include "gps_subframe.hpp"*/
#include "helperFunctions.h"


template<::SatelliteSystem s>
class NavEng {};

/*template <>
class NavEng<::SatelliteSystem::GPS> {
public:

    void yakala_subframe_data_LNAV (const std::uint32_t(&word)[10], std::uint8_t svId);
    void yakala_subframe_data_CNAV (const std::uint32_t(&word)[10], std::uint8_t svId);

    typedef union {
        struct {
            UINT8 sbfrm1    : 1;
            UINT8 sbfrm2    : 1;
            UINT8 sbfrm3    : 1;
            UINT8 sbfrm4    : 1;
            UINT8 sbfrm5    : 1;
            UINT8 almanac   : 1;
            UINT8 ephemeris : 1;
            UINT8 reserved  : 1;
        } new_nav_msg;
        UINT8 u8;
    }yeni_subframe;

    using satId = int;
    std::map<satId, yeni_subframe> yeni_subframe_map{};
    bool       week_geldi {false};

    GpsNavData data{}; ///!< GPS Navigation Message Data

private:

    using GpsL1Subframe1 = GpsSubframe<TrackingCode::L1CA, Subframe::one>;
    using GpsL1Subframe2 = GpsSubframe<TrackingCode::L1CA, Subframe::two>;
    using GpsL1Subframe3 = GpsSubframe<TrackingCode::L1CA, Subframe::three>;
    using GpsL1Subframe4 = GpsSubframe<TrackingCode::L1CA, Subframe::four>;
    using GpsL1Subframe5 = GpsSubframe<TrackingCode::L1CA, Subframe::five>;

    GpsL1Subframe1 L1_Subframe1{};  ///!< L1 Subframe 1
    GpsL1Subframe2 L1_Subframe2{};  ///!< L1 Subframe 2
    GpsL1Subframe3 L1_Subframe3{};  ///!< L1 Subframe 3
    GpsL1Subframe4 L1_Subframe4{};  ///!< L1 Subframe 4
    GpsL1Subframe5 L1_Subframe5{};  ///!< L1 Subframe 5
};

class EphemerisFile;

template <>
class NavEng<::SatelliteSystem::Glonass> {
public:
    void yakala_glonass_nav_string (const std::uint32_t(&word)[10], std::uint8_t svId);

    typedef union {
        struct {
            UINT8 str1      : 1;
            UINT8 str2      : 1;
            UINT8 str3      : 1;
            UINT8 str4      : 1;
            UINT8 str5      : 1;
            UINT8 almstr1   : 1;
            UINT8 almstr2   : 1;
            UINT8 ephemeris : 1;
            UINT8 almanac   : 1;
            UINT8 reserved  : 7;
        };
        UINT16 u16;
    } new_data;

    using satId = int;
    std::map<satId, new_data> new_data_map{};

    GlonassNavData  superframes{};

private:
    friend class EphemerisFile;
    static time_t zaman_damgasi_al (UINT32 curYear, UINT16 curMonth, UINT32 curDay, UINT32 tb_mins);

    void tarih_saat_hesapla (INT32& curYear, INT32& curMonth, INT32& curDay, INT32& tb_mins, size_t gelen_ephemeris_satId) const;
};*/

template <>
class NavEng<::SatelliteSystem::SBAS> {
public:
    void yakala_sbas_nav_data (const std::uint32_t(&word)[10], std::uint8_t svId);
    /// tow ve week değerlerinin gelme durumlarını tutar
    bool is_week_set = false;
    bool time_ok = true;
    /// ilk utc mesajı gelene kadar oluşturulmuş olan konum mesajlarını saklar
    std::vector<svId_RINEX> rinex_msg;
    std::string input_file_path = R"(C:\Users\Cezeri Stajyer\CLionProjects\SBAS_Navigation_Message_Decode\COM6_210813_111929.ubx)";
    std::string output_file_path = R"(C:\Users\Cezeri Stajyer\CLionProjects\diffFilesclass\output_COM3_210812_112916.txt)";
    SbasNavData sbasNavData;         ///!< SBAS Navigation Message Data
};


#endif /* NAVIGATION_ENGINE_HPP */