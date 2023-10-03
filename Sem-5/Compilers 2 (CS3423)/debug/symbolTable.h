#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <variant>
#include <optional>

enum class TYPE {INT, FLOAT, STRING, BOOL, FAMILY, ERROR}; 
class Family
{
    std::string name;
    std::map<std::string, int> int_members;
    std::map<std::string, float> float_members;
    std::map<std::string, std::string> string_members;
    std::map<std::string, bool> bool_members;
    std::map<std::string, Family> family_members;
};
/// @brief a token class to represent error in eval function
class error{};
typedef std::variant<int, float, std::string, bool, Family, error> datatype;

/**
 * @brief Enum representing the different types of symbols
 * 
 */
enum class KIND{
	PRIMITIVE_VAR,		// int, float, string, bool, void
	OBJECT_VAR,
	FAMILY,
	FUNCTION,
	INBUILT_PRIMITIVE_TYPE,
	INBUILT_FAMILY,
	INBUILT_FUNCTION,
	UNKNOWN
};

// Forward declaration of data type used to store location of symbol
struct YYLTYPE;

/**
 * @brief Represents an entry in a Symbol Table
 * 
 * A symbol table entry holds the identifier name, type of symbol, the typename of the symbol,
 * and its location where it was declared
 */
class Symbol{
private:
	std::string name;
	KIND type;
	std::string type_name;
	YYLTYPE* location;
	// TODO: Add another field to store the value of each symbol in the symbol table
	// TODO: Add variables to represent var/const and public/private properties for the relevant symbols

public:
	Symbol(){};
	Symbol(std::string name, KIND type, std::string type_name, YYLTYPE* location);
	~Symbol(){/*TODO: Delete location*/};
	
	std::string getName() { return name; }
	KIND getKind() { return type; }
	std::string getTypeName() { return type_name; }
	void addArgTypeNames(std::string arg_types) { if(type == KIND::FUNCTION) type_name += "(" + arg_types + ")"; }
	YYLTYPE* getLocation() { return location; }

	friend std::ostream& operator << (std::ostream& out, const Symbol& symbol);
};

/**
 * @brief Represents a Symbol Table
 *
 * Internally uses a map to store the symbols. Each symbol table can have multiple child symbol tables, 
 * to represent nested scopes and such.
 */
class SymbolTable{
private:
	std::string namespace_name;
	std::map<std::string, Symbol> symbol_table;
	std::map<std::string, SymbolTable*> child_symbol_tables;
	SymbolTable* parent = NULL;

public:
	static std::string currentVariableType;

private:
	void addInbuiltSymbols();
	void addInbuiltPrimitiveTypenames();
	void addInbuiltFamilyTypenames();
	void addInbuiltFunctions();
	void addInbuiltConstants();

	SymbolTable* addPrimitiveVariable(std::string name, std::string type_name, YYLTYPE* location);
	SymbolTable* addObjectVariable(std::string name, std::string type_name, YYLTYPE* location);
	SymbolTable* addFamily(std::string name, YYLTYPE* location);
	SymbolTable* addFunction(std::string name, std::string type_name, YYLTYPE* location);

public:
	SymbolTable(SymbolTable* parent = NULL, std::string namespace_name = "", bool append = false);
	~SymbolTable(){/*TODO: delete all child symbol tables*/};

	SymbolTable* addSymbol(std::string identifier_name, std::string type_name, YYLTYPE* location, KIND type = KIND::UNKNOWN);
	Symbol* lookUp(std::string name);

	SymbolTable* startNewScope(std::string scope_name = "", bool append = true){auto new_scope = new SymbolTable(this, scope_name, append); return new_scope;};
	SymbolTable* endScope(){return parent;};
	SymbolTable* returnFromFunction(){return parent;};

	std::string getNamespaceName(){return namespace_name;}
	SymbolTable* getParent(){return parent;}

	void printSymbolTable(std::ostream& f, int indentation = 0);
};

#endif