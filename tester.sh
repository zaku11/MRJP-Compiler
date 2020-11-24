
echo -e "\e[0m\e[1m-------------GOOD TESTS--------------------"
for f in ./../lattests/good/*.lat
do
    echo -e "\e[0mTEST $f"
    ./TestLatte $f
    if [ $? -eq 0 ] 
    then
        echo -e "\e[32m\e[1mOK"
    else
        echo -e "\e[31m\e[1mWRONG"
    fi
done

echo -e "\e[0m\e[1m-------------BAD TESTS--------------------"
for f in ./../lattests/bad/*.lat
do
    echo -e "\e[0mTEST $f"
    ./TestLatte $f
    if [ $? -eq 0 ] 
    then
        echo -e "\e[31m\e[1mWRONG"
    else
        echo -e "\e[32m\e[1mOK"
    fi
done