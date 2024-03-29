
echo -e "\e[0m\e[1m-------------GOOD TESTS--------------------"
TOTAL_GOOD=0
CORRECT_GOOD=0
TOTAL_BAD=0
CORRECT_BAD=0
for f in ./lattests/good/*.output
do
    filename=${f::-7}.lat
    echo -e "\e[0mTEST $filename"
    rm -f ${f::-7}.ll ${f::-7}.bc
    ./latc_llvm $filename 2>1 > /dev/null
    if [ $? -eq 0 ] 
    then
        ./latc_llvm $filename 
        if test -f ${f::-7}.input; 
        then 
            echo -e "Test with input"
            lli-6.0 ${f::-7}.bc < ${f::-7}.input > tmp.out
            if  diff $f tmp.out > /dev/null 2>&1
            then
                echo -e "\e[32m\e[1mOK"
                ((CORRECT_GOOD=CORRECT_GOOD+1))
            else 
                echo -e "\e[31m\e[1mWRONG"
            fi
        else 
            lli-6.0 ${f::-7}.bc > tmp.out
            if diff $f tmp.out > /dev/null 2>&1
            then
                echo -e "\e[32m\e[1mOK"
                ((CORRECT_GOOD=CORRECT_GOOD+1))
            else 
                echo -e "\e[31m\e[1mWRONG"
            fi
        fi
    else
        echo -e "\e[31m\e[1mWRONG"
    fi
    ((TOTAL_GOOD=TOTAL_GOOD+1))
done

# echo -e "\e[0m\e[1m-------------BAD TESTS--------------------"
# for f in ./lattests/bad/*.lat
# do
#     echo -e "\e[0mTEST $f"
#     ./latc_llvm $f
#     if [ $? -eq 0 ] 
#     then
#         echo -e "\e[31m\e[1mWRONG"
#     else
#         echo -e "\e[32m\e[1mOK"
#         ((CORRECT_BAD=CORRECT_BAD+1))
#     fi
#     ((TOTAL_BAD=TOTAL_BAD+1))
# done

echo -e "\e[0m\e[1mGOOD Test results : $CORRECT_GOOD / $TOTAL_GOOD" 
# echo -e "\e[0m\e[1mBAD Test results : $CORRECT_BAD / $TOTAL_BAD" 
echo -e "\e[0m"