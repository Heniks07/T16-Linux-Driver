# T16-Linux-Driver
User space Drivers for the T16 Wired Gaming Mouse

# Usage

1. Download the Executable from the [Release Page](https://github.com/Heniks07/T16-Linux-Driver/releases) and put it in your `/usr/bin/` directory
2. Download [Service file](https://github.com/Heniks07/T16-Linux-Driver/blob/main/MouseDriver.service) and put it in your `/etc/systemd/system/` directory
```
chmod +x /usr/bin/mouseDriver          #make the mouseDriver file executable
systemctl daemon-reload                #reload the systemd daemon
systemctl start MouseDriver.service    #starts the service
systemctl enable MouseDriver.service   #(optional) starts the service at system start
```

# Build

To compile the code yourself download the Source code. Then unpack the `.zip` or `.tar.gz` file and execute 
```
gcc -o mouseDriver mouseDriver.c -lusb-1.0
```
