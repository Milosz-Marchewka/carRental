#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

class Date{
    int year = 0;
    int month = 0;
    int day = 0;

public:
    Date();
    Date(int, int, int);

    int getYear() const;
    int getMonth() const;
    std::string getMonthFormatted() const;
    int getDay() const;
    std::string getDayFormatted() const;
    std::string getDate() const;
    static Date today();
    static int currentYear();
    static int currentMonth();
    static int currentDay();

    void setYear(int);
    void setMonth(int);
    void setDay(int);
    void setDate(int, int, int);
    static void validateDate(Date);
    static void validateDate(int,int,int);
};

#endif // DATE_H_INCLUDED
