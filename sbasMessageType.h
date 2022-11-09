//
// Created by Cezeri Stajyer on 19.08.2021.
//

#ifndef SBASMESSAGETYPE_H
#define SBASMESSAGETYPE_H

#include <iostream>
#include "datetime.hpp"


enum MessageType {
    type_0_and_63   = 0,
    type_1          = 1,
    type_2to5       = 2,
    type_6          = 6,
    type_7          = 7,
    type_9          = 9,
    type_10         = 10,
    type_12         = 12,
    type_17         = 17,
    type_18         = 18,
    type_24         = 24,
    type_25         = 25,
    type_26         = 26,
    type_27         = 27,
    type_28         = 28,
};

/// Type 0 “Do Not Use” message broadcast on L1
typedef struct {
    std::string spare;
}message_type_0_and_63;

/// Type 1 PRN mask message
typedef struct {
    /// a number that uniquely identifies the satellite PRN code and related assignments as shown in Table B-25.
    int PRN_code_numbers[210]{0};
    /// an indicator that associates the correction data with a PRN mask.
    int IODP = 0;
}message_type_1;

/// Types 2 to 5 fast correction message
typedef struct {
    /// an indicator that associates UDREIis with fast corrections. The index j shall denote the message type (j = 2 to 5)
    /// to which IODFj applies (the fast correction type identifier +2).
    int IODF = 0;
    /// an indicator that associates the correction data with a PRN mask.
    int IODP = 0;
    /// for satellite i, the pseudo-range correction for rapidly varying errors, other than tropospheric or ionospheric errors,
    /// to be added to the pseudo-range after application of the long-term correction.
    double FC[13]{0};
    /// an indicator that defines the σ2i,UDRE for satellite i as described in Table B-29.
    double UDREI[13]{0};
}message_type_2to5;

/// Type 6 integrity message
typedef struct {
    /// an indicator that associates UDREIis with fast corrections. The index j shall denote the message type (j = 2 to 5)
    /// to which IODFj applies (the fast correction type identifier +2).
    int IODF_2 = 0;
    int IODF_3 = 0;
    int IODF_4 = 0;
    int IODF_5 = 0;
    /// an indicator that defines the σ2i,UDRE for satellite i as described in Table B-29.
    double UDREI[51]{0};
}message_type_6;

/// Type 7 fast correction degradation factor message
typedef struct {
    /// the time interval between the origin of the fast correction degradation and the user differential range estimate indicator (UDREI) reference time.
    int system_latency = 0;
    /// an indicator that associates the correction data with a PRN mask.
    int IODP = 0;
    /// an indicator of the fast correction degradation factor (ai) for the ith satellite as described in Table B-34.
    double ai[51]{0};
    std::string spare;
}message_type_7;

/// Type 9 ranging function message
typedef struct {
    /// Issue of Data Navigation, see reference RTCA DO-229, 8 first bits after Message Type if MT9)(IODN)
    double reserved = 0;
    /// the reference time for the GEO ranging function data, expressed as the time after midnight of the current day.
    double t0_geo = 0;
    /// an indicator of the root-mean-square ranging error, excluding atmospheric effects, as described in Table B-26.
    double URA = 0;
    /// the position of the GEO at time t0,GEO.
    double location_X = 0;
    /// the position of the GEO at time t0,GEO.
    double location_Y = 0;
    /// the position of the GEO at time t0,GEO.
    double location_Z = 0;
    /// the velocity of the GEO at time t0,GEO.
    double velocity_X = 0;
    /// the velocity of the GEO at time t0,GEO.
    double velocity_Y = 0;
    /// the velocity of the GEO at time t0,GEO.
    double velocity_Z = 0;
    /// the acceleration of the GEO at time t0,GEO.
    double acceleration_X = 0;
    /// the acceleration of the GEO at time t0,GEO.
    double acceleration_Y = 0;
    /// the acceleration of the GEO at time t0,GEO.
    double acceleration_Z = 0;
    /// the time offset of the GEO clock with respect to SNT for L1 SBAS, defined at t0,GEO.
    double a_gf0 = 0;
    /// the drift rate of the GEO clock with respect to SNT for L1 SBAS.
    double a_gf1 = 0;
}message_type_9;

