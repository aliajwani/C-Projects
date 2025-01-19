#!/bin/bash

#Navigate to the src directory to build the program
echo "Building gcal..."
cd src || exit 1  # Exit if src directory is not found

#Build the program using the makefile
make || exit 1

#Create the installation directory if it doesn't exist
INSTALL_DIR="$HOME/.local/bin"
mkdir -p $INSTALL_DIR

#Copy the executable to the installation directory
echo "Copying gcal to $INSTALL_DIR..."
cp gcal $INSTALL_DIR/

#Update the PATH in .bashrc to include the installation directory
if ! grep -q "$INSTALL_DIR" "$HOME/.bashrc"; then
  echo "Updating PATH in ~/.bashrc to include $INSTALL_DIR"
  echo "export PATH=\$PATH:$INSTALL_DIR" >> "$HOME/.bashrc"
  echo "PATH updated. Please restart your terminal or run 'source ~/.bashrc' to apply the changes."
else
  echo "PATH already updated."
fi


