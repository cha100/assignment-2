
#ifndef PARSERCLASSES_H_
#define PARSERCLASSES_H_

//Use only the string library DO NOT add any other libraries
#include <string>

using namespace std;

//Declare your variables for storing delimiters here:
string paranths = "()";
string braces = "{}";
string bracks = "[]";
string angBracks = "<>";
string dquote = "\"\"";
string squote = "\'\'";

//Token class for a doubly-linked list of string tokens
class Token {
private:
	Token *next; //Next pointer for doubly linked list
	Token *prev; //Previous pointer for doubly linked list
	string stringRep; //Token value
	 
	//Allow TokenList class to access Token member variables marked private
	friend class TokenList;

public:
	//Default Constructor, pointers initialized to NULL
	Token() : next(NULL), prev(NULL) { }
		
	//Constructor with string initialization, pointers initialized to NULL
	Token(const string &stringRep) : next(NULL), prev(NULL), stringRep(stringRep) { }

	//Returns the Token's *next member 
	Token* getNext ( ) const 
	{
		return next;  //Gets the value of next
	}

	//Sets the Token's *next member
	void setNext (Token* next ) 
	{
		this -> next = next; // pointer pointing to itself, which is the value of next
	}

	//Returns the Token's *prev member 
	Token* getPrev ( ) const 
	{
		return prev; //Gets the value of the last
	}

	//Sets the Token's *prev member
	void setPrev (Token* prev )
	{
		this -> prev = prev; //this operator is a pointer which points to itself
	}

	//Returns a reference to the Token's stringRep member variable
	const string& getStringRep ( ) const 
	{
		return (this -> stringRep); //returns a pointer pointing the address of stringRep
	}

	//Sets the token's stringRep variable
	void setStringRep (const string& stringRep ) 
	{ 
		next->stringRep = stringRep; //sets the value of the next token
	}
};

//A doubly-linked list class consisting of Token elements
class TokenList {
private:
	Token *head; //Points to the head of the token list (doubly linked)
	Token *tail; //Points to the tail of the function list (doubly linked)
	
public:
	//Default Constructor, Empty list with pointers initialized to NULL
	TokenList() : head(NULL), tail(NULL) { }
	
	//Returns a pointer to the head of the list
	Token* getFirst() const 
	{
		return head;  //points to the head of the list
	}

	//Returns a pointer to the tail of the list
	Token* getLast() const 
	{
		return tail;  //points to the tail of this list
	}

	//Creates a new token for the string input, str
	//Appends this new token to the TokenList
	//On return from the function, it will be the last token in the list
	void append(const string &str);	//example comment
	

	//Appends the token to the TokenList if not null
	//On return from the function, it will be the last token in the list
	void append(Token *token);

    //Removes the token from the linked list if it is not null
	//Deletes the token
	//On return from function, head, tail and the prev and next Tokens (in relation to the provided token) may be modified.
	void deleteToken(Token *token);
};

//A class for tokenizing a string of C++  code into tokens
class Tokenizer {
private:
	/*State tracking variables for processing a single string*/
	bool processingInlineComment; //True if processing an In-line comment //
	bool processingBlockComment;  //True if processing a Block Comment /* */
	bool processingIncludeStatement; //True if processing an include statement <> ""
	bool complete; //True if finished processing the current string
	
	size_t offset; //Current position in string
	size_t tokenLength; //Current token length
	string *str; //A pointer to the current string being processed

	//Include any helper functions here
	//e.g. trimming whitespace, comment processing

	//write out the functions for deleting comments and trimming whitespaces.
	
	//Computes a new tokenLength for the next token
	//Modifies: size_t tokenLength, and bool complete
	//(Optionally): may modify offset
	//Does NOT modify any other member variable of Tokenizer
	void prepareNextToken();
	
public:
	//Default Constructor- YOU need to add the member variable initializers.
	Tokenizer()
	{  
		processingInlineComment = false;
		processingBlockComment = false;
		processingIncludeStatement = false; 
		complete = false;
		offset;
		tokenLength; 
		str = NULL;
	};

	//Sets the current string to be tokenized
	//Resets all Tokenizer state variables
	//Calls Tokenizer::prepareNextToken() as the last statement before returning.
	void setString(string *str);

	//Returns true if all possible tokens have been extracted from the current string (string *str)
	bool isComplete() const 
	{ /*Fill in implementation */ 
		return complete;
	}

	//Returns the next token. Hint: consider the substr function
	//Updates the tokenizer state
	//Updates offset, resets tokenLength, updates processingABC member variables
	//Calls Tokenizer::prepareNextToken() as the last statement before returning.
	string getNextToken();
};




#endif /* PARSERCLASSES_H_ */

