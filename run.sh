#!/bin/bash
# Manage Shashank Lib

usage() {
  echo "Usage: $0 (build|rebuild|clean|test)"
}

clean() {
  echo "Cleaning up..."
  rm -rf build/*
}

build() {
  echo "Building Shashank Library..."
  cd build
  cmake ..
  make
}

rebuild() {
  clean
  build
}

tester() {
  rebuild
  make test
}


if [ $# -ne 1 ]; then
  usage
  exit 1
fi

case $1 in
  "build")
    build
    ;;

  "rebuild")
    rebuild
    ;;

  "clean")
    clean
    ;;

  "test")
    tester
    ;;

  *)
    usage
    exit 1
    ;;
esac

