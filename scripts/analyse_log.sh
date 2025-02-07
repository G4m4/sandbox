#!/usr/bin/env bash

# If having issues on the first execution line of this script,
# please make sure you did not introduce DOS line endings!

set -e
#~set -x

echo "Analysing log"

grep -e "warning:" -e "should add" -e "should remove" -i $1 | tee $2

if [ -s $2 ]; then
    warnings_count=$(cat $2 | wc -l)
    echo "Found $warnings_count warning(s)"
    exit 1
else
    echo "No warnings in build."
    exit
fi
