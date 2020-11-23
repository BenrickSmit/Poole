##-------------------------------------------------------------------------------------------------
## HEADER INFORMATION
##-------------------------------------------------------------------------------------------------
## This Shell Script is used to obtain the program filename from build_name.txt in build_info
## after which it will execute it with gprof, profiling the program for heatmaps.


##-------------------------------------------------------------------------------------------------
## SECTION: FUNCTION DECLARATIONS
##-------------------------------------------------------------------------------------------------
have_prog() {
    [ -x "$(which $1)" ]
}


##-------------------------------------------------------------------------------------------------
## SECTION: PROGRAM LOGIC
##-------------------------------------------------------------------------------------------------
SOURCE_FILENAME="${PWD}/build_info/build_name.txt"
EXEC_FILENAME=(`cat $SOURCE_FILENAME`)
EXEC_FILENAME=${EXEC_FILENAME}
RED=`tput setaf 1`
GREEN=`tput setaf 10`
NC=`tput sgr0`

## Run gprof on the program created
cd build/src/

    ## Determine whether the gmon.out file exists
    if [ -f gmon.out]; then
        gprof ${EXEC_FILENAME} gmon.out --brief > ${EXEC_FILENAME}_profile_info.txt
        cat ${EXEC_FILENAME}_profile_info.txt
    else
        echo "${RED}Profile Information Does NOT Exists. ${NC}"
        echo "${RED}\'gprof\' might not be installed, or you didn't allow${NC}"
        echo "${RED}the creation of profiling information.${NC}"
        echo "${RED}Continuing...${NC}"
    fi

