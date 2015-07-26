#ifndef ROCKCHUCK_H
#define ROCKCHUCK_H

#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif
char* getsrc(char*, unsigned, char*);
#ifdef __cplusplus
}
#endif

class stmt {
protected:
	string Type;
public:
	void printType() { cout << this->Type << endl; }
};

class excepthandler {
};

class expr {
protected:
	string Type;
public:
	void printType() { cout << this->Type << endl; }
};

enum OP {
	ADD,
	SUB,
	MULT,
	DIV,
	MOD,
	POW,
	LSHIFT,
	RSHIFT,
	BITOR,
	BITXOR,
	BITAND,
	FLOORDIV
};

class op{
public:
	unsigned &Op;
	op(unsigned &_Op): Op(_Op){}
};

enum BOOLOP {
	AND,
	OR
};

enum UNARYOP {
	INVERT,
	NOT,
	UADD,
	USUB
};

enum CMPOP {
	EQ,
	NOTEQ,
	LT,
	LTE,
	GT,
	GTE,
	IS,
	ISNOT,
	IN,
	NOTIN
};

class boolop {
public:
	unsigned &Op;
	boolop(unsigned &_Op) : Op(_Op) {}
};

class unaryop {
public:
	unsigned &Op;
	unaryop(unsigned &_Op) : Op(_Op) {}
};

class cmpop {
public:
	unsigned &Op;
	cmpop(unsigned &_Op) : Op(_Op) {}
};

enum expr_context {
	LOAD,
	STORE,
	DEL,
	AUGLOAD,
	AUGSTORE,
	PARAM
};

class exprcontext {
private:
	unsigned value;
public:
	exprcontext(unsigned _value) : value(_value) {}
};



class FunctionDef : public stmt {
private:
	string &name;
	vector<string> &args;
	vector<stmt> &body;
	vector<expr> &declist;
public:
	FunctionDef(string &_name,
				vector<string> &_args,
				vector<stmt> &_body,
				vector<expr> &_declist): name(_name), args(_args), body(_body), declist(_declist) {
		Type = "FunctionDef";
	}
};

class ClassDef : public stmt {
private:
	string &name;
	vector<expr> &bases;
	vector<stmt> &body;
	vector<expr> &declist;
public:
	ClassDef(string &_name,
			vector<expr> &_bases,
			vector<stmt> &_body,
			vector<expr> &_declist): name(_name), bases(_bases), body(_body), declist(_declist){
		Type = "ClassDef";
	}
};

class Return : public stmt {
private:
	vector<expr> &value;
public:
	Return(vector<expr> &_value) : value(_value) { 
		Type = "Return";
	}
};

class Delete : public stmt {
private:
	vector<expr> &targets;
public:
	Delete(vector<expr> &_targets): targets(_targets){
		Type = "Delete";
	}
};

class Assign : public stmt {
private:
	vector<expr> &targets;
	expr &value;
public:
	Assign(vector<expr> &_targets, expr &_value): targets(_targets), value(_value) {
		Type = "Assign";
	}
};

class AugAssign : public stmt {
private:
	expr &target;
	op &Op;
	expr &value;
public:
	AugAssign(expr &_target, op &_Op, expr &_value): target(_target), Op(_Op), value(_value) {
		Type = "AugAssign";
	}
};

class Print : public stmt {
private:
	vector<expr> &dest;
	vector<expr> &values;
	bool &nl;
public:
	Print(vector<expr> &_dest, 
		vector<expr> &_values, 
		bool &_nl): dest(_dest), values(_values), nl(_nl) {
		Type = "Print";
	}
};

class For: public stmt {
private:
	expr &target;
	expr &iter;
	vector<stmt> &body;
	vector<stmt> &orelse;
public:
	For(expr &_target, 
		expr &_iter, 
		vector<stmt> &_body,
		vector<stmt> &_orelse): target(_target), iter(_iter), body(_body), orelse(_orelse) {
		Type = "For";
	}
};

class While :public stmt {
private:
	expr &target;
	vector<stmt> &body;
	vector<stmt> &orelse;
public:
	While(expr &_target,
		vector<stmt> &_body,
		vector<stmt> &_orelse) : target(_target), body(_body), orelse(_orelse) {
		Type = "While";
	}
};

class If :public stmt {
private:
	expr &test;
	vector<stmt> &body;
	vector<stmt> &orelse;
public:
	If(expr &_test, 
		vector<stmt> &_body, 
		vector<stmt> &_orelse): test(_test), body(_body), orelse(_orelse) {
		Type = "If";
	}
};

class With : public stmt {
private:
	expr &context_expr;
	vector<expr> &optional_vars;
	vector<stmt> &body;
public:
	With(expr &_context_expr, 
		vector<expr> &_optional_vars,
		vector<stmt> &_body): context_expr(_context_expr), optional_vars(_optional_vars), body(_body) {
		Type = "With";
	}
};

class Raise : public stmt {
private:
	vector<expr> &type;
	vector<expr> &inst;
	vector<expr> &tback;
public:
	Raise(vector<expr> &_type,
		vector<expr> &_inst,
		vector<expr> &_tback) : type(_type), inst(_inst), tback(_tback) {
		Type = "Raise";
	}
};

class TryExcept : public stmt {
private:
	vector<expr> &body;
	vector<excepthandler> &handlers;
	vector<stmt> &orelse;
public:
	TryExcept(vector<expr> &_body, 
		vector<excepthandler> &_handlers, 
		vector<stmt> &_orelse): body(_body), handlers(_handlers), orelse(_orelse) {
		Type = "TryExcept";
	}
};

