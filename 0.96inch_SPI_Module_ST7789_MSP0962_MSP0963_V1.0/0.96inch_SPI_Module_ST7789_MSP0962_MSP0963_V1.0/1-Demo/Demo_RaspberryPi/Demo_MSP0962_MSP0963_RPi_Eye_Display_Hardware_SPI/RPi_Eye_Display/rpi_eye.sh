#!/bin/bash

if [ $(id -u) -ne 0 ]; then
  echo "Installer must be run as root."
  echo "Try 'sudo bash $0'"
  exit 1
fi

cat /proc/cpuinfo | grep -q "Model" | grep -q "Raspberry Pi 4"
RESULT=$?
if [ $RESULT ]; then
  # Verify this is Raspbian Desktop OS (X11 should exist)
  if [ ! -d "/usr/bin/X11" ]; then
    echo "Target system is Pi 4/400/CM4 but this appears to"
    echo "be a \"Lite\" OS. \"Desktop\" OS is required."
    echo "it will exit!"
    sleep 3
    exit 0
  fi
else
  # Verify this is Raspbian Lite OS (X11 should NOT exist)
  if [ -d "/usr/bin/X11" ]; then
    echo "Target system is not Pi 4/400/CM4 yet this appears to"
    echo "be a \"Desktop\" OS. \"Lite\" OS (Legacy) is required."
    echo "it will exit!"
    sleep 3
    exit 0
  fi
fi

# START INSTALL ------------------------------------------------------------
# All selections are validated at this point...

# Given a filename, a regex pattern to match and a replacement string,
# perform replacement if found, else append replacement to end of file.
# (# $1 = filename, $2 = pattern to match, $3 = replacement)
reconfig() {
  grep $2 $1 >/dev/null
  if [ $? -eq 0 ]; then
    # Pattern found; replace in file
    sed -i "s/$2/$3/g" $1 >/dev/null
  else
    # Not found; append (silently)
    echo $3 | sudo tee -a $1 >/dev/null
  fi
}

# Same as above, but appends to same line rather than new line
reconfig2() {
  grep $2 $1 >/dev/null
  if [ $? -eq 0 ]; then
    # Pattern found; replace in file
    sed -i "s/$2/$3/g" $1 >/dev/null
  else
    # Not found; append to line (silently)
    sed -i "s/$/ $3/g" $1 >/dev/null
  fi
}

echo
echo "Starting installation..."
echo "Updating package index files..."
sudo apt-get update

echo "Installing Python libraries..."
sudo apt-get install -y python3-pip python3-dev python3-pil python3-smbus libatlas-base-dev
sudo pip3 install numpy pi3d svg.path rpi-gpio adafruit-blinka adafruit-circuitpython-ads1x15

echo "Installing code and data"
wget --spider -q -o /dev/null --tries=1 -T 10 https://github.com
if [ $? -eq 0 ]; then
   sudo curl -LO https://github.com/adafruit/Pi_Eyes/archive/master.zip
   if [ $? -eq 0 ]; then
     sudo unzip -o master.zip
   else
     sudo cp -f ./src/RPi_Eyes.zip ./
     sudo unzip -o RPi_Eyes.zip
  fi
else
   sudo cp -f ./src/RPi_Eyes.zip ./
   sudo unzip -o RPi_Eyes.zip
fi
sudo cp -rf Pi_Eyes-master /home/RPi_Eyes

# CONFIG -------------------------------------------------------------------

echo "Configuring system..."

if [ $RESULT ]; then
  # Make desktop system to boot to console (from raspi-config script):
  systemctl set-default multi-user.target
  ln -fs /lib/systemd/system/getty@.service /etc/systemd/system/getty.target.wants/getty@tty1.service
  rm -f /etc/systemd/system/getty@tty1.service.d/autologin.conf

  # Pi3D requires "fake" KMS overlay to work. Check /boot/config.txt for
  # vc4-fkms-v3d overlay present and active. If so, nothing to do here,
  # module's already configured.
  grep '^dtoverlay=vc4-fkms-v3d' /boot/config.txt >/dev/null
  if [ $? -ne 0 ]; then
    # fkms overlay not present, or is commented out. Check if vc4-kms-v3d
    # (no 'f') is present and active. That's normally the default.
    grep '^dtoverlay=vc4-kms-v3d' /boot/config.txt >/dev/null
    if [ $? -eq 0 ]; then
      # It IS present. Comment out that line for posterity, and insert the
      # 'fkms' item on the next line.
      sed -i "s/^dtoverlay=vc4-kms-v3d/#&\ndtoverlay=vc4-fkms-v3d/g" /boot/config.txt >/dev/null
    else
      # It's NOT present. Silently append 'fkms' overlay to end of file.
      echo dtoverlay=vc4-fkms-v3d | sudo tee -a /boot/config.txt >/dev/null
    fi
  fi

  sudo cp -f ./src/xorg.conf /etc/X11/

