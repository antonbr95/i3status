#! 


echo 1 > mode
echo -n "starting pomodoro at "
date +%T
./run_pomodoro $@
while [ true ]; do
	echo 2 > mode
	echo -n "starting pause at "
	date +%T
	./run_pomodoro 5 0
	echo 1 > mode
	echo -n "starting pomodoro at "
	date +%T
	./run_pomodoro 25
done


