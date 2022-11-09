/**
 * @file    : Ublox-Driver 
 * @authors : MEHMET AKSU
 * @note    : mehmet.aksu@cezeri.com
 * @date    : 10 / Mayıs / 2021
 * @code    : datetime.hpp file
 * @details : 
 */



#ifndef DATETIME_HPP
#define DATETIME_HPP

#include <iosfwd>
#include "rtklib.h"

enum TimeZone
{
    locale,
    utc,
};

enum RelativeDay
{
    yesterday,
    today,
    tomorrow,
    now
};

enum class WeekDay
{
    Sunday = 1,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};


class DateTime {
private:
    int m_day{};
    int m_mon{};
    int m_year{};
    int m_hour{};
    int m_min{};
    int m_sec{};
    double m_fsec{};
    time_t m_epoch_time{};
    RelativeDay m_relative_day{};
    TimeZone m_time_zone{};

private:
    void set_date (struct tm* tm);
    void set_datetime (struct tm* tm);
    char* print_date (char* buff) const;
    char* print_datetime (char* buff) const;

    [[nodiscard]] WeekDay get_weekday () const;

    inline static constexpr const char* const p_days[] = {"", "Pazar", "Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi"};
    inline static constexpr const char* const p_months[] = {"", "Ocak", "Subat", "Mart", "Nisan", "Mayis", "Haziran", "Temmuz", "Agustos", "Eylul", "Ekim", "Kasim", "Aralik"};

    inline static constexpr auto SEC_PER_MIN  = 60;
    inline static constexpr auto SEC_PER_HOUR = SEC_PER_MIN  * 60;
    inline static constexpr auto SEC_PER_DAY  = SEC_PER_HOUR * 24;

public:

    explicit DateTime(RelativeDay = today, TimeZone = locale);

    explicit DateTime(int day, int mon, int year, int hour, int min, int sec, int fsec = 0);
    explicit DateTime(int day, int mon, int year);

    explicit DateTime (const gtime_t& gtime);

    [[nodiscard]] int get_day () const;
    [[nodiscard]] std::string get_monthName () const;
    [[nodiscard]] int get_month () const;
    [[nodiscard]] int get_year () const;
    [[nodiscard]] std::string get_WeekDay () const;
    [[nodiscard]] int get_dayOfWeek () const;
    [[nodiscard]] int get_hour () const;
    [[nodiscard]] int get_minute () const;
    [[nodiscard]] int get_second () const;
    [[nodiscard]] double get_fsecond () const;
    [[nodiscard]] double get_secondsOfDay () const;
    [[nodiscard]] double get_secondsOfWeek () const;

    bool operator== (const DateTime& other) const;
    bool operator!= (const DateTime& other) const;

    friend std::ostream& operator<< (std::ostream& os, const DateTime& date_time);

};

#endif /* DATETIME_HPP */