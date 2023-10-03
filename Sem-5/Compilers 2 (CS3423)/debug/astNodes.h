#ifndef ASTNODES_H
#define ASTNODES_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <optional>

// #include <llvm/IR/Value.h>

#include "symbolTable.h"
using namespace std;

/*------------------------------------------------------------------------
 * Defining the Class Hierarchy

 *------------------------------------------------------------------------*/

/**
 * @brief Base Class for all NOdes in AST
 * 
 */
class ASTNode
{
public:
    /// @brief prints the description/properties/value of the current node
    virtual void print() = 0;
};

/*------------------------------------------------------------------------
 * Expressions
 *------------------------------------------------------------------------*/

/**
 * @brief Base Class for all Expression Nodes
 * 
 */
class Expression : public ASTNode
{
protected:
    datatype value;   ///holds the value of the current node as pair of Identifier of value and the actual value

public:
    Expression(){}
    ~Expression(){}
    /**
     * @brief Evaluates the value of the current Expression based on current value and the children of the nodes if they exist
     * 
     * @return datatype 
     */
    virtual datatype evaluate() = 0;

    // virtual llvm::Value *codegen() = 0;
    /**
     * @brief Get the type of the value stored as a enum class TYPE
     * @note this works correctly iff the index of the components of the std::variant are the same index as the enum class TYPE(both defined in symbolTable.h) 
     * @return TYPE 
     */
    TYPE get_type();
};

////////////////////////////////
/********* Literals ***********/
////////////////////////////////

/**
 * @brief Base Class for all Literals, derives from Expression
*/
class Literal : public Expression
{
    /**
     * @brief return the evaluated value of the expression 
     * 
     * @return datatype 
     */
    datatype evaluate();
};

/**
 * @brief Integer Literal
 * 
 */
class IntegerLiteral : public Literal
{
public:
    /**
     * @brief Construct a new Integer Literal object
     * 
     * @param val the value of the int literal
     */
    IntegerLiteral(int val){value = val;}
    void print();
    datatype evaluate();
    // llvm::Value *codegen() override;
};
/**
 * @brief Float Literals
 * 
 */
class FloatLiteral : public Literal
{
public:
    /**
     * @brief Construct a new Floating Point Literal object
     * 
     * @param val value of float literal
     */
    FloatLiteral(float val){value = val;}
    void print();
    datatype evaluate();
    // llvm::Value *codegen() override;
};

/**
 * @brief String literals
 * 
 */
class StringLiteral : public Literal
{
public:
    /**
     * @brief Construct a new String Literal object
     * 
     * @param val value of the string literal
     */
    StringLiteral(string val){value = val;}
    void print();
    datatype evaluate();
    // llvm::Value *codegen() override;
};
/**
 * @brief Boolean Literal
 * 
 */
class BooleanLiteral : public Literal
{
public:
    /**
     * @brief Construct a new Boolean Literal object
     * 
     * @param val value of boolean literal
     */
    BooleanLiteral(bool val){value = val;}
    void print();
    datatype evaluate();
    // llvm::Value *codegen() override;
};

/* Identifiers */
/**
 * @brief Represent a variable in the AST
 * 
 */
class Variable : public Expression
{
};

/**
 * @brief represents an Identifier for a type/variable
 * 
 */
class Identifier : public Variable
{
protected:
    string id;  ///name the identifier

public:
    Identifier(string name):id(name){};
    void print();
    string ret_id();
    datatype evaluate();
    // llvm::Value *codegen() override;
};

/**
 * @brief Represents member access operator '::'
 * 
 */
class MemberAccess : public Variable
{
protected:
    Variable *accessor_name;
    Identifier id;

public:
   /**
    * @brief Construct a new Member Access object
    * 
    * @param v 
    * @param s 
    */
    MemberAccess(Variable *v, string s): accessor_name(v), id(Identifier(s)){}
    void print();
    datatype evaluate();
};

/**
 * @brief Array Access i.e. '[]'
 * 
 */
class ArrayAccess : public Variable
{
protected:
    Variable *array_name;   ///name of array
    Expression *index;      ///index to access

public:
    ArrayAccess(Expression *name, Expression *ind)
        :array_name((Variable*)name),index(ind){}
    void print();
    datatype evaluate();
};

