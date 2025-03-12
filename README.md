# Docker
```shell
brew install --cask docker
```
# riscv
## Source
https://github.com/riscv-software-src/riscv-tools?tab=readme-ov-file
## Install toolchain
```shell
brew tap riscv-software-src/riscv
brew install riscv-tools conan
```

## Conan profile
```ini
[settings]
arch=riscv64
build_type=Release
compiler=gcc
compiler.cppstd=gnu17
compiler.libcxx=libstdc++11
compiler.version=14
os=Linux

[buildenv]
CC=riscv64-unknown-elf-gcc
CXX=riscv64-unknown-elf-g++
LD=riscv64-unknown-elf-ld
```

## DuoS
https://milkv.io/ru/docs/duo/getting-started/duos

### Wifi
Update config /etc/wpa_supplicant.conf
```ini
ctrl_interface=/var/run/wpa_supplicant
ap_scan=1
update_config=1

network={
    ssid="SSID"
    psk="PASS"
    key_mgmt=WPA-PSK
}
```
### Check configuration
```shell
wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant.conf
ifconfig
...
wlan0     Link encap:Ethernet  HWaddr 88:00:33:77:55:02
inet addr:192.168.0.18  Bcast:192.168.0.255  Mask:255.255.255.0
inet6 addr: fe80::fff9:a2d:98e8:bedf/64 Scope:Link
UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
RX packets:122 errors:0 dropped:0 overruns:0 frame:0
TX packets:30 errors:0 dropped:0 overruns:0 carrier:0
collisions:0 txqueuelen:1000
RX bytes:11275 (11.0 KiB)  TX bytes:2442 (2.3 KiB)
...
```
### Setup wifi on start
/mnt/system/auto.sh
```ini
interface="wlan0"
max_attempts=100
attempt=0
log_file="/var/log/auto.sh.log"

# Continuously attempt to detect if the interface exists, up to $max_attempts times
echo "start auto.sh" > "$log_file"
while [ $attempt -lt $max_attempts ]; do
    # Check if the wlan0 interface exists
    ip link show "$interface" > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        echo "$(date +'%Y-%m-%d %H:%M:%S') $interface interface exists, starting wpa_supplicant..." >> "$log_file"
        wpa_supplicant -B -i "$interface" -c /etc/wpa_supplicant.conf >> "$log_file"
        break  # Exit the loop if the interface is found
    else
        echo "$(date +'%Y-%m-%d %H:%M:%S') $interface interface not found, waiting..." >> "$log_file"
        sleep 1  # Wait for 1 second before checking again
        attempt=$((attempt + 1))  # Increment the attempt counter
    fi
done

# If the maximum number of attempts is reached and the interface still not found, output an error message
if [ $attempt -eq $max_attempts ]; then
    echo "$(date +'%Y-%m-%d %H:%M:%S') Interface $interface not found after $max_attempts attempts" >> "$log_file"
fi
```
### Setup fixed mac-address
```shell
echo "MAC_ADDR=88:00:33:77:55:02" > /mnt/system/firmware/aic8800/rwnx_settings.ini && sync
```

## Linux toolchain
```shell
sudo apt install gcc-14-riscv64-linux-gnu g++-14-riscv64-linux-gnu
```
### Conan profile
```ini
[settings]
arch=riscv64
build_type=Debug
compiler=gcc
compiler.cppstd=gnu17
compiler.libcxx=libstdc++11
compiler.version=13
os=Linux
[buildenv]
CC=riscv64-linux-gnu-gcc
CXX=riscv64-linux-gnu-g++
LD=riscv64-linux-gnu-ld
```

## Bare metal toolchain
```shell
sudo apt install gcc-riscv64-unknown-elf
```
### Conan profile
```ini
[settings]
arch=riscv64
build_type=Debug
compiler=gcc
compiler.cppstd=gnu17
compiler.libcxx=libstdc++11
compiler.version=13
os=Linux
[buildenv]
CC=riscv64-unknown-elf-gcc
CXX=riscv64-unknown-elf-g++
LD=riscv64-unknown-elf-ld
```