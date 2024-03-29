RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
echo -e "${BLUE}\n#########################################"
echo -e "~~~~~~~~~~~~~~~~~ Tests ~~~~~~~~~~~~~~~~~"
echo -e "#########################################\n${NC}"

for dTest in ./test/*; do
    #OPEN FILES
    expected=$(cat ./expected/${dTest/test/}/__stdout__)
    expected_return=$(cat ./expected/${dTest/test/}/__return_code__)

    echo $dTest
    echo

    #RUN VALGRIND
    valgrind --tool=memcheck --leak-check=full --leak-resolution=med --show-reachable=yes --trace-children=yes --track-fds=yes --track-origins=no --time-stamp=yes --num-callers=20 --error-exitcode=42  --log-file=./valgrind/${dTest/test/} $dTest/cmd
    val_return=$?
    cuarentaydos=42
    # Test results
    if [ $val_return == $cuarentaydos ]
    then
        printf "${RED} FAILED: Bad memory management ${NC}"
    else
        printf "${GREEN} OK ${NC}"
    fi
    echo
    echo -e "\n-------------------------------------\n" 
done