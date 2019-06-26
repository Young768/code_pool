import random

def add(a):
	print('Function of python called!')
	print('a = ',a)
	#c = 4
	c = random.randint(1,100)%7
	print('New algorithm is:',c)
	return c

#add(3)
