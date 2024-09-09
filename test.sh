#!/usr/bin/env bash

set -e

echo "Testing random ISBN 1000 times."
sleep 2
for (( i = 0; i < 1000; i++ )); do
    rand=$($1 -r)
    $1 -c "$rand" || (echo "Rand failed with ISBN: $rand" && false)
    echo "ISBN: $rand Passed."
done

echo -e "\n\n\n"

echo "Testing fixing on 1000 Random ISBNs"
sleep 2
for (( i = 0; i < 1000; i++ )); do
    rand=$($1 -r)
    badisbn=${rand%-*}
    fixed=$($1 -f "$badisbn") || (echo "Fixing failed with ISBN: $rand" && false)
    if [ "$fixed" = "$rand" ];then
      echo "ISBN: $rand Passed."
    else
      echo "ISBN: $badisbn was not fixed."
      false
    fi
done
