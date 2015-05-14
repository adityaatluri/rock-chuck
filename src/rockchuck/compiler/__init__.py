'''
This file is used to do generate python AST and send it
to rockchuck llvm compiler
'''

import ast

def generateAST(src):
	node = ast.parse(src)
	return ast.dump(node)
