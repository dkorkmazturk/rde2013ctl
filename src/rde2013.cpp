#include "rde2013.h"

RDE2013::RDE2013() : lusb_context(nullptr), dev_handle(nullptr), kernelDriverWasAttached(false)
{
    // Initialize libusb context
    if(libusb_init(&lusb_context) != 0)
        throw std::runtime_error("Failed to initialize libusb");

    // Set debug level of libusb [0-5]
    libusb_set_debug(lusb_context, 3);

    // Open the mouse
    dev_handle = libusb_open_device_with_vid_pid(lusb_context, 0x1532, 0x0037);
    if(dev_handle == nullptr)
        throw std::runtime_error("Could not find or open the mouse");

    // Detach kernel driver if it has already attached
    if(libusb_kernel_driver_active(dev_handle, usb_interface))
    {
        if(libusb_detach_kernel_driver(dev_handle, usb_interface) != 0)
            throw std::runtime_error("Failed to detach kernel driver");

        kernelDriverWasAttached = true;
    }

    // Claim the necessary interface of the mouse
    if(libusb_claim_interface(dev_handle, usb_interface) != 0)
        throw std::runtime_error("Failed to claim the necessary interface");
}

RDE2013::~RDE2013()
{
    libusb_release_interface(dev_handle, usb_interface);

    if(kernelDriverWasAttached)
        libusb_attach_kernel_driver(dev_handle, usb_interface);

    libusb_close(dev_handle);
    libusb_exit(lusb_context);
}

void RDE2013::sendCommand(unsigned char * const command)
{
    // Sending commands multiple times seems like works better
    for(unsigned char i = 0; i < 3; ++i)
        libusb_control_transfer(dev_handle, 0x21, 9, 0x0300, 0, command, 90, 2000);
}

RDE2013 &RDE2013::getInstance()
{
    static RDE2013 rde2013;
    return rde2013;
}

void RDE2013::sendCommand(const Command &command)
{
    if(command == Command::TURN_LOGO_LIGHT_OFF)
    {
        unsigned char command[] = {0x00, 0xff, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x01, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00};
        sendCommand(command);
    }

    else if(command == Command::TURN_LOGO_LIGHT_ON)
    {
        unsigned char command[] = {0x00, 0xff, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x01, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00};
        sendCommand(command);
    }

    else if(command == Command::TURN_WHEEL_LIGHT_ON)
    {
        unsigned char command[] = {0x00, 0xff, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00};
        sendCommand(command);
    }

    else if(command == Command::TURN_WHEEL_LIGHT_OFF)
    {
        unsigned char command[] = {0x00, 0xff, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        sendCommand(command);
    }
}
