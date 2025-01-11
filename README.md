# T16-Linux-Driver
User space Drivers for the T16 Wired Gaming Mouse

# Usage

1. Put the [Executable](https://github.com/Heniks07/T16-Linux-Driver/releases) in your `/usr/bin/` directory
2. Download [Service file](https://github.com/Heniks07/T16-Linux-Driver/blob/main/MouseDriver.service) and put it in your `/etc/systemd/system/` directory
3. 
```
systemctl daemon-reload               #reload the systemd daemon
systemctl start MouseDriver.service   #starts the service
systemctl enable MouseDriver.service  #(optional) starts the service at system start
```

# Build

To compile the code yourself download the [Source code of the lates releas](https://github.com/Heniks07/T16-Linux-Driver/releases/tag/v1.0.0). Then unpack the `.zip` or `.tar.gz` file and execute 
```
gcc -o mouse_monitor mouse_monitor.c -lusb-1.0
```
