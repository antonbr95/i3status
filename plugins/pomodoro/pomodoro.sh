#! 


echo 1 > mode
./run_pomodoro $@
while [ true ]; do
	echo 2 > mode
	./run_pomodoro 5 0
	echo 1 > mode
	./run_pomodoro 25
done


