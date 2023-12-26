#!/bin/bash
set -e
REPORT=$1
EXCUTION=$2
GPERFLIB=/usr/local/lib/libprofiler.so.0
function main() {
     LD_PRELOAD=$GPERFLIB CPUPROFILE=$1 $2
}
main "$@"