/// Type 10 degradation parameter message
typedef struct {
    /// a parameter that bounds the noise and round-off errors when computing the range rate correction degradation as in 3.5.5.6.2.2.
    double B_rrc        = 0;
    /// the maximum round-off error due to the resolution of the orbit and clock information.
    double C_ltc_lsb    = 0;
    /// the velocity error bound on the maximum range rate difference of missed messages due to clock and orbit rate differences.
    double C_ltc_v1     = 0;
    /// the update interval for long-term corrections if velocity code = 1 (3.5.4.4.1).
    double I_ltc_v1     = 0;
    /// a parameter that bounds the difference between two consecutive long-term corrections for satellites with a velocity code = 0.
    double C_ltc_v0     = 0;
    /// the minimum update interval for long-term messages if velocity code = 0 (3.5.4.4.1).
    double I_ltc_v0     = 0;
    /// the maximum round-off error due to the resolution of the orbit and clock information
    double C_geo_lsb    = 0;
    /// the velocity error bound on the maximum range rate difference of missed messages due to clock and orbit rate differences.
    double C_geo_v      = 0;
    /// the update interval for GEO ranging function messages.
    double I_geo        = 0;
    /// the bound on the residual error associated with using data beyond the precision approach/approach with vertical guidance time-out.
    double C_er         = 0;
    /// the bound on the difference between successive ionospheric grid delay values
    double C_iono_step  = 0;
    /// the minimum update interval for ionospheric correction messages
    double I_iono       = 0;
    /// the rate of change of the ionospheric corrections
    double C_iono_ramp  = 0;
    /// the root-sum-square flag for fast and long-term correction residuals
    double RSS_UDRE     = 0;
    /// the root-sum-square flag for ionospheric residuals
    double RSS_iono     = 0;
    /// the term which is used to compensate for quantization effects when using the Type 28 message
    double C_covariance = 0;
    std::string Spare  ;
}message_type_10;

/// Type 12 SBAS network time/UTC message
typedef struct {
    double A_1_SNT           = 0;
    double A_0_SNT           = 0;
    double t_0t              = 0;
    double WN_t              = 0;
    double deltaT_ls         = 0;
    double WN_lsf            = 0;
    double DN                = 0;
    double deltaT_lsf        = 0;
    /// an indication of the UTC reference source as defined in Table B-35
    double UTC_std_idtf      = 0;
    /// the number of seconds that have passed since the transition from the previous GPS week
    /// (similar to the GPS parameter in 3.1.1.2.6.1 but with a 1-second resolution).
    double TOW               = 0;
    /// GPS week number (week count):
    double WN                = 0;
    /// a flag indicating if GLONASS time parameters are provided
    double glonass_indicator = 0;
    /// A parameter broadcast on L1 that represents the stable part of the offset between the L1 GLONASS time and the L1 SBAS network time
    double gamma_a_i_glonass = 0;
    std::string spare;
}message_type_12;

/// Type 17 GEO almanac message
typedef struct {
    struct {
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
    }satellites[3];
    /// the reference time for the GEO almanac data, expressed as the time after midnight of the current day.
    double t_almanac = 0;
}message_type_17;

/// Type 18 IGP mask message
typedef struct {
    /// the number of IGP band masks being broadcast.
    int Number_of_IGP_bands = 0;
    /// the number identifying the ionospheric band as defined in Table B-30.
    int IGP_band_identifier = 0;
    /// an indication of when the kth IGP band mask changes
    int IODI_k = 0;
    /// a bit indicating whether data are provided within that IGP band for the associated IGP
    int IGP_mask_value[201]{0};
    std::string spare;
}message_type_18;

/// Type 24 mixed fast/long-term satellite error correction message
typedef struct {
    /// for satellite i, the pseudo-range correction for rapidly varying errors, other than tropospheric or ionospheric errors,
    /// to be added to the pseudo-range after application of the long-term correction.
    double FC[6]{0};
    ///  an indicator that defines the σ2i,UDRE for satellite i as described in Table B-29.
    double UDREI[6]{0};
    /// an indicator that associates the correction data with a PRN mask.
    int IODP = 0;
    /// Fast correction type identifier
    int FCTI = 0;
    /// an indicator that associates UDREIis with fast corrections. The index j shall denote the message type (j = 2 to 5)
    /// to which IODFj applies (the fast correction type identifier +2).
    int IODF_j = 0;
    std::string Spare;
    std::string Type_25_half_msg;
}message_type_24;

