import os

port = 23333
command = 'socat -d -d tcp-l:' + str(port) + ',reuseaddr,fork EXEC:"python3 -u task.py" '
os.system(command)