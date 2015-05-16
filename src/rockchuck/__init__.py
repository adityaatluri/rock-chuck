'''
We send the python source to llvm.
Here, we use pythons shlex and inspect
to convert the python function to its
source. We pass the string to rockchuck
C++/LLVM compiler.
'''

import shlex, inspect, os
from ctypes import *
from compiler import *
import rockchuck

def rockchuck(fn):
	def wrap(*args, **kargs):
		print "In decorator"
		src = inspect.getsource(fn)
		print src, type(src)
		a = CDLL("./rockchuck/librockchuck.so")
		a.getsrc.restype=c_char_p
		a.getsrc.argtypes=[c_char_p,c_int,c_char_p]
		src = compiler.generateAST(src)
		s = create_string_buffer(len(src))
		print a.getsrc(s,len(s),src)
		return fn(*args,**kargs)
	return wrap

class rock_chuck(object):
	def map(self,fn,*args):
		src = inspect.getsource(fn)
		print src, type(src)
		a = CDLL("./rockchuck/librockchuck.so")
		a.getsrc.restype=c_char_p
		a.getsrc.argtypes=[c_char_p,c_int,c_char_p]
		src = compiler.generateAST(src)
		s = create_string_buffer(len(src))
		print a.getsrc(s,len(s),src)
	def apply(self,fn,*args):
		src = inspect.getsource(fn)
		print src, type(src)
		a = CDLL("./rockchuck/librockchuck.so")
		a.getsrc.restype=c_char_p
		a.getsrc.argtypes=[c_char_p,c_int,c_char_p]
		src = compiler.generateAST(src)
		s = create_string_buffer(len(src))
		print a.getsrc(s,len(s),src)


def RockChuck():
	r = rock_chuck()
	return r;

if __name__ == "__main__":
	print "Loading rockchuck"