/// Type 25 long-term satellite error correction half message
typedef struct {
    /// an indicator of the message format broadcast (Table B-48 and Table B-49).
    int Velocity_Code_0 = 0;
    /// (VELOCITY CODE = 0)
    struct {
        /// the sequence number (1 to 51) of the mask values set in the PRN mask
        double PRN_mask_number = 0;
        /// an indicator that associates the long-term corrections for the ith satellite with the ephemeris data broadcast by that satellite
        double IOD_i = 0;
        /// for satellite i, the ephemeris correction for the x axis.
        double x_i = 0;
        /// for satellite i, the ephemeris correction for the y axis.
        double y_i = 0;
        /// for satellite i, the ephemeris correction for the z axis.
        double z_i = 0;
        /// for satellite i, the ephemeris correction for the x axis.
        double a_i = 0;
    }type_25_zero[2];
    /// an indicator that associates the correction data with a PRN mask
    int IODP = 0;
    std::string spare;
    /// (VELOCITY CODE = 1)
    struct {
        /// an indicator of the message format broadcast (Table B-48 and Table B-49).
        int Velocity_Code_1 = 0;
        /// the sequence number (1 to 51) of the mask values set in the PRN mask
        double PRN_mask_number = 0;
        /// an indicator that associates the long-term corrections for the ith satellite with the ephemeris data broadcast by that satellite
        double IOD_i = 0;
        /// for satellite i, the ephemeris correction for the x axis.
        double x_i = 0;
        /// for satellite i, the ephemeris correction for the y axis.
        double y_i = 0;
        /// for satellite i, the ephemeris correction for the z axis.
        double z_i = 0;
        /// for satellite i, the ephemeris time correction.
        double a_i_f0 = 0;
        /// for satellite i, ephemeris velocity correction for x axis.
        double v_x_i = 0;
        /// for satellite i, ephemeris velocity correction for y axis.
        double v_y_i = 0;
        /// for satellite i, ephemeris velocity correction for z axis.
        double v_z_i = 0;
        /// for satellite i, rate of change of the ephemeris time correction.
        double a_i_f1 = 0;
        /// the time of applicability of the parameters δxi, δyi, δzi, δai,f0, δx˙i, δy˙i, δz˙i and δai,f1, expressed in seconds after midnight of the current day.
        double t_i_LT = 0;
        /// an indicator that associates the correction data with a PRN mask.
        int IODP = 0;
    }type_25_one;
}message_type_25;

/// Type 26 Ionospheric delay message
typedef struct {
    /// the number identifying the ionospheric band as defined in Table B-30
    int IGP_band_identifier = 0;
    /// the identifier of the IGP block. The IGP blocks are defined by dividing into groups of 15 IGPs
    /// the sequence of IGPs within an IGP band mask which have IGP mask values of “1”. The IGP blocks
    /// are numbered in an order of IGP mask value transmission, starting with “0”.
    int IGP_block_identifier = 0;
    struct {
        /// an estimate of the delay induced for a signal at 1 575.42 MHz if it traversed the ionosphere vertically at the IGP.
        double IGP_vertical_delay_estimate = 0;
        /// an indicator that defines the σ2i,GIVE as described in Table B-33
        double GIVEI_i = 0;
    }grid_point[15];
    /// an indication of when the kth IGP band mask changes
    int IODI_k = 0;
    std::string spare;
}message_type_26;

/// Type 27 SBAS service message
typedef struct {
    /// an indication of a change of the service provided in the region
    int IODS = 0;
    /// the number of different Type 27 SBAS service messages being broadcast. (Value is coded with an offset of 1.)
    int Number_of_service_messages = 0;
    /// a sequential number identifying the message within the currently broadcast set of Type 27 messages (from 1 to number of service messages, coded with an offset of 1).
    int Service_message_number = 0;
    /// the number of service regions for which coordinates are broadcast in the message
    int Number_of_regions = 0;
    /// an indication of a message precedence if two messages define overlapping regions. The message with a higher
    /// value of priority code takes precedence. If priority codes are equal, the message with the lower δUDRE takes precedence.
    int Priority_code = 0;
    /// an indication of regional UDRE degradation factor (δUDRE) applicable at locations inside any region defined in the message, in accordance with Table B-36
    int UDRE_indicator_inside = 0;
    /// an indication of regional UDRE degradation factor (δUDRE) applicable at locations outside all regions defined in all current Type 27 messages, in accordance with Table B-36
    int UDRE_indicator_outside = 0;
    struct {
        /// the latitude of one corner of a region
        double Coordinate_1_latitude = 0;
        /// the longitude of one corner of a region
        double Coordinate_1_longitude = 0;
        /// the latitude of one corner of a region
        double Coordinate_2_latitude = 0;
        /// the longitude of one corner of a region
        double Coordinate_2_longitude = 0;
    }regions[5];
    /// an indication of whether a region is a triangle or quadrangle "0 = triangle" "1 = quadrangle"
    int Region_shape = 0;
    std::string spare;
}message_type_27;

/// Type 28 clock-ephemeris covariance matrix
typedef struct {
    /// an indicator that associates the correction data with a PRN mask
    int IODP = 0;
    struct {
        /// the sequence number (1 to 51) of the mask values set in the PRN mask
        int PRN_mask_number = 0;
        /// A term to compute the scale factor used to code the Cholesky factorization elements
        int Scale_exponent = 0;
        int E1_1 = 0;
        int E2_2 = 0;
        int E3_3 = 0;
        int E4_4 = 0;
        int E1_2 = 0;
        int E1_3 = 0;
        int E1_4 = 0;
        int E2_3 = 0;
        int E2_4 = 0;
        int E3_4 = 0;
    }type_28[2];
}message_type_28;

#endif //SBASMESSAGETYPE_H
