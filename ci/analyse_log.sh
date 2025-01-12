#!/usr/bin/env bash

set -e
#~set -x

echo "Analysing log"

grep "warning:" -i build.log | tee warnings.log

if [ -s warnings.log ]; then
    warnings_count=$(cat warnings.log | wc -l)
    echo "Found $warnings_count warning(s):"
    cat warnings.log
    exit 1
else
    echo "No warnings in build."
    exit
fi
