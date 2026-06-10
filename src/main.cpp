#include <fmt/core.h>

int main() {
    fmt::print("{} v{}\n", PERIPHERALOS_NAME, PERIPHERALOS_VERSION);
    fmt::print("Author: {}\n", PERIPHERALOS_AUTHOR);
    fmt::print("Platform: {}\n", PERIPHERALOS_PLATFORM);

    return 0;
}