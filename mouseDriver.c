#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <libusb-1.0/libusb.h>


#define VENDOR_ID  0x258a
#define PRODUCT_ID 0x1007

libusb_device_handle *handle;

void open_mouse(){

    handle = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
    if (!handle) {
        printf("Device not found\n");
        return;
    }

    // Detach kernel driver if already claimed
    if (libusb_kernel_driver_active(handle, 1) == 1) {
        printf("Kernel driver active, detaching...\n");
        if (libusb_detach_kernel_driver(handle, 1) != 0) {
            fprintf(stderr, "Failed to detach kernel driver\n");
            libusb_close(handle);
            libusb_exit(NULL);
            return;
        }
    }

    // Claim the first interface (0 for mouse)
    if (libusb_claim_interface(handle, 1) != 0) {
        fprintf(stderr, "Failed to claim interface\n");
        libusb_close(handle);
        libusb_exit(NULL);
        return;
    }
}


int main() {
    struct uinput_user_dev uinput_device;
    int uinput_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (uinput_fd == -1) {
        perror("Error opening uinput device");
        exit(1);
    }

    memset(&uinput_device, 0, sizeof(uinput_device));
    strncpy(uinput_device.name, "Virtual Mouse", UINPUT_MAX_NAME_SIZE);
    uinput_device.id.bustype = BUS_USB;
    uinput_device.id.vendor = 0x258a;
    uinput_device.id.product = 0x1008;
    uinput_device.id.version = 1;


    if (write(uinput_fd, &uinput_device, sizeof(uinput_device)) == -1) {
        perror("Writing uinput device");
        close(uinput_fd);
        return 1;
    }

    ioctl(uinput_fd, UI_SET_EVBIT, EV_KEY);  // Set key event type
    ioctl(uinput_fd, UI_SET_EVBIT, EV_SYN);  // Set sync event type
    ioctl(uinput_fd, UI_SET_KEYBIT, BTN_EXTRA);  // Button 1
    ioctl(uinput_fd, UI_SET_KEYBIT, BTN_TASK);   // Button 2
    ioctl(uinput_fd, UI_SET_KEYBIT, BTN_FORWARD); // Button 3

    ioctl(uinput_fd, UI_DEV_CREATE, 0);

    int r;

    r = libusb_init(NULL);
    if (r < 0) {
        fprintf(stderr, "Failed to initialize libusb\n");
        return EXIT_FAILURE;
    }

    open_mouse();

    unsigned char data[8];
    int transferred;
    printf("Listening for data...\n");

    libusb_device *dev = NULL; // Declare dev
    struct libusb_device_descriptor desc; // Declare desc

    while (1) {
        libusb_close(handle);
        handle = NULL;

        open_mouse();
        
        if(!handle)
        {
            sleep(1);
            continue;
        }
        
        struct input_event ev;


        r = libusb_interrupt_transfer(handle, 0x82, data, sizeof(data), &transferred, 0);
        if (data[1] == 0x40) {
            ev.type = EV_KEY;
            ev.code = BTN_EXTRA; // Button 1
            ev.value = 1; // Press
            write(uinput_fd, &ev, sizeof(ev));

           ev.type = EV_SYN;
           ev.code = SYN_REPORT;
           ev.value = 0;
           write(uinput_fd, &ev, sizeof(ev));

        } else if (data[1] == 0x80) {
            ev.type = EV_KEY;
            ev.code = BTN_TASK; // Button 1
            ev.value = 1; // Press
            write(uinput_fd, &ev, sizeof(ev));

           ev.type = EV_SYN;
           ev.code = SYN_REPORT;
           ev.value = 0;
           write(uinput_fd, &ev, sizeof(ev));

            
        } else if (data[1] == 0x08) {
            ev.type = EV_KEY;
            ev.code = BTN_FORWARD; // Button 1
            ev.value = 1; // Press
            write(uinput_fd, &ev, sizeof(ev));

           ev.type = EV_SYN;
           ev.code = SYN_REPORT;
           ev.value = 0;
           write(uinput_fd, &ev, sizeof(ev));

        }
        else if (data[1] == 0x00){
            ev.type = EV_KEY;
            ev.code = BTN_EXTRA; // Button 1
            ev.value = 0; // Release
            write(uinput_fd, &ev, sizeof(ev));


            ev.type = EV_KEY;
            ev.code = BTN_TASK; // Button 1
            ev.value = 0; // Release
            write(uinput_fd, &ev, sizeof(ev));

            ev.type = EV_KEY;
            ev.code = BTN_FORWARD; // Button 1
            ev.value = 0; // Release
            write(uinput_fd, &ev, sizeof(ev));

            ev.type = EV_SYN;
            ev.code = SYN_REPORT;
            ev.value = 0;
            write(uinput_fd, &ev, sizeof(ev));
        }
    }

    libusb_release_interface(handle, 1);
    libusb_close(handle);
    libusb_exit(NULL);
    return 0;
}
