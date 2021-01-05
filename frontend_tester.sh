TOTAL_GOOD=0
CORRECT_GOOD=0
TOTAL_BAD=0
CORRECT_BAD=0
echo -e "\e[0m\e[1m-------------BAD TESTS--------------------"
for f in ./lattests/bad_front/*.lat
do
    echo -e "\e[0mTEST $f"
    ./latc_llvm $f
    if [ $? -eq 0 ] 
    then
        echo -e "\e[31m\e[1mWRONG"
        exit 0
    else
        echo -e "\e[32m\e[1mOK"
        ((CORRECT_BAD=CORRECT_BAD+1))
    fi
    ((TOTAL_BAD=TOTAL_BAD+1))
done

echo -e "\e[0m\e[1m-------------GOOD TESTS--------------------"
for f in ./lattests/good_front/*.lat
do
    echo -e "\e[0mTEST $f"
    ./latc_llvm $f > tmp.out
    lli-6.0 ${f::-4}.bc > /dev/null
    ./latc_llvm $f > tmp.out # Hacky, since we need to know the escape code
    if [ $? -eq 0 ] 
    then
        echo -e "\e[32m\e[1mOK"
        ((CORRECT_GOOD=CORRECT_GOOD+1))
    else
        echo -e "\e[31m\e[1mWRONG"
        exit 0
    fi
    ((TOTAL_GOOD=TOTAL_GOOD+1))
done


echo -e "\e[0m\e[1mGOOD Test results : $CORRECT_GOOD / $TOTAL_GOOD" 
echo -e "\e[0m\e[1mBAD Test results : $CORRECT_BAD / $TOTAL_BAD" 