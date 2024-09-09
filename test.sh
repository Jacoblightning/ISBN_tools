#!/usr/bin/env bash

set -e

echo "Testing random ISBN 1000 times."
for (( i = 0; i < 1000; i++ )); do
    rand=$($1 -r)
    $1 -c "$rand" || (echo "Rand failed with ISBN: $rand" && false)
    echo "ISBN: $rand Passed."
done