class TryFinally : public stmt {
private:
	vector<stmt> &body;
	vector<stmt> &finalbody;
public:
	TryFinally(vector<stmt> &_body,
				vector<stmt> &_finalbody): body(_body), finalbody(_finalbody) {
		Type = "TryFinally";
	}
};

class Assert : public stmt {
private:
	expr &test;
	vector<expr> &msg;
public:
	Assert(expr &_test, 
		vector<expr> &_msg) : test(_test), msg(_msg) {
		Type = "Assert";
	}
};

class Import : public stmt {
	// Usually not needed. If needed, write it.
};

class ImportFrom : public stmt {
	// Usually not needed. If needed, write it.
};

class Exec : public stmt {
private:
	expr &body;
	vector<expr> &globals;
	vector<expr> &locals;
public:
	Exec(expr &_body, vector<expr> &_globals, vector<expr> &_locals): body(_body), globals(_globals), locals(_locals) {
		Type = "Exec";
	}
};

class Global : public stmt {
private:
	vector<string> &names;
public:
	Global(vector<string> &_names) : names(_names) {
		Type = "Global";
	}
};

class Expr : public stmt {
private:
	expr &value;
public:
	Expr(expr &_value) : value(_value) {
		Type = "Expr";
	}
};

class BoolOp : public expr {
private:
	boolop &op;
	vector<expr> values;
public:
	BoolOp(boolop &_op, vector<expr> &_values) : op(_op), values(_values) {
		Type = "BoolOp";
	}
};

class BinOp : public expr {
private:
	op &Op;
	expr &left;
	expr &right;
public:
	BinOp(op &_Op, expr &_left, expr &_right) : Op(_Op), left(_left), right(_right) {
		Type = "BinOp";
	}
};

class UnaryOp : public expr {
private:
	unaryop &Op;
	expr &operand;
public:
	UnaryOp(unaryop &_Op, expr &_operand) : Op(_Op), operand(_operand) {
		Type = "UnaryOp";
	}
};

class Lambda : public expr {
private:
	vector<string> args;
	expr body;
public:
	Lambda(vector<string> &_args, expr &_body): args(_args), body(_body) {
		Type = "Lambda";
	}
};

class IfExp : public expr {
private:
	expr &test;
	expr &body;
	expr &orelse;
public:
	IfExp(expr &_test, expr &_body, expr &_orelse) : test(_test), body(_body), orelse(_orelse) {
		Type = "IfExp";
	}
};

class Dict : public expr {
private:
	vector<expr> &keys;
	vector<expr> &values;
public:
	Dict(vector<expr> &_keys, vector<expr> &_values) : keys(_keys), values(_values){
		Type = "Dict";
	}
};

class Set : public expr {
private:
	vector<expr> &elts;
public:
	Set(vector<expr> &_elts) : elts(_elts) {
		Type = "Set";
	}
};
/*
ListComp(expr elt, comprehension* generators)
SetComp(expr elt, comprehension* generators)
DictComp(expr elt, expr, value, comprehension* generators)
GeneratorExp(expr elt, comprehension* generators)
Yield(expr? value)
*/

class Compare : public expr {
private:
	expr &left;
	vector<cmpop> &ops;
	vector<expr> &comparators;
public:
	Compare(expr _left, vector<cmpop> &_ops, vector<expr> &_comparators):left(_left), ops(_ops), comparators(_comparators) {
		Type = "Compare";
	}
};

class Call : public expr {
private:
	expr &func;
	vector<expr> &args;
	vector<expr> &keywords;
public:
	Call(expr &_func, vector<expr> &_args, vector<expr> &_keywords):func(_func), args(_args), keywords(_keywords) {
		Type = "Call";
	}
};

class Repr : public expr{
private:
	expr &value;
public:
	Repr(expr &_value): value(_value) {
		Type = "Repr";
	}
};

class Num : public expr {
private:
	expr &h;
public:
	Num(expr &_h):h(_h) {
		Type = "Num";
	}
};

class Str : public expr {
private:
	expr &s;
public:
	Str(expr &_s): s(_s) {
		Type = "Str";
	}
};

class Attribute : public expr {
private:
	expr &value;
	string &attr;
	exprcontext &ctx;
public:
	Attribute(expr &_value, string &_attr, exprcontext &_ctx): value(_value), attr(_attr), ctx(_ctx) {
		Type = "Attribute";
	}
};

class Subscript : public expr {
private:
	expr &value;
	expr &slice;
	exprcontext &ctx;
public:
	Subscript(expr &_value, expr &_slice, exprcontext &_ctx) : value(_value), slice(_slice), ctx(_ctx) {
		Type = "Subscript";
	}
};

class Name : public expr {
private:
	string &id;
	exprcontext &ctx;
public:
	Name(string &_id, exprcontext &_ctx) : id(_id), ctx(_ctx) {
		Type = "Name";
	}
};

class List :public expr {
private:
	vector<expr> &elts;
	exprcontext &ctx;
public:
	List(vector<expr> &_elts, exprcontext &_ctx) : elts(_elts), ctx(_ctx) {
		Type = "List";
	}
};

class Tuple : public expr {
private:
	vector<expr> &elts;
	exprcontext &ctx;
public:
	Tuple(vector<expr> &_elts, exprcontext &_ctx) : elts(_elts), ctx(_ctx) {
		Type = "Tuple";
	}
};


#endif