fi

# Disable overscan compensation (use full screen):
raspi-config nonint do_overscan 1

# Dedicate 128 MB to the GPU:
sudo raspi-config nonint do_memory_split 128

# HDMI settings for Pi eyes
reconfig /boot/config.txt "^.*hdmi_force_hotplug.*$" "hdmi_force_hotplug=1"
reconfig /boot/config.txt "^.*hdmi_group.*$" "hdmi_group=2"
reconfig /boot/config.txt "^.*hdmi_mode.*$" "hdmi_mode=87"
reconfig /boot/config.txt "^.*hdmi_cvt.*$" "hdmi_cvt=1280 720 60 1 0 0 0"

# Enable I2C for ADC
#if [ $INSTALL_ADC -ne 0 ]; then
  raspi-config nonint do_i2c 0
#fi

# Enable SPI and install fbx2 and eyes.py,
  raspi-config nonint do_spi 0

  # Enable SPI1 by adding overlay to /boot/config.txt
  reconfig /boot/config.txt "^.*dtparam=spi1.*$" "dtparam=spi1=on"
  reconfig /boot/config.txt "^.*dtoverlay=spi1.*$" "dtoverlay=spi1-3cs"

  # Adjust spidev buffer size to 8K (default is 4K)
  reconfig2 /boot/cmdline.txt "spidev\.bufsiz=.*" "spidev.bufsiz=8192"

  # Auto-start fbx2 on boot
  grep fbx2 /etc/rc.local >/dev/null
  if [ $? -eq 0 ]; then
    # fbx2 already in rc.local, but make sure correct:
    sed -i "s/^.*fbx2.*$/\/home\/RPi_Eyes\/fbx2 -i \&/g" /etc/rc.local >/dev/null
  else
    # Insert fbx2 into rc.local before final 'exit 0'
    sed -i "s/^exit 0/\/home\/RPi_Eyes\/fbx2 -i \&\\nexit 0/g" /etc/rc.local >/dev/null
  fi

  # Auto-start eyes.py on boot
  grep eyes.py /etc/rc.local >/dev/null
  if [ $? -eq 0 ]; then
    # eyes.py already in rc.local, but make sure correct:
    if [ $RESULT ]; then
      sed -i "s/^.*eyes.py.*$/cd \/home\/RPi_Eyes;xinit \/usr\/bin\/python3 eyes.py --radius 240 \:0 \&/g" /etc/rc.local >/dev/null
    else
      sed -i "s/^.*eyes.py.*$/cd \/home\/RPi_Eyes;python3 eyes.py --radius 240 \&/g" /etc/rc.local >/dev/null
    fi
  else
    # Insert eyes.py into rc.local before final 'exit 0'
    if [ $RESULT ]; then
      sed -i "s/^exit 0/cd \/home\/RPi_Eyes;xinit \/usr\/bin\/python3 eyes.py --radius 240 \:0 \&\\nexit 0/g" /etc/rc.local >/dev/null
    else
      sed -i "s/^exit 0/cd \/home\/RPi_Eyes;python3 eyes.py --radius 240 \&\\nexit 0/g" /etc/rc.local >/dev/null
    fi
  fi

cat /proc/cpuinfo | grep -q "Model" | grep -q "Raspberry Pi Zero"
RESULT1=$?

if [ $RESULT1 -eq 0 ]; then
  reconfig /boot/config.txt "^.*dtoverlay=dwc2.*$" "dtoverlay=dwc2"
  grep "modules-load=dwc2,g_ether" /boot/cmdline.txt >/dev/null
  if [ $? -ne 0 ]; then
    # Insert ethernet gadget into config.txt after 'rootwait'
    sed -i "s/rootwait/rootwait modules-load=dwc2,g_ether/g" /boot/cmdline.txt >/dev/null
  fi
fi

# PROMPT FOR REBOOT --------------------------------------------------------

echo "Done."
echo "Settings take effect on next boot."
echo "Reboot started..."
sleep 2
reboot
exit 0
