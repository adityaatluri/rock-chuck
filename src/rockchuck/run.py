from ctypes import *
a = CDLL("./librockchuck.so")
a.getsrc.restype=c_char_p
a.getsrc.argtypes=[c_char_p,c_int,c_char_p]
s = create_string_buffer(20)
print a.getsrc(s,len(s),"SH11!")
