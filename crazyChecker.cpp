#include <string>

auto isAfraid(std::string day, int number) -> bool {
    if (day == "Monday")
        return number == 12;

    if (day == "Tuesday")
        return number > 95;

    if (day == "Wednesday")
        return number == 34;

    if (day == "Thursday")
        return number == 0;

    if (day == "Friday")
        return (number % 2) - 1;

    if (day == "Saturday")
        return number == 56;

    if (day == "Sunday")
        return abs(number) == 666;

    return false;
}
