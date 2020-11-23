##-------------------------------------------------------------------------------------------------
## HEADER INFORMATION
##-------------------------------------------------------------------------------------------------
## This Shell Script is used to obtain the program filename from build_name.txt in build_info
## after which it will execute it.

## Read the filename from the chosen location
SOURCE_FILENAME="${PWD}/build_info/build_name.txt"
EXEC_FILENAME=(`cat $SOURCE_FILENAME`)
EXEC_FILENAME=${EXEC_FILENAME}

## Change directory to execute the file
cd build/tests
./${EXEC_FILENAME}_tests