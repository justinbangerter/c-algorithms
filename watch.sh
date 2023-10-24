while inotifywait -e close_write,modify,move,delete -r src test; do
    clear
    ./compile-test.sh
done
