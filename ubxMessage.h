//
// Created by Cezeri Stajyer on 19.08.2021.
//

#ifndef UBXMESSAGE_H
#define UBXMESSAGE_H

#include "sbasMessageType.h"
#include "navigation_base.hpp"
//#include "rtklib.h"

//sbsion_t sbsion[MAXBAND+1];

static const double ura_eph[]={         /* ura values (ref [3] 20.3.3.3.1.1) */
        2.4,3.4,4.85,6.85,9.65,13.65,24.0,48.0,96.0,192.0,384.0,768.0,1536.0,
        3072.0,6144.0,0.0
};

/* ura index to ura value (m) ------------------------------------------------*/
static double uravalue(int sva)
{
    return 0<=sva&&sva<15?ura_eph[sva]:32767.0;
}

typedef struct {
    /// rinex dosyasına yazılacak uydunun numarası
    uint8_t svId = 0;
    /// mesajın geldiği tarih bütünü
    DateTime datetime;
    /// message transmission time
    double trnms_t = 0;
    /// ephemeris bilgileri
    message_type_9 messageType9{};
    /// uydu health değeri
    double health = 0;
}svId_RINEX;

/// Message type struct
struct Message{
    message_type_0_and_63   messageType0And63{};
    message_type_1          messageType1{};
    message_type_2to5       messageType2To5{};
    message_type_6          messageType6{};
    message_type_7          messageType7{};
    message_type_9          messageType9{};
    message_type_10         messageType10{};
    message_type_12         messageType12{};
    message_type_17         messageType17{};
    message_type_18         messageType18{};
    message_type_24         messageType24{};
    message_type_25         messageType25{};
    message_type_26         messageType26{};
    message_type_27         messageType27{};
    message_type_28         messageType28{};
    svId_RINEX              svIdRinex;
};

/*typedef struct {
    uint8_t     preamble;
    uint8_t     msg_type;
    std::string data;
    std::string parity;
    std::string pad;
    Message     message;
} UBX_RXM_SFRBX_DATA;

typedef struct {
    uint8_t gnssId;
    uint8_t svId;
    uint8_t reserved0;
    uint8_t freqId;
    uint8_t numWords;
    uint8_t chn;
    uint8_t version;
    uint8_t reserved1;
    uint32_t dwrd[10];
    std::string word_data;
    UBX_RXM_SFRBX_DATA ubxRxmSfrbxData;
} UBX_RXM_SFRBX;

typedef struct {
    uint8_t preamble1;
    uint8_t preamble2;
    uint8_t classId;
    uint8_t msgId;
    uint8_t length_low;
    uint8_t length_high;
    UBX_RXM_SFRBX payload;
    uint8_t CK_A;
    uint8_t CK_B;
} Ubx_Message_t;*/

typedef union {
    struct
    {
        uint32_t byte_0 : 8; // LSB
        uint32_t byte_1 : 8;
        uint32_t byte_2 : 8;
        uint32_t byte_3 : 8; // MSB
    };
    uint32_t u32;
} uint32_dort_byte;


template<>
struct Almanac<SatelliteSystem::SBAS> {
    message_type_17 messageType17{};
    double reserved = 0;
    /// a number that uniquely identifies the satellite PRN code and related assignments as shown in Table B-25.
    double PRN_code_number = 0;
    /// an indication of the functions provided by the SBAS. The service provider identifiers are shown in Table B-27 in section 3.5.1.
    double Health_and_status = 0;
    /// the position of the GEO at time talmanac.
    double location_X_G_A = 0;
    /// the position of the GEO at time talmanac.
    double location_Y_G_A = 0;
    /// the position of the GEO at time talmanac.
    double location_Z_G_A = 0;
    /// the velocity of the GEO at time talmanac.
    double velocity_X_G_A = 0;
    /// the velocity of the GEO at time talmanac.
    double velocity_Y_G_A = 0;
    /// the velocity of the GEO at time talmanac.
    double velocity_Z_G_A = 0;
    /// the reference time for the GEO almanac data, expressed as the time after midnight of the current day.
    double t_almanac = 0;
};

template<>
struct Ephemeris<SatelliteSystem::SBAS> {
    message_type_9 messageType9{};
};

template<>
struct UTC<SatelliteSystem::SBAS> {
    message_type_12 messageType12{};
};

template<>
struct Ionosphere<SatelliteSystem::SBAS> {
    message_type_18 messageType18{};
    message_type_26 messageType26{};
};

using SBASUTC        = UTC<SatelliteSystem::SBAS>;
using SBASAlmanac    = Almanac<SatelliteSystem::SBAS>;
using SBASEphemeris  = Ephemeris<SatelliteSystem::SBAS>;
using SBASIonosphere = Ionosphere<SatelliteSystem::SBAS>;

struct SbasNavData {

    SBASAlmanac    alm[Num_SBAS_Satellites]{};
    SBASEphemeris  eph[Num_SBAS_Satellites]{};
    UINT8         health[Num_SBAS_Satellites]{};
    SBASUTC        utc{};
    SBASIonosphere iono[Num_SBAS_Satellites]{};
    Message         msg[Num_SBAS_Satellites];

};

class ubxSetterFunctions{
public:
    static void set_message_type_0_and_63(std::string data, SbasNavData *satll, uint8_t svId);

    static void set_message_type_1(std::string data, SbasNavData *satll, uint8_t svId);

    static void set_message_type_2to5(std::string data, SbasNavData *satll, uint8_t svId);

    static void set_message_type_6(std::string data, SbasNavData *satll, uint8_t svId);

    static void set_message_type_7(std::string data, SbasNavData *satll, uint8_t svId);

    static void set_message_type_9(std::string data, SbasNavData *satll, uint8_t svId);

    static void set_message_type_10(std::string data, SbasNavData *satll, uint8_t svId);

    static void set_message_type_12(std::string data, SbasNavData *satll, uint8_t svId);

    static void set_message_type_17(std::string data, SbasNavData *satll, uint8_t svId);

    static void set_message_type_18(std::string data, SbasNavData *satll, uint8_t svId);

    static void set_message_type_24(std::string data, SbasNavData *satll, uint8_t svId);

    static void set_message_type_25(std::string data, SbasNavData *satll, uint8_t svId);

    static void set_message_type_26(std::string data, SbasNavData *satll, uint8_t svId);

    static void set_message_type_27(std::string data, SbasNavData *satll, uint8_t svId);

    static void set_message_type_28(std::string data, SbasNavData *satll, uint8_t svId);
};

#endif //UBXMESSAGE_H