class Arg : public Expression
{
protected:
    Identifier t;
    Identifier id;
public:
    Arg(Identifier t_, Identifier id_): t(t_), id(id_){}
    string getType(){return t.ret_id();};
    void print();
    datatype evaluate();
};

/* Function Call */

class FunctionCall : public Expression
{
protected:
    Variable *func_name;
    vector<Expression *> args_list;

public:
    FunctionCall(Expression *name, vector<Expression *> l = vector<Expression *>())
        :func_name((Variable*)name), args_list(l){}
    void print();
    datatype evaluate();
};

/* Assignment */

class AssignmentExp : public Expression
{
protected:
    Variable *LHS;
    Expression *RHS;

public:
    AssignmentExp();
    AssignmentExp(Variable *L, Expression *R): LHS(L), RHS(R){}
    void print();
    datatype evaluate();
};

class AddAssign : public AssignmentExp
{
public:
    AddAssign(Variable *L, Expression *R): AssignmentExp(L,R){}
    void print();
    datatype evaluate(); // evaluation is different from AssignmentExp
};

class SubAssign : public AssignmentExp
{
public:
    SubAssign(Variable *L, Expression *R): AssignmentExp(L,R){}
    void print();
    datatype evaluate(); // evaluation is different from AssignmentExp
};

class MulAssign : public AssignmentExp
{
public:
    MulAssign(Variable *L, Expression *R):  AssignmentExp(L,R){}
    void print();
    datatype evaluate(); // evaluation is different from AssignmentExp
};

class DivAssign : public AssignmentExp
{
public:
    DivAssign(Variable *L, Expression *R):  AssignmentExp(L,R){}
    void print();
    datatype evaluate(); // evaluation is different from AssignmentExp
};

class ModAssign : public AssignmentExp
{
public:
    ModAssign(Variable *L, Expression *R):  AssignmentExp(L,R){}
    void print();
    datatype evaluate(); // evaluation is different from AssignmentExp
};

/* Base Classes for Unary and Binary Operations */

class UnaryOperation : public Expression
{
};

class UnaryIncrement : public UnaryOperation
{
protected:
    Variable *var;
    UnaryIncrement(Variable* v): var(v){}
public:
    void print();
    datatype evaluate();
};

class PostfixInc : public UnaryIncrement
{
public:
    PostfixInc(Variable *v): UnaryIncrement(v){}
    void print();
    datatype evaluate();
};

class PrefixInc : public UnaryIncrement
{
public:
    PrefixInc(Variable *v): UnaryIncrement(v){}
    void print();
    datatype evaluate();
};

class UnaryDecrement : public UnaryOperation
{
protected:
    Variable *var;
    UnaryDecrement(Variable *v):var(v){}
public:
    void print();
    datatype evaluate();
};

class PostfixDec : public UnaryDecrement
{
public:
    PostfixDec(Variable *v):UnaryDecrement(v){}
    void print();
    datatype evaluate();
};

class PrefixDec : public UnaryDecrement
{
public:
    PrefixDec(Variable *v):UnaryDecrement(v){}
    void print();
    datatype evaluate();
};

class UnaryPlus : public UnaryOperation
{
protected:
    Expression *exp;

public:
    UnaryPlus(Expression *e):exp(e){}
    void print();
    datatype evaluate();
};

class UnaryMinus : public UnaryOperation
{
protected:
    Expression *exp;

public:
    UnaryMinus(Expression *e):exp(e){}
    void print();
    datatype evaluate();
};

/// @brief Class to represent the ternary operator in the AST. Derives from Statement
class TernaryOperator : public Expression
{
protected:
    Expression *condition;
    Expression *true_eval;
    Expression *false_eval;

public:
    /// @brief Constructor for TernaryOperator
    /// @param cond conditon
    /// @param t_eval expression to eval on cond == true
    /// @param f_eval expression to eval on cond == false
    TernaryOperator(Expression *cond, Expression *t_eval, Expression *f_eval):
        condition(cond), true_eval(t_eval),false_eval(f_eval){}
    void print();
    datatype evaluate();
};

/* Arithmetic Operations */
class BinaryOperation : public Expression
{
protected:
    Expression *LHS;
    Expression *RHS;
    BinaryOperation();
public:
    BinaryOperation(Expression *L, Expression *R):LHS(L),RHS(R){}
    void print();
    datatype evaluate();
};

