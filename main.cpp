#include <cstdlib>

#include "Application.h"
#include <iostream>
#include <string>

// not sure if needed
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
// end

int main() try
{
    Application app;
    app.runMainLoop();

    return EXIT_SUCCESS;
}
catch (std::exception& e)
{
    // errorMessage(e.what(), "Error! Message: " + std::string(e.what()) + "\nPress enter to exit.\n");
    return EXIT_FAILURE;
}
catch(...)
{
    // errorMessage("Unrecognised exception type.", "Error: Unrecognised exception type.\nPress enter to exit.\n");
    return EXIT_FAILURE;
}