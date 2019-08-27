# Imports

import csv
from Bio import SeqIO
import subprocess

# Computations

alg = ["dicho", "hash", "dp"]

G1 = "../cpp/resources/fasta/g1.fa"
G2 = "../cpp/resources/fasta/g2.fa"

m = 5

for n in range(0, 10001, 100):
	for j in range(0, len(alg)):
		try:
			for k in range(0, m):
				subprocess.check_call("../cpp/%s %s %s %s" % ("lcs" + alg[j], G1, G2, str(n)), shell=True)
		except:
			pass

# CSV

lines = []

for i in range(0, len(alg)):
	seqs = SeqIO.parse(open("subseq" + alg[i] + ".fa"), "fasta")

	for seq in seqs:		
		head = seq.description.split(" ")

		for j in range(0, len(head)):
			if head[j] == "L:":
				L = int(head[j + 1])
			elif head[j] == "N:":
				N = int(head[j + 1])
			elif head[j] == "T:":
				T = float(head[j + 1])

		lines.append([alg[i], N, L, T])

	subprocess.call("rm -rf %s" % ("subseq" + alg[i] + ".fa"), shell=True)

subprocess.call("mkdir -p products/txt", shell=True)

with open("products/txt/data.txt", 'w', newline='') as file:
	wr = csv.writer(file)
	wr.writerow(["algorithm", "n", "length", "time"])
	for line in lines:
		wr.writerow(line)