class Addition : public BinaryOperation
{
public:
    Addition(Expression *L, Expression *R):BinaryOperation(L,R){}
    void print();
    datatype evaluate();
    /*
    Note : in the implmentation of evaluate function, check the type of both expressions
    and proceed accordingly
    Concatenation can be implemented here
    */
   // llvm::Value *codegen() override;
};

class Subtraction : public BinaryOperation
{
public:
    Subtraction(Expression *L, Expression *R):BinaryOperation(L,R){}
    void print();
    datatype evaluate();
    // llvm::Value *codegen() override;
};

class Multiplication : public BinaryOperation
{
public:
    Multiplication(Expression *L, Expression *R):BinaryOperation(L,R){}
    void print();
    datatype evaluate();
    // llvm::Value *codegen() override;
};

class Division : public BinaryOperation
{
public:
    Division(Expression *L, Expression *R):BinaryOperation(L,R){}
    void print();
    datatype evaluate();
    // llvm::Value *codegen() override;
};

class ModularDiv : public BinaryOperation
{
public:
    ModularDiv(Expression *L, Expression *R):BinaryOperation(L,R){}
    void print();
    datatype evaluate();
    // llvm::Value *codegen() override;
};

/* Logical Operations */

class LogicalAND : public BinaryOperation
{
public:
    LogicalAND(Expression *L, Expression *R):BinaryOperation(L,R){}
    void print();
    datatype evaluate();
};

class LogicalOR : public BinaryOperation
{
public:
    LogicalOR(Expression *L, Expression *R):BinaryOperation(L,R){}
    void print();
    datatype evaluate();
};

class LogicalNOT : public UnaryOperation
{
protected:
    Expression *exp;

public:
    LogicalNOT(Expression *e):exp(e){}
    void print();
    datatype evaluate();
};

/* Comparison Operations */

class CompGT : public BinaryOperation
{
public:
    CompGT(Expression *L, Expression *R):BinaryOperation(L,R){}
    void print();
    datatype evaluate();
    // llvm::Value *codegen() override;
};

class CompLT : public BinaryOperation
{
public:
    CompLT(Expression *L, Expression *R):BinaryOperation(L,R){}
    void print();
    datatype evaluate();
    // llvm::Value *codegen() override;
};

class CompGE : public BinaryOperation
{
public:
    CompGE(Expression *L, Expression *R):BinaryOperation(L,R){}
    void print();
    datatype evaluate();
    // llvm::Value *codegen() override;
};

class CompLE : public BinaryOperation
{
public:
    CompLE(Expression *L, Expression *R):BinaryOperation(L,R){}
    void print();
    datatype evaluate();
    // llvm::Value *codegen() override;
};

class CompEQ : public BinaryOperation
{
public:
    CompEQ(Expression *L, Expression *R):BinaryOperation(L,R){}
    void print();
    datatype evaluate();
    // llvm::Value *codegen() override;
};

class CompNEQ : public BinaryOperation
{
public:
    CompNEQ(Expression *L, Expression *R):BinaryOperation(L,R){}
    void print();
    datatype evaluate();
    // llvm::Value *codegen() override;
};

/*------------------------------------------------------------------------
 * Statements
 *------------------------------------------------------------------------*/
class Statement : public ASTNode
{
    public:
        // virtual llvm::Value *codegen() = 0;
};
/// @brief Class to represent Expression Statements in the AST. Derives from \ref Statement
class ExpressionStatement : public Statement
{
protected:
    vector<Expression *> *exp; ///
public:
    ExpressionStatement():exp(nullptr){}
    /// @brief Constructor for class
    /// @param e input expression
    ExpressionStatement(vector<Expression *>*e) : exp(e){};
    /// @brief print the content of expression statement
    vector<Expression *> getValue();
    void print();
};

/// @brief Class to represent Compound Statements in the AST. Derives from Statement. Represents a collection of statements
class CompoundStatement : public Statement
{
protected:
    vector<Statement *> stmt_list;
    CompoundStatement() = delete;

public:
    /// @brief Constructor for Comppund Statement Class
    /// @param l list of statements
    CompoundStatement(vector<Statement *> l = vector<Statement *>()) : stmt_list(l) {}
    /// @brief print the content of compound statement
    void print();
};

