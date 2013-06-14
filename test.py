a='dimos'

b=int(raw_input())

for x in range(b):
	print a[x%len(a)],
