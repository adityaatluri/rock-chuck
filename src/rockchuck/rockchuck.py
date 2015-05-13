

import shlex, inspect

def rockchuck(arg):
	def wrap(fn):
		def inner(*args, **kargs):
			src = inspect.getsource(fn)
			print src
			return fn(*args,**kargs)
		return inner
	return wrap

@rockchuck("gpu")
def math(a,b):
	return a+b

print math([3,3,3],[2,2,2])
