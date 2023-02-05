#!/bin/bash

config_file="/home/blesson/bpxconfig.xml"

username=$( xmlstarlet sel -t -v '/config/username' "$config_file" )

pswd=$( xmlstarlet sel -t -v '/config/password' "$config_file" )

boost_home=$( xmlstarlet sel -t -v '/config/boost_home' "$config_file" )

file_name=$1
#$2=hpp_file_name

##############################
# Execute For Customer Master 
##############################
g++  -I$boost_home  $file_name -o output  $boost_home/boost/regex.hpp $boost_home/boost/multi_array.hpp  $boost_home/boost/numeric/ublas/matrix.hpp $boost_home/boost/numeric/ublas/operation.hpp   && ./output  /home/blesson/base_code/neural_net/data/sample_train.csv
