/**
 * @file    : Ublox-Driver 
 * @authors : MEHMET AKSU
 * @note    : mehmet.aksu@cezeri.com
 * @date    : 10 / Mayıs / 2021
 * @code    : datetime.cpp file
 * @details : 
 */


#include <ctime>
#include <iostream>
#include "datetime.hpp"

DateTime::DateTime (RelativeDay relative_day, TimeZone time_zone) : m_relative_day(relative_day), m_time_zone(time_zone)
{
    m_epoch_time = std::time(nullptr);

    switch (m_relative_day)
    {
        case yesterday:
        {
            break;
        }

        case today:
        {
            auto tm = localtime(&m_epoch_time);
            set_date(tm);
            break;
        }

        case tomorrow:
        {
            break;
        }

        case now:
        {
            switch (m_time_zone)
            {
                case locale:
                {
                    auto tm = std::localtime(&m_epoch_time);
                    set_datetime(tm);
                    break;
                }
                case utc:
                {
                    auto tm = std::gmtime(&m_epoch_time);
                    set_datetime(tm);
                    break;
                }
            }
            break;
        }
    }
}

DateTime::DateTime (int day, int mon, int year, int hour, int min, int sec, int fsec)
: m_day(day), m_mon(mon), m_year(year), m_hour(hour), m_min(min), m_sec(sec), m_fsec(fsec*1e-9)
{
    m_relative_day = now;
}

DateTime::DateTime (int day, int mon, int year) : m_day(day), m_mon(mon), m_year(year)
{
    m_relative_day = now;
}

DateTime::DateTime (const gtime_t& gtime)
{
    m_epoch_time   = gtime.time;
    m_fsec         = gtime.sec;
    m_relative_day = now;
    auto tm = std::gmtime(&m_epoch_time);
    set_datetime(tm);
}

void DateTime::set_date (struct tm * tm)
{
    m_day  = tm->tm_mday;
    m_mon  = tm->tm_mon  + 1;
    m_year = tm->tm_year + 1900;
}

void DateTime::set_datetime (struct tm * tm)
{
    m_day  = tm->tm_mday;
    m_mon  = tm->tm_mon  + 1;
    m_year = tm->tm_year + 1900;
    m_hour = tm->tm_hour;
    m_min  = tm->tm_min;
    m_sec  = tm->tm_sec;
}

char* DateTime::print_date (char* buff) const
{
    std::sprintf(buff, "%02d-%s-%04d-%s", m_day, p_months[m_mon], m_year, p_days[static_cast<int>(get_weekday())]);
    return buff;
}

char* DateTime::print_datetime (char* buff) const
{
    std::sprintf(buff, "%02d %-7s %04d %-9s %02d:%02d:%02d", m_day, p_months[m_mon], m_year, p_days[static_cast<int>(get_weekday())], m_hour, m_min, m_sec);
    return buff;
}

WeekDay DateTime::get_weekday () const
{
    constexpr int m_tabs[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

    auto day  = m_day;
    auto mon  = m_mon;
    auto year = m_year;

    year = mon < 3 ? year-1 : year;

    auto wd = static_cast<WeekDay>(((year + year / 4 - year / 100 + year / 400 + m_tabs[mon - 1] + day) % 7) + 1);
    return wd;
}

std::ostream& operator<< (std::ostream& os, const DateTime& date_time)
{
    char buff[50]{};

    switch (date_time.m_relative_day)
    {
        case now:
            date_time.print_datetime(buff);
            return os << buff;

        default:
            date_time.print_date(buff);
            return os << buff;
    }
}

int DateTime::get_day () const
{
    return m_day;
}

std::string DateTime::get_monthName () const
{
    return std::string{p_months[m_mon]};
}

int DateTime::get_month () const
{
    return m_mon;
}

int DateTime::get_year () const
{
    return m_year;
}

std::string DateTime::get_WeekDay () const
{
    return std::string{p_days[static_cast<int>(get_weekday())]};
}

int DateTime::get_hour () const
{
    return m_hour;
}

int DateTime::get_minute () const
{
    return m_min;
}

int DateTime::get_second () const
{
    return m_sec;
}

double DateTime::get_fsecond () const
{
    return m_fsec;
}

double DateTime::get_secondsOfDay () const
{
    return m_hour * 3600 + m_min * 60 + m_sec + m_fsec;
}

int DateTime::get_dayOfWeek () const
{
    return static_cast<int>(get_weekday());
}

double DateTime::get_secondsOfWeek () const
{
    return (get_dayOfWeek()-1) * SEC_PER_DAY + get_secondsOfDay();
}

bool DateTime::operator== (const DateTime& other) const
{
    return m_year == other.m_year &&
           m_mon  == other.m_mon  &&
           m_day  == other.m_day  &&
           m_hour == other.m_hour &&
           m_min  == other.m_min  &&
           m_sec  == other.m_sec;
}

bool DateTime::operator!= (const DateTime& other) const
{
    return !(*this == other);
}




