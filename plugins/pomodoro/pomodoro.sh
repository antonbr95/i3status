#! 


./run_pomodoro $@
while [ true ]; do
	./run_pomodoro 5 0
	./run_pomodoro 25
done


