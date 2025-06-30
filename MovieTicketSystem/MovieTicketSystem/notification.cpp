#include "notification.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

void showNotification(const std::string& message) {
#ifdef _WIN32
    MessageBoxA(NULL, message.c_str(), "Notification", MB_OK | MB_ICONINFORMATION);
#else
    std::cout << "\n*** NOTIFICATION: " << message << " ***\n\n";
#endif
}
