#ifndef RDE2013_H
#define RDE2013_H

#include <libusb-1.0/libusb.h>
#include <stdexcept>

// RAII Style, noncopyable, singleton wrapper for needed libusb functionality

enum class Command {TURN_WHEEL_LIGHT_ON, TURN_WHEEL_LIGHT_OFF, TURN_LOGO_LIGHT_ON, TURN_LOGO_LIGHT_OFF};

class RDE2013
{
private:
    explicit RDE2013();
    RDE2013(const RDE2013 &) {}
    RDE2013& operator=(const RDE2013 &) {}
    ~RDE2013();

    void sendCommand(unsigned char * const command);

    const int usb_interface = 0;
    libusb_context *lusb_context;
    libusb_device_handle *dev_handle;
    bool kernelDriverWasAttached;

public:
    static RDE2013 &getInstance();
    void sendCommand(const Command &command);
};

#endif // RDE2013_H
