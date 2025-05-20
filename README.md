# T16-Linux-Driver
User space Drivers for the T16 Wired Gaming Mouse

# Limitations

At this point only two buttons can habe distinct functions. I once had gotten a third to work as well but I don't know what it was assigned to anymore and I also can't find it after clicking the reset button without thinking. Most options don't work or are registered as normal keyboard input. If you have a solution to this feel free to open an issue or pull request. The only two options that work are, forward and backward and are assigned to the upper two side buttons by default.

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
