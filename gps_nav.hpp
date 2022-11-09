/**
 * @file    : Ublox-Driver
 * @author  : MEHMET AKSU
 * @note    : mehmet.aksu@cezeri.com
 * @date    : 20 / Nisan / 2021
 * @code    : gps_nav.hpp file
 * @details : 
 */


#ifndef GPS_NAV_HPP
#define GPS_NAV_HPP

#include "navigation_base.hpp"


template<>
struct Almanac<SatelliteSystem::GPS> {
    UINT8    svId_u8{};            ///!< Satellite identifier PRN
    UINT8    svHealth_u8{};        ///!< Satellite health information
    UINT8    svConfig_u8{};        ///!< SV config anti-spoofing
    FLOAT64  ecc_f64{};            ///!< Eccentricity
    INT32    week_s32{};           ///!< Almanac week number
    FLOAT64  toa_sn_f64{};         ///!<  Toa (s) in week
    FLOAT64  deltai_rad_f64{};     ///!< Delta orbital Inclination(rad)
    FLOAT64  i0_rad_f64{};         ///!< Orbital Inclination(rad)
    FLOAT64  OMGdot_rad_f64{};     ///!< Rate of Right Ascension(rad/s) omegaDot
    FLOAT64  sqrtA_m_f64{};        ///!< SQRT(A)  (m 1/2), Square root of semi-major axis, semiperiod
    FLOAT64  omg0_rad_f64{};       ///!< Longitude of ascending node of orbital plane (rad)
    FLOAT64  omg_rad_f64{};        ///!< Argument of Perigee(rad)
    FLOAT64  m0_rad_f64{};         ///!< Mean Anomaly at reference time(rad)
    FLOAT64  af0_s_f64{};          ///!< Af0(s): Satellite clock bias
    FLOAT64  af1_ss_f64{};         ///!< Af1(s/s): Satellite clock rate
};

template<>
struct Ephemeris<SatelliteSystem::GPS> {
    UINT8   svId_u8{};              ///!< Satellite identifier PRN
    UINT8   svHealth_u8{};          ///!< Satellite health information
    INT32   week_s32{};             ///!< Ephemeris week number
    INT32   fitInterval_s32{};      ///!< fit interval (h)
    UINT8   uraIndex_u8{};          ///!< SV accuracy URA index
    FLOAT64 IODE_f64{};             ///!< IODE Index of data - ephemeris
    UINT16  IODC_u16{};             ///!< IODC Index of data - clock
    UINT8   codeflags_u8{};         ///!< L2 codes
    UINT8   L2P_flag_u8{};          ///!< L2 P data flag
    FLOAT64 HOWtime_f64{};          ///< Time (seconds-of-week) of handover word (txmit)

    FLOAT64 tgd_s_f64{};            ///!< Group delay differential Ionospheric L1/L2 data correction (seconds)

    FLOAT64 Toe{};                  ///!< Time of Ephemeris Epoch
    FLOAT64 Toc{};                  ///!< Time of Clock Epoch
    FLOAT64 Tot{};                  ///!< Time of Transmission

    /// Clock informations
    FLOAT64 af0_s_f64{};            ///!< Time polynomial coefficient 0 - SV clock bias (sec)
    FLOAT64 af1_ss_f64{};           ///!< Time polynomial coefficient 1 - SV clock drift (sec/sec)
    FLOAT64 af2_ss2_f64{};          ///!< Time polynomial coefficient 2 - SV clock drift rate (sec/sec**2)

    /// Major orbit parameters
    FLOAT64 sqrtA_f64{};            ///!< Square root of semi-major axis (m 1/2)
    FLOAT64 OMGdot_rad_f64{};       ///!< Rate of Right Ascension(rad/s)
    FLOAT64 deltaN_rad_sec_f64{};   ///!< Mean motion difference from computed value at reference time
    FLOAT64 m0_rad_f64{};           ///!< Mean anomaly at reference time
    FLOAT64 ecc_f64{};              ///!< Eccentricity
    FLOAT64 omega_rad_f64{};        ///!< Argument of Perigee(rad)
    FLOAT64 omega0_rad_f64{};       ///!< Longitude of ascending node of orbital plane at weekly epoch
    FLOAT64 i0_rad_f64{};           ///!< Inclination angle(rad), at reference time
    FLOAT64 IDOT_rad_sec_f64{};     ///!< Inclination Rate rad/sec

    /// Harmonic perturbations
    FLOAT64 Cis_rad_f64{};          ///!< Amplitude of sine harmonic correction term to angle of inclination
    FLOAT64 Cic_rad_f64{};          ///!< Amplitude of cosine harmonic correction term to angle of inclination
    FLOAT64 Crs_m_f64{};            ///!< Amplitude of sine correction term to orbit radius
    FLOAT64 Crc_m_f64{};            ///!< Amplitude of cosine correction term to orbit radius
    FLOAT64 Cus_rad_f64{};          ///!< Amplitude of sine harmonic correction term to argument of latitude
    FLOAT64 Cuc_rad_f64{};          ///!< Amplitude of cosine harmonic correction term to argument of latitude

};


template<>
struct UTC<SatelliteSystem::GPS> {
    FLOAT64 A0_s_f64{};      ///!< First parameter of UTC polynomial
    FLOAT64 A1_ss_f64{};     ///!< Second parameter of UTC polynomial
    FLOAT64 DtLS_s_f64{};     ///!< Delta time due to current leap seconds
    FLOAT64 Tot_s_f64{};      ///!< UTC parameters reference time of week (GPS time)
    FLOAT64 WNt_f64{};        ///!< UTC parameters reference week number
    FLOAT64 WNlsf_f64{};      ///!< Week number at the end of which the future leap second becomes effective
    FLOAT64 Dn_f64{};         ///!< Day number at the end of which the future leap second becomes effective
    FLOAT64 DtLSF_s_f64{};    ///!< Delta time due to future leap seconds
};

template<>
struct Ionosphere<SatelliteSystem::GPS> {
    FLOAT64 alpha0_f64{};   ///!< Ionospheric parameter alpha0 [s]
    FLOAT64 alpha1_f64{};   ///!< Ionospheric parameter alpha1 [s/semi-circle]
    FLOAT64 alpha2_f64{};   ///!< Ionospheric parameter alpha2 [s/semi-circle^2]
    FLOAT64 alpha3_f64{};   ///!< Ionospheric parameter alpha3 [s/semi-circle^3]
    FLOAT64 beta0_f64{};    ///!< Ionospheric parameter beta0 [s]
    FLOAT64 beta1_f64{};    ///!< Ionospheric parameter beta1 [s/semi-circle]
    FLOAT64 beta2_f64{};    ///!< Ionospheric parameter beta2 [s/semi-circle^2]
    FLOAT64 beta3_f64{};    ///!< Ionospheric parameter beta3 [s/semi-circle^3]
};

using GPSUTC        = UTC<SatelliteSystem::GPS>;
using GPSAlmanac    = Almanac<SatelliteSystem::GPS>;
using GPSEphemeris  = Ephemeris<SatelliteSystem::GPS>;
using GPSIonosphere = Ionosphere<SatelliteSystem::GPS>;

struct GpsNavData {

    GPSAlmanac    alm[Num_Gps_Satellites]{};
    GPSEphemeris  eph[Num_Gps_Satellites]{};
    UINT8         health[Num_Gps_Satellites]{};
    GPSUTC        utc{};
    GPSIonosphere iono{};
};


#endif /* GPS_NAV_HPP */