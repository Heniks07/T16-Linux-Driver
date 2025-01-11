# T16-Linux-Driver
User space Drivers for the T16 Wired Gaming Mouse

# Usage

1. Put the [Executable](https://github.com/Heniks07/T16-Linux-Driver/releases) in your `/usr/bin/` directory
2. Download [Service file](https://github.com/Heniks07/T16-Linux-Driver/blob/main/MouseDriver.service) and put it in your `/etc/systemd/system/` directory
3. Reload systemd by executing `systemctl daemon-reload` (Might require elevated privileges)
4. Start the service by executing `systemctl start MouseDriver.service` (Might require elevated privileges)
5. (Optional) Enable the service to start at system start by executing `systemctl enable MouseDriver.service` (Might require elevated privileges)
