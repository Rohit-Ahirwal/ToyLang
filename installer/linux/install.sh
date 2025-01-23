#!/bin/bash

# Define installation directory
INSTALL_DIR="/usr/local/ToyLang"
BINARY_NAME="ToyLang"

# Check if the script is run as root (necessary for installing in system directories)
if [ "$(id -u)" -ne "0" ]; then
  echo "This script must be run as root (use sudo)."
  exit 1
fi

# Create the installation directory
echo "Creating installation directory at $INSTALL_DIR"
mkdir -p $INSTALL_DIR

# Copy your binary (assuming you have it ready in the current directory)
echo "Copying binary to $INSTALL_DIR"
cp $BINARY_NAME $INSTALL_DIR/

# Add the binary to PATH by modifying .bashrc (or other shell config files)
echo "Adding $INSTALL_DIR to PATH"
echo "export PATH=\$PATH:$INSTALL_DIR" >> ~/.bashrc

# Reload .bashrc to apply changes
source ~/.bashrc

# Verify the installation
echo "Installation complete!"
echo "You can now use 'ToyLang' from any terminal."

