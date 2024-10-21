#!/bin/bash

find ./TIMGE/include/TIMGE ./TIMGE/src -type f \( -name "*.hpp" -o -name "*.cpp" \) -exec awk 'NF' {} + | wc -l
