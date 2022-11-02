#include <iostream>
#include <string>

// Date
class DateTime
{
private:
    int day, month, year, hour, minute, second;

public:
    // Constructors
    DateTime() : day(0), month(0), year(0), hour(0), minute(0), second(0) {}
    DateTime(std::string s, std::string day_delimiter, std::string part_delimiter, std::string time_delimiter);
    DateTime(int d, int m, int y, int h, int min, int s)
    {
        day = d;
        month = m;
        year = y;
        hour = h;
        minute = min;
        second = s;
    }

    // Interface
    void print() { 
        std::cout << day << "." << month << "." << year << " " <<
            hour << ":" << minute << ":" << second << std::endl; }
    int getDay() { return day; }
    int getMonth() { return month; }
    int getYear() { return year; }
    int getHour() { return hour; }
    int getMinute() { return minute; }
    int getSecond() { return second; }
    int TtoS() { return ((day*24 + hour)*60 + minute)*60 + second; }

    // Operators
    bool operator > (const DateTime &d);
    bool operator < (const DateTime &d);
    bool operator == (const DateTime &d);
    bool operator != (const DateTime &d);

    DateTime &operator ++ ();
    DateTime operator ++ (int);
    DateTime &operator -- ();
    DateTime operator -- (int);
    DateTime operator + (int dif);
    DateTime operator - (int dif);

    int operator - (const DateTime &d);

    int operator [] (int index);

    friend std::ostream &operator << (std::ostream &output, DateTime &d);
};

DateTime::DateTime(std::string s, std::string day_delimiter,std::string part_delimiter ,std::string time_delimiter)
{ // rozdelim datum day delimiter month delimiter year
    int pos = 0;
    int datetime[6] = {0, 0, 0, 0, 0, 0};
    int counter = 0;
    pos = s.find(part_delimiter);
    std::string date = s.substr(0, pos);
    std::string time = s.substr(pos+1);

    for (int i = 0; i < 2; i++) {
        if ((pos = date.find(day_delimiter)) == std::string::npos) {
            std::cout << "Nesprávne zadané hodnoty v dátume!";
            return;
        }
        datetime[counter] = std::stoi(date.substr(0, pos));
        date.erase(0, pos + day_delimiter.length());
        counter++;
    }
    datetime[2] = std::stoi(date);
    counter++;

    for (int i = 0; i < 2; i++) {
        if ((pos = time.find(time_delimiter)) == std::string::npos) {
            std::cout << "Nesprávne zadané hodnoty v čase!";
            return;
        }
        datetime[counter] = std::stoi(time.substr(0, pos));
        time.erase(0, pos + time_delimiter.length());
        counter++;
    }
    datetime[5] = std::stoi(time);
    day = datetime[0];
    month = datetime[1];
    year = datetime[2];
    hour = datetime[3];
    minute = datetime[4];
    second = datetime[5];
}

// Operators //////////////////////////////////////////////////////////////////////////////////////////////////

bool DateTime::operator > (const DateTime &d) {
    if (year > d.year) { return true; }
    if (year < d.year) { return false; }
    if (month > d.month) {return true; }
    if (month < d.month) { return false; }
    if (day > d.day) { return true; }
    if (day < d.day) { return false; }
    if (hour > d.hour) { return true; }
    if (hour < d.hour) { return false; }
    if (minute > d.minute) { return true; }
    if (minute < d.minute) { return false; }
    if (second > d.second) { return true; }
    if (second < d.second) { return false; }
    return false;
}

bool DateTime::operator < (const DateTime &d) {
    if (year < d.year) { return true; }
    if (year > d.year) { return false; }
    if (month < d.month) { return true; }
    if (month > d.month) {return false; }
    if (day < d.day) { return true; }
    if (day > d.day) { return false; }
    if (hour < d.hour) { return true; }
    if (hour > d.hour) { return false; }
    if (minute < d.minute) { return true; }
    if (minute > d.minute) { return false; }
    if (second < d.second) { return true; }
    if (second > d.second) { return false; }
    return false;
}

bool DateTime::operator == (const DateTime &d) {
    return (year == d.year && 
        month == d.month && 
        day == d.day && 
        hour == d.hour && 
        minute == d.minute && 
        second == d.second);
}

bool DateTime::operator != (const DateTime &d) {
    return year != d.year || 
        month != d.month || 
        day != d.day || 
        hour != d.hour || 
        minute != d.minute || 
        second != d.second;
}

DateTime &DateTime::operator ++ ()
{
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    second++;
    if (second == 60) { 
        second = 0;
        minute++;
        if (minute == 60) {
            minute = 0;
            hour++;
            if (hour == 24) {
                hour = 0;
                day++;
                if (day == (daysInMonth[month - 1] + 1)) {
                    day = 1;
                    month++;
                    if (month == 13) {
                        month = 1;
                        year++;
                    }
                }
            }
        }
    }
    return *this;
}

DateTime DateTime::operator ++ (int) 
{
    DateTime org = *this;
    ++(*this);
    return org;
}

DateTime &DateTime::operator -- ()
{
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    second--;
    if (second == -1) { 
        second = 59;
        minute--;
        if (minute == -1) {
            minute = 59;
            hour--;
            if (hour == -1) {
                hour = 23;
                day--;
                if (day == 0) {
                    month--;
                    if (month == 0) {
                        month = 12;
                        year--;
                    }
                    day = daysInMonth[month - 1];
                }
            }
        }
    }
    return *this;
}

DateTime DateTime::operator -- (int) 
{
    DateTime org = *this;
    --(*this);
    return org;
}

    // Veľmi neefektívne, treba opraviť ak budeme pokračovať
DateTime DateTime::operator + (int dif) {
    DateTime sum = *this;
    for (int i = 0; i < dif; i++) {
        ++sum;
    }
    return sum;
}

DateTime DateTime::operator - (int dif) {
    DateTime sum = *this;
    for (int i = 0; i < dif; i++) {
        --sum;
    }
    return sum;
}
    // -----------------------------------------------------

int DateTime::operator - (const DateTime &d) {
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int months = ((year-d.year) * 12 + (month-d.month));

    // Add full years
    int result = ( months / 12 ) * 365 * 24 * 60 * 60;
    
    // Add months
    months %= 12;
    int m = d.month;
    int days = 0;
    for (int i = 0; i < months; i++) {
        days += daysInMonth[m-1];
        (++m) %= 12;
    }

    // Add days
    result += (days + (day - d.day)) * 24 * 60 * 60;
    // Add hours
    result += (hour - d.hour) * 60 * 60;
    // add Minutes
    result += (minute - d.minute) * 60;
    // Add seconds
    result += second - d.second;
    return result;
}

int DateTime::operator[] (int index) {
    if (index == 0) { return second; }
    if (index == 1) { return minute; }
    if (index == 2) { return hour; }
    if (index == 3) { return day; }
    if (index == 4) { return month; }
    if (index == 5) { return year; }
    return -1;
}

std::ostream &operator << (std::ostream &output, DateTime &d) {
    output << d.day << "." << d.month << "." << d.year << " " <<
        d.hour << ":" << d.minute << ":" << d.second;
    return output;
}

int main(){ 
    DateTime dt1("31.12.2022 23:58:56", ".", " ", ":");
    DateTime dt2("1.1.2023 0:1:56", ".", " ", ":");

    std::cout << dt1 << std::endl;
    std::cout << dt2 << std::endl;
    int dt3 = dt2 - dt1;
    std::cout << dt3 << std::endl;

}