/* Family */
enum class ACCESS_SPEC
{
    PUBLIC,
    PRIVATE
};
/// @brief Class to represent family declarations
class FamilyMembers : public Statement
{
protected:
    ACCESS_SPEC access_specifier;
    Statement *member;

public:
    FamilyMembers(ACCESS_SPEC acc_spec, Statement *member_) : access_specifier(acc_spec), member(member_) {}
    void print();
};
class FamilyDecl : public Statement
{
protected:
    Identifier fam_name;                                            /// Identifier of the familie
    vector<FamilyMembers *> members = vector<FamilyMembers *>();        /// saves the pouinter to the member vars/ function as a List
    std::optional<pair<Identifier, ACCESS_SPEC>> parent_class = {}; /// saves the Identifier and Access specification of the parent class. if there is no parent class, std::optional is not initialised
public:
    FamilyDecl(Identifier fam_name_):fam_name(fam_name_){}
    /**
     * @brief Construct a new Family Decl object
     *
     * @param fam_name_ Identifier of family
     * @param members_ List of pointers to the memeber funcs/vars
     * @param parent_class_ pairent class's Identifier and access specs(public/ private) as a optional.
     */
    FamilyDecl(Identifier fam_name_, vector<FamilyMembers *> members_, optional<pair<Identifier, ACCESS_SPEC>> parent_class_ = {})
        : fam_name(fam_name_), members(members_), parent_class(parent_class_) {}
    /**
     * @brief Construct a new Family Decl object
     *
     * @param fam_name_ Identifier of family
     * @param parent_class_ pairent class's Identifier and access specs(public/ private) as a optional.
     */
    FamilyDecl(Identifier fam_name_, optional<pair<Identifier, ACCESS_SPEC>> parent_class_)
        : fam_name(fam_name_), parent_class(parent_class_) {}
    void print();
};
class ConstructorDeclaration : public Statement
{
protected:
    Identifier class_name;
    CompoundStatement *body;
    vector<Arg *> arg_list;

public:
    ConstructorDeclaration(Identifier class_name_, Statement *body_, vector<Arg *> arg_list_) 
        : class_name(class_name_), body((CompoundStatement*)body_), arg_list(arg_list_){};
    void print();
};

/* Declaration Statements */

/// @brief Class to represent Function Definition in the AST. Derives from Statement
class FunctionDeclaration : public Statement
{
protected:
    Identifier *func_name;
    Identifier return_type;
    CompoundStatement *func_body;
    vector<Arg *> arg_list;

public:
    FunctionDeclaration() = delete;
    /// @brief Constructor for Function Definition Class
    /// @param _name function name
    /// @param _t return type
    /// @param _arg_list list of arguments
    /// @param _stmt list of arguments
    FunctionDeclaration(Identifier *_name, Identifier _t, Statement *_stmt, vector<Arg *> _arg_list = vector<Arg *>())
        :func_name(_name), return_type(_t), func_body((CompoundStatement*)_stmt), arg_list(_arg_list) {}
    /// @brief print the content of function definition
    void print();
};
/// @brief Class to represent Variable Declaration in the AST. Derives from Statement
class VariableDeclaration : public Statement
{
protected:
    Identifier variable_type;
    vector<Expression *> variable_list;

public:
    /// @brief Constructor for function declaration
    /// @param t type of variable
    /// @param l list of identifires
    VariableDeclaration(Identifier t, vector<Expression *> l = vector<Expression*>())
        :variable_type(t), variable_list(l){}
    void print();
};
/// @brief Class to represent definition of driver function in the AST. Derives from CompoundStatement
class DriverDefinition : public Statement
{
protected:
    CompoundStatement *func_body;

public:
    DriverDefinition() = delete;
    /// @brief Constructor for DriverFunction
    /// @param body the Compound Statements that take make up the driver function
    // DriverDefinition(CompoundStatement* body) : func_body(body) {};
    DriverDefinition(Statement *body) : func_body((CompoundStatement *)body) {}
    void print();
};
/// @brief Class to represent variable initialization in the AST. Derives from Statement
class VariableInitialization : public Statement
{
protected:
    Identifier variable_type;
    AssignmentExp *exp;

public:
    /// @brief Constructor for VariableInitiailization
    /// @param t type of variable
    /// @param e paired assignment expression
    VariableInitialization(Identifier t, AssignmentExp *e):variable_type(t), exp(e){}
    void print();
};

/* Labeled Statements */

/// @brief Class to represent All Labelled Statements in the AST
class LabeledStatement : public Statement
{
protected:
    Expression *label;
    Statement *stmt;

public:
    /// @brief Constructor for LabelledStatement
    LabeledStatement() = default;
    LabeledStatement(Expression *lb, Statement *st): label(lb), stmt(st){}
    void print();
};
/// @brief Class to represent 'case' in the AST. Derives from Statement
class CaseLabel : public LabeledStatement
{
public:
    /// @brief Constructor for CaseLabel
    /// @param lb expression to check for in case
    /// @param st_list statement to execute in said case
    CaseLabel(Expression *lb, Statement *st): LabeledStatement(lb,st){}
    void print();
};
/// @brief Class to represent 'default' in the AST. Derives from Statement
class DefaultLabel : public LabeledStatement
{
public:
    /// @brief Constructor for DefaultLabel
    /// @param st_list statement in default case
    DefaultLabel(Statement *st): LabeledStatement(nullptr,st){}
    void print();
};

/* Iteration Statements */

/// @brief Class to represent  iterations in the AST. Derives from Statement. Provides base class to classes like WhileLoop
class IterationStatement : public Statement
{
protected:
    CompoundStatement *body;
    Expression *condition;

public:
    /// @brief Constructor for IterationStatement
    IterationStatement(CompoundStatement *b, Expression *cond): body(b), condition(cond){}
    void print();
};
/// @brief Class to represent while loop in the AST. Derives from Statement
class WhileLoop : public IterationStatement
{
public:
    /// @brief Constructor for WhileLoop
    /// @param b list of statements to execute
    WhileLoop(CompoundStatement *b): IterationStatement(b,nullptr){}
    /// @brief Constructor for WhileLoop
    /// @param b body of while loop
    /// @param cond entry condition for while loop
    WhileLoop(CompoundStatement *b, Expression *cond): IterationStatement(b,cond){}
    void print();
};

/// @brief Class to represent for loop in the AST. Derives from Statement
class ForLoop : public IterationStatement
{
protected:
    ExpressionStatement *initialization;
    ExpressionStatement *condition;
    Expression *counter_updation;

public:
    ForLoop(CompoundStatement *b, ExpressionStatement *init, ExpressionStatement *cond, Expression *update)
        :IterationStatement(b,nullptr), initialization(init), condition(cond), counter_updation(update) {} 
    void print();
};

/*********************************************
 * Selection Statements
 * *******************************************/
/// @brief Class to represent if - else statements in the AST. Derives from Statement
class IfStatement : public Statement
{
protected:
    Expression *condition;
    CompoundStatement *if_block;

public:
    IfStatement(Expression *e, CompoundStatement *block):condition(e),if_block(block) {}
    void print();
    // llvm::Value *codegen() override;
};
class IfElseStatement : public Statement
{
protected:
    Expression *if_condition;
    CompoundStatement *if_block, *else_block;

public:
    IfElseStatement(Expression *cond, CompoundStatement *block1, CompoundStatement *block2)
        :if_condition(cond), if_block(block1), else_block(block2) {}
    void print();
    // llvm::Value *codegen() override;
};
/// @brief Class to represent switch case statement in the AST. Derives from Statement
class SwitchStatement : public Statement
{
protected:
    Expression *exp;
    CompoundStatement *block;

public:
    SwitchStatement(Expression *e, CompoundStatement *b):exp(e), block(b) {}
    void print();
};

/// @brief Provides base class for all jump statements
class JumpStatement : public Statement
{
};
/// @brief Class to represent 'return' in the AST. Derives from Statement.
class ReturnStatement : public JumpStatement
{
protected:
    Expression *return_val;

public:
    ReturnStatement(Expression *val):return_val(val) {}
    void print();
};
/// @brief Class to represent 'break' in the AST. Derives from Statement
class BreakStatement : public JumpStatement
{
public:
    void print();
};
/// @brief Class to represent 'continue' in the AST. Derives from Statement
class ContinueStatement : public JumpStatement
{
public:
    void print();
};

/*------------------------------------------------------------------------
 * Class to create the AST Root Node
 *------------------------------------------------------------------------*/
/// @brief Class to represent the actual program as the AST. Derives from Statement
class Program : public ASTNode
{
protected:
    vector<Statement *> *stmt_list;

public:
    Program(vector<Statement *> *stmts = new vector<Statement *>()):stmt_list(stmts) {}
    void print();
};

// objects at the base of the tree
// extern map <string, value_pair> symTable;
extern Program *root;

#endif