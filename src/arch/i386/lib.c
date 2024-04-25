#include <lib.h>

uint32_t uatoi(const char* str)
{
    uint32_t res = 0;
    const char digits[] = "0123456789";

    for (uint32_t index = 0; str[index] != '\0'; ++index) {
        res = res * 10 + str[index] - '0'; // Subtract '0' to get int value from ASCII
        
        for (uint8_t digit_index; digit_index < 10; digit_index++) {
            if (str[index] == digits[digit_index]) {
                res = res * 10 + str[index] - '0'; // Subtract '0' to get int value from ASCII
            }
        }
    }

    return res;
}