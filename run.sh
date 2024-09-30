#!/bin/bash


# g++ Trying_to_make_it_efficient.cpp
# Specify the folder containing the files
# folder="easytests"

# # Loop through each file in the folder
# for file in "$folder"/*; do
#     # Check if it is a regular file (not a directory or special file)
#     echo "Checking file $file"
#     if [ -f "$file" ]; then
#         # Copy the file's contents into clauses.txt
#         cat $file > clauses.txt
        
#         # Run the program ./a.out
#         ./a.out
        
#         # Optional: Add a delay between each run if needed
#         # sleep 1
#     fi
# done


folder="tests"

# Loop through each file in the folder
for file in "$folder"/*; do
    # Check if it is a regular file (not a directory or special file)
    echo "Checking file $file"
    if [ -f "$file" ]; then
        # Copy the file's contents into clauses.txt
        cat $file > clauses.txt
        
        # Run the program ./a.out
        ./a.out
        
        # Optional: Add a delay between each run if needed
        # sleep 1
    fi
done