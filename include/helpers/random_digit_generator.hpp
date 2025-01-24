#include <string>
#include <cstdlib>
#include <sstream>

namespace helper {
static std::string GenerateRandomDigits(int lenght)
{
    srand ( (unsigned int)time(NULL) );
    std::string randomDigits;
    for (int i = 0; i < lenght; ++i) {
        randomDigits += std::to_string(rand() % 10); // Generate digits between 0-9
    }
    return randomDigits;
}
} // namespace helper