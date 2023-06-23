#!/bin/bash

output_file="out_06_p1_Z.root"
input_files=""

for ((i=1; i<=10; i++)); do
    input_files+="06_p1_Z_E2_${i}.root "
done

command="hadd ${output_file} ${input_files}"
echo "Running command: ${command}"
eval ${command}




