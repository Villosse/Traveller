#!/usr/bin/env bash

source "./.env"
# Regex Tah les ouf
if [[ $PROJECT_NAME =~ [^a-zA-Z0-9_] ]]; then
  echo "error : PROJECT_NAME contains a forbidden symbol"
  exit 1
fi

new_line="project(${PROJECT_NAME})"
sed -i "5s,.*,$new_line," CMakeLists.txt

new_line="add_executable(${PROJECT_NAME} src/main.cpp)"
sed -i "24s,.*,$new_line," CMakeLists.txt

new_line="set(EXECUTABLE_OUTPUT_PATH ${PROJECT_OUTPUT_DIR})"
sed -i "27s,.*,$new_line," CMakeLists.txt

new_line="target_link_libraries(${PROJECT_NAME} Qt5::Widgets)"
sed -i "30s,.*,$new_line," CMakeLists.txt


mkdir -p "${PROJECT_OUTPUT_DIR}/build"

mkdir -p output/debug/ 

cmake -B "${PROJECT_OUTPUT_DIR}/build" > output/debug/cmake.log

if [ $? -ne 0 ]; then
  echo "Compilation failed at Cmake\n"
  cat output/debug/cmake.log
  exit 1
fi

make -C "${PROJECT_OUTPUT_DIR}/build" > output/debug/make.log

if [ $? -ne 0 ]; then
  echo "Compilation failed at Make\n"
  cat output/debug/cmake.log
  exit 1
fi

if [ $? -eq 0 ]; then
    echo "Compilation successful. Executable is located at: ${PROJECT_OUTPUT_DIR}/${PROJECT_NAME}"
else
    echo "Compilation failed."
    exit 1
fi

./$PROJECT_NAME
