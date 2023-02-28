./compile_windows.sh || { echo ''; echo 'FAIL' ; exit 1; }
cd ./demo # otherwise godot shits the bed
../../Godot4 -d main.tscn