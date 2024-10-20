#!python
a = [1, 2, 3]

if -1:
	print("-1 is true")

if 0:
	print("0 is true")

if 1:
	print("1 is true")

if 4:
	print("4 is true")

for index, i in enumerate(a):
	if (i == 2):
		a.insert(index + 1, 4)
	print(i)