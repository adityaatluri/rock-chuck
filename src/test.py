from rockchuck import *

@rockchuck
def math(a,b):
	return a+b

def sub(a,b):
	return a-b

print math([1,1,1],[2,2,2])
rc = RockChuck()
print rc.map(sub,[1,1,1],[2,2,2])
print rc.apply(sub,[1,1,1],[2,2,2])
