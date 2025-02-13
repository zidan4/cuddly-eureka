#include <stdio.h>

int main() {
    int inputMonth, inputYear;
    int day, i, startingColumn;
    int daysInMonth;
    int firstDay; // Day of week for the 1st of the month

    // Array for number of days in each month (index 1 = January, etc.)
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Prompt user for input
    printf("Enter month and year (MM YYYY): ");
    scanf("%d %d", &inputMonth, &inputYear);

    // Adjust for leap year in February
    if (inputMonth == 2) {
        if ((inputYear % 400 == 0) || ((inputYear % 4 == 0) && (inputYear % 100 != 0)))
            days[2] = 29;
    }
    daysInMonth = days[inputMonth];

    // For Zeller's Congruence, treat January and February as months 13 and 14 of the previous year.
    int m = inputMonth;
    int y = inputYear;
    if (m < 3) {
        m += 12;
        y -= 1;
    }
    int K = y % 100;
    int J = y / 100;

    // Zeller's Congruence formula:
    // 0 = Saturday, 1 = Sunday, 2 = Monday, ..., 6 = Friday.
    firstDay = (1 + (13 * (m + 1)) / 5 + K + (K / 4) + (J / 4) + 5 * J) % 7;

    // Adjust so that 0 = Sunday, 1 = Monday, ..., 6 = Saturday.
    // If firstDay is 1 (Sunday), we want startingColumn = 0.
    startingColumn = (firstDay + 6) % 7;

    // Print the calendar header
    printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    // Print initial spaces for the first week
    for (i = 0; i < startingColumn; i++) {
        printf("     ");
    }

    // Print the days of the month
    for (day = 1; day <= daysInMonth; day++) {
        printf("%5d", day);
        startingColumn++;
        if (startingColumn % 7 == 0) {
            printf("\n");
        }
    }
    if (startingColumn % 7 != 0) {
        printf("\n");
    }

    return 0;
}

