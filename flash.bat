set "TARGET_PATH=%~1"
set "TARGET_PATH_OCD=%TARGET_PATH:\=/%"

openocd -f "%~dp0openocd.cfg" -c "program \"%TARGET_PATH_OCD%\" verify reset exit"