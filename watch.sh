while inotifywait -e close_write,modify,move,delete -r src test; do ./compile-test.sh; done
