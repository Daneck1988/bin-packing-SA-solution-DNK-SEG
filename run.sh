#!/usr/bin/env bash

IFS=$'\n'

if [[ -z $EXEC ]]; then
	EXEC="build/sabp"
fi

if [[ -z $TEST_FOLDER ]]; then
	TEST_FOLDER="test/reduced"
fi

if [[ -z $SOLUTIONS_FILE ]]; then
	SOLUTIONS_FILE=test/solucoes.txt
fi

declare -A solutions
if [[ -f "$SOLUTIONS_FILE" ]]; then
	while read line; do
		solutions[$(awk '{print $1}' <<< "$line")]=$(awk '{print $2}' <<< "$line")
	done < "$SOLUTIONS_FILE"
fi

for file in $(find "$TEST_FOLDER" -type f); do
	echo "Arquivo de teste: $file"
	res=$("$EXEC" -i -c < "$file" | awk '{print $4}')
	optimal=${solutions[$(basename "$file")]}
	echo "Resultado do programa: ${res}"
	if [[ ! -z $optimal ]]; then
		echo "Resultado ótimo:       ${optimal}"
		if [[ $res = $optimal ]]; then
			echo "Resultado ótimo!"
		else
			echo "Diferença de $(bc <<< "${res} - ${optimal}")"
		fi
	fi
done
