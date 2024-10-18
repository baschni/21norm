#!python
a = [1, 2, 3]

for index, i in enumerate(a):
	if (i == 2):
		a.insert(index + 1, 4)
	print(i)