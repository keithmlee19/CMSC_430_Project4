// CMSC 430 Compiler Theory and Design
// Project 4 Skeleton
// UMGC CITE
// Summer 2023

// This file contains the template symbol table

template <typename T>
class Symbols
{
public:
	void insert(char* lexeme, T entry);
	bool find(char* lexeme, T& entry);
	bool findDup(char* lexeme, string message);
private:
	map<string, T> symbols;
};

template <typename T>
void Symbols<T>::insert(char* lexeme, T entry)
{
	string name(lexeme);
	symbols[name] = entry;
}

template <typename T>
bool Symbols<T>::find(char* lexeme, T& entry)
{
	string name(lexeme);
	typedef typename map<string, T>::iterator Iterator;
	Iterator iterator = symbols.find(name);
	bool found = iterator != symbols.end();
	if (found)
		entry = iterator->second;
	return found;
}

template <typename T>
bool Symbols<T>::findDup(char* lexeme, string message)
{
	string name(lexeme);
	typedef typename map<string, T>::iterator Iterator;
	Iterator iterator = symbols.find(name);
	bool found = iterator != symbols.end();
	// adds error message with name of variable
	if (found)
		appendError(GENERAL_SEMANTIC, "Duplicate " + message + name);
	return found;
}