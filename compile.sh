#!/usr/bin/env bash

source "./.env"
# Regex Tah les ouf
if [[ $PROJECT_NAME =~ [^a-zA-Z0-9_] ]]; then
  echo "error : PROJECT_NAME contains a forbidden symbol"
  exit 1
fi


# Prompt user to choose between TUI and GUI
read -p "Do you want to use tui or gui? (write tui or gui): " UI_CHOICE

if [[ $UI_CHOICE == "tui" ]]; then
  cp src/main.cpp.tui src/main.cpp
elif [[ $UI_CHOICE == "gui" ]]; then
  cp src/main.cpp.gui src/main.cpp
else
  echo "Invalid choice. Please write 'tui' or 'gui'."
  exit 1
fi



mkdir -p "${PROJECT_DIR}/build"

mkdir -p output/debug/ 

cmake -B "${PROJECT_DIR}/build" > output/debug/cmake.log

if [ $? -ne 0 ]; then
  echo "Compilation failed at Cmake\n"
  cat output/debug/cmake.log
  exit 1
fi

make -C "${PROJECT_DIR}/build" > output/debug/make.log

if [ $? -ne 0 ]; then
  echo "Compilation failed at Make\n"
  cat output/debug/cmake.log
  exit 1
fi

if [ $? -eq 0 ]; then
    echo "Compilation successful. Executable is located at: ${PROJECT_DIR}/${PROJECT_NAME}"
else
    echo "Compilation failed."
    exit 1
fi

./$PROJECT_NAME
