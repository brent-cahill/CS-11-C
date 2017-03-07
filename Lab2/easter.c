#include <stdio.h>
#define CENTURY 100
#define MIN_YEAR 1582
#define MAX_YEAR 39999


int main(void)
{
    int year;
    int date;
    int calculate_Easter_date(int year);
    while (scanf("%d", &year) != EOF)
    {
        date = calculate_Easter_date(year);

        if(date == 0)
        {
            fprintf(stderr, "Error: Year is out of range\n");
        }
        
        else if(date < 0)
        {
            date *= -1;
            fprintf(stdout, "%d - March %d\n", year, date);
        }
        else
        {
            fprintf(stdout, "%d - April %d\n", year, date);
        }
    }
}

int calculate_Easter_date(int year)
{
    int goldYear; /* the current year of the Metonic cycle */
    int currentCentury; /* current century */
    int leapYear; /* number of skipped leap years */
    int moon; /* a correction factor for the moon's orbit */
    int sun; /* value to find a Sunday in March */
    int epact; /* specifies when a full moon occurs */
    int calFullMoon; /* the day in March when the full moon occurs */
    int easter;

    if (year < MIN_YEAR || year > MAX_YEAR)
    {
        return 0;
    }

    /*finding which year 'year' is in the Metonic Cycle*/
    goldYear = (year % 19) + 1;
    currentCentury = (year / CENTURY) + 1; /*finding the current century*/
    /*the number of skipped leap years*/
    leapYear = (3 * currentCentury / 4) - 12;
    /*correction facor for the moon's orbit*/
    moon = ((8 * currentCentury + 5) / 25) - 5;
    /*intermediate value to help find the Sunday in March*/
    sun = ((5 * year) / 4) - leapYear - 10; 
    epact = (((11 * goldYear) + 20 + moon - leapYear) % 30);
    if(((epact == 25) && (goldYear > 11)) || (epact == 24))
    {
        epact++;
    }
    /*March 'calFullMoon' is when a full moon occurs*/
    calFullMoon = 44 - epact;
    if(calFullMoon < 21)
    {
        calFullMoon += 30;
    }
    /*the Sunday after a full moon*/
    easter = calFullMoon + 7 - ((sun + calFullMoon) % 7);

    if(easter > 31)
    {
        /*for the main function, this will mean that these
        values are in April*/
        easter -= 31;
    }
    else
    {
        /*for the main function, this will mean that the
        absolute values of these values are in March*/
        easter = 0 - easter;
    }

    return easter;
}
