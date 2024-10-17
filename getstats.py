arqname = input("Escreva o nome do arquivo de saída (Deve estar no formato de saída dos scripts, com arquivo de resposta ótima, e com os argumentos -i e -c)\n> ")
arq = open(arqname, "r", -1, "UTF-8")

caseqtd = 0
accuracy = 0.0
timetot = 0
largesterr = 0

while True:
	arq.readline()
	l2 = arq.readline().split(" ")
	l3 = arq.readline().split(" ")
	arq.readline()
	l5 = arq.readline().split(" ")

	if len(l5) < 5: break

	progres = int(l2[len(l2)-1])
	optires = int(l3[len(l3)-1])
	extime = int(l5[len(l5)-2])

	caseqtd += 1
	timetot += extime
	diff = progres-optires
	if diff > largesterr: largesterr = diff
	accuracy += (1 - (progres-optires)/optires - accuracy)/caseqtd

print("----------Statistics----------")
print("Cases parsed...........: %d" %caseqtd)
print("Average execution time.: %f" %(timetot/caseqtd))
print("Average answer accuracy: %f%%" %(accuracy*100.0))
print("Largest error..........: %d" %largesterr)
