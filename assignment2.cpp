//Use only the following libraries:
#include "parserClasses.h"
#include <string>
#include <iostream> //REMEMEBER TO DELETE THIS

//Complete the implementation of the following member functions:

//****TokenList class function definitions******

//Creates a new token for the string input, str
//Appends this new token to the TokenList
//On return from the function, it will be the last token in the list
void TokenList::append(const string &str)
{
	Token *newNode = new Token(str);

	//empty 
	if (head == NULL && tail == NULL)
	{
		head = newNode ;
		tail = head;
	}
	else
	{
		newNode->next = NULL;
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode ;
	}
}

//Appends the token to the TokenList if not null
//On return from the function, it will be the last token in the list
void TokenList::append(Token *token)
{
	/* Has access to:
	Token *next; //Next pointer for doubly linked list
	Token *prev; //Previous pointer for doubly linked list
	string stringRep; //Token value
	*/
	//empty
	if (head == NULL && tail == NULL)
	{
		head = token;
		tail = head;
	}
	else
	{
		token->next = NULL;
		token->prev = tail;
		tail->next = token;
		tail = token;
	}


}

//Removes the token from the linked list if it is not null
//Deletes the token
//On return from function, head, tail and the prev and next Tokens (in relation to the provided token) may be modified.
void TokenList::deleteToken(Token *token)
{
	//Has access to: Token *next; //Next pointer for doubly linked list, Token *prev; //Previous pointer for doubly linked list, string stringRep; //Token value

	//error checking
	if (head == NULL && tail == NULL)
	{
		cout << "List is empty, nothing to delete. so fuck you";
		return;
	}

	//Head
	else if (token == head)
	{
		token->next->prev = NULL; //sets the next tokens previous link to null
		head = token->next; //sets the head to the next token
		delete token; //deletes the node
	}

	//Tail
	else if (token == tail)
	{
		token->prev->next = NULL; //makes the next link of the previous node null
		tail = token->prev; // sets the tail to be the previous node
		delete token; //deletes the node
	}

	//Body
	else
	{
		token->prev->next = token->next; //sets the previous tokens next link to the next link of the current node
		token->next->prev = token->prev; //sets the next nodes previous link to the previous link of the current node
		delete token; //deletes the node
	}
}


//****Tokenizer class function definitions******

//Computes a new tokenLength for the next token
//Modifies: size_t tokenLength, and bool complete
//(Optionally): may modify offset
//Does NOT modify any other member variable of Tokenizer
void Tokenizer::prepareNextToken()
{
	//cout<< " in top of prepare next token" << endl;
	int temp = 0;

	/*if(processingIncludeStatement == true)
	{
		if(str->at(offset+1) == '<')
		{
			temp = str->find_first_of(">", offset);
			tokenLength = temp - offset;
			offset = offset+tokenLength;
			return; 
			
		}
		else if(str->at(offset+1) == quotes)
		{
			temp = str->find_first_of(quotes, offset-1);
			tokenLength = temp - offset;
			offset = offset+tokenLength;
			return;
		}
		 complete= true;
		return;
	}
	*/

	//removes whitespace
	isWhitespace();

	//Checks for overflow
	if(offset < 0 || (offset >= str -> length()))
	{
		complete = true; 
		return;
	}

	//if processingIncludeStatement is on, makes the <...> strings and "..."
	

	else if(str->at(offset) == '/')
	{
		if(str->at(offset+1)!='\0' && (str->at(offset+1) == '/' || str->at(offset+1) ==  '*'))
		{
			tokenLength = 2;
		}
		else
		{
			tokenLength = 1;
		}
		offset = offset+tokenLength;
		return;
	}
	
	//checks comments
	else if(processingInlineComment)
	{
		temp = str->find_first_not_of(allDaThings, offset);

		tokenLength = temp - offset;

		offset = offset+tokenLength; 
		return;
	}

	//checks block comments
	else if(processingBlockComment)
	{
		int temp1 = 0;
		int temp2 = 0;
		int temp3 = 0;
		
		if (str->at(offset) != '\0')
		{
			temp2 = str->find_last_of("*", offset);
			temp3 = str->find_last_of("/", offset);
			if(temp3 == temp2+1)
			{
				//tokenLength = temp3-offset;
				tokenLength = 2;
				offset = offset+tokenLength;
				return;
			}
	
		}
		temp1 = str->find_first_not_of(allDaThings, offset);
		
		tokenLength = temp1 - offset;
		offset = offset+tokenLength;
		return;
	}

	
	//uses ascii characters (65-90 checks capital case characters A-Z & 97-122 checks lower case characters a-z)
	else if ((str->at(offset) >=65) && (str->at(offset)<=90) || (str->at(offset) >=97) && (str->at(offset)<=122))
	{

		temp = str->find_first_of(" ;,", offset);
		tokenLength = temp - offset;
		offset = offset+tokenLength; 
		return;
		
	}
	
	
	
	//checks for numbers (Ascii code 48-57 represents integers 0-9)
	
	else if (str->at(offset) >=48 && (str->at(offset)<=57))
	{

		temp = str->find_first_of(" ;,", offset);
		tokenLength = temp - offset;
		offset = offset+tokenLength; 
		return;
	}
	
		
	//Double and Triple Cases
	
	// /, //, /*
	

	
	
	
	// &, && , &=
	else if(str->at(offset) == '&')
	{

		if(str->at(offset+1)!='\0' && ((str->at(offset+1) == '&' || str->at(offset+1) ==  '=')))
		{
			tokenLength = 2 ;

		}
		else
		{
			tokenLength = 1;
		}
		offset = offset+tokenLength;

		return;
	}
	
	// |, ||, |=
	else if(str->at(offset) == '|')
	{
		if(str->at(offset+1)!='\0' && (str->at(offset+1) == '|' || str->at(offset+1) ==  '='))
		{
			tokenLength = 2 ;
		}
		else
		{
			tokenLength =1;
		}
		offset = offset+tokenLength;
		return;
	}
	
	//=, ==
	else if(str->at(offset) == '=')
	{
		if(str->at(offset+1)!='\0' && str->at(offset+1) == '=' )
		{
			tokenLength = 2 ;
		}
		else
		{
		tokenLength = 1;
		}
		offset = offset+tokenLength;
		return;
	}
	
	// <. <<. <=, <<=
	else if(str->at(offset) == '<')
	{

		if(str->at(offset+1)!='\0' && (str->at(offset+1) == '<' || str->at(offset+1) == '=' ))
		{
			if (str->at(offset+2)!='\0' && str->at(offset+1) == '<' && str->at(offset+2) == '=' )
			{
				tokenLength = 3;
			}
			else
			{
				tokenLength = 2 ;
			}
		}
		else
		{
			tokenLength = 1;
		}
		offset = offset+tokenLength;
		return;
	}
	
	// >, >>, >=,  >>=
	else if(str->at(offset) == '>')
	{
		if(str->at(offset+1)!='\0' &&  (str->at(offset+1) == '>' || str->at(offset+1) ==  '=' ))
		{
			if (str->at(offset+2)!='\0' && str->at(offset+1) == '>'  && str->at(offset+2) ==  '=')
			{
				tokenLength = 3;
			}
			else
			{
				tokenLength = 2 ;
			}
		}
		else
		{
			tokenLength = 1;
		}
		offset = offset+tokenLength;
		return;
	}
	
	// !, !=
	else if(str->at(offset) == '!')
	{
		if(str->at(offset+1)!='\0' && str->at(offset+1) ==  '=' )
		{
			tokenLength = 2;
		}
		else
		{
			tokenLength = 1;
		}
		offset = offset+tokenLength;
		return;
	}
	
	
	//+, ++, +=
	else if(str->at(offset) == '+')
	{
		if(str->at(offset+1)!='\0' && (str->at(offset+1) ==  '+' || str->at(offset+1) ==  '=' ))
		{
			tokenLength = 2;
		}
		else
		{
			tokenLength = 1;
		}
		offset = offset+tokenLength;
		return;
	}
	
	// -, --, ->, ->*
	else if(str->at(offset) == '-')
	{
		if(str->at(offset+1)!='\0' && (str->at(offset+1) == '-' || str->at(offset+1) ==  '=' || str->at(offset+1) ==  '>' ))
		{
			if (str->at(offset+2)!='\0' && str->at(offset+1) == '>' && str->at(offset+2) == '*' )
			{
				tokenLength = 3;
			}
			else
			{
				tokenLength = 2 ;
			}
		}
		else
		{
			tokenLength = 1;
		}
		offset = offset+tokenLength;
		return;
	}
	
	//*, *=, */ 
	else if(str->at(offset) == '*')
	{
		if(str->at(offset+1)!='\0' && (str->at(offset+1) == '='  || str->at(offset+1) == '/' ))
		{
			tokenLength = 2;
		}
		else
		{
			tokenLength = 1;
		}
		offset = offset+tokenLength;
		return;
	}
	
	// :. ::
	else if(str->at(offset) == ':')
	{
		if(str->at(offset+1)!='\0' && str->at(offset+1) == ':' )
		{
			tokenLength = 2;
		}
		else
		{
			tokenLength = 1;
		}
		offset = offset+tokenLength;
		return;
	}
	
	// ^, ^=
	else if(str->at(offset) == '^')
	{
		if(str->at(offset+1)!='\0' && str->at(offset+1) == '=' )
		{
			tokenLength = 2;
		}
		else
		{
			tokenLength = 1;
		}
		offset = offset+tokenLength;
		return;
	}
	
	// %, %=
	else if(str->at(offset) == '%')
	{
		if(str->at(offset+1)!='\0' && str->at(offset+1) == '=' )
		{
			tokenLength = 2;
		}
		else
		{
			tokenLength = 1;
		}
		offset = offset+tokenLength;
		return;
	}
	
	// (,),[,],{,},;.'.',~,_
	else if(str->at(offset) == '(' || str->at(offset) == ')' || str->at(offset) == '[' || str->at(offset) == ']' || str->at(offset) == '{' || str->at(offset) == '}' 
				||str->at(offset) == ';' || str->at(offset) == '\'' || str->at(offset) == '\"' || str->at(offset) == '~' ||  str->at(offset) == '#' || str->at(offset) == ','|| str->at(offset) == '_')
	{
		tokenLength = 1;
		offset = offset+tokenLength;
		return;
	}
	
	else if (offset!=0 || offset !=1 && str->at(offset-2)== '#')
	{
		temp = str->find_first_of(" ", offset);
		tokenLength = temp - offset;
		offset = offset+tokenLength; 
	}
		
	//cout<< " in end of getNExtToken" << endl;
		
	//complete = true;
	return;

	
}

//Sets the current string to be tokenized
//Resets all Tokenizer state variables
//Calls Tokenizer::prepareNextToken() as the last statement before returning.
void Tokenizer::setString(string *str) 
{
	this -> str = str; // sets the value of string to the str variable in the Tokenizer class
	
	processingInlineComment = false;
	processingIncludeStatement = false;
	complete = false;
	offset = 0;
	tokenLength = 0;
	str = NULL;
	prepareNextToken();
}

//Returns the next token. Hint: consider the substr function
//Updates the tokenizer state
//Updates offset, resets tokenLength, updates processingABC member variables
//Calls Tokenizer::prepareNextToken() as the last statement before returning.
string Tokenizer::getNextToken()
{ 

	string newString = str -> substr(offset-tokenLength, tokenLength); //creates substring at position offset and length tokenLength
	//resets the flags to default false
	processingInlineComment = false;
	processingIncludeStatement = false;
	processingPound = false;


	//checks for #
	if (newString == "#")
	{
		processingPound = true;
	}
	if (processingPound == true && (newString == "include")) //checks for include if # is present
	{

		processingPound = false;
		processingIncludeStatement = true;
		
	}

	//checks for commenting
	

	if(newString == "//")
 	{
		processingInlineComment = true;
	}
	if(newString == "/*")
	{
		processingBlockComment = true;
	}
	if(newString == "*/" && processingBlockComment)
	{                                                                                                                   
		processingBlockComment = false;
	}


	prepareNextToken();
	return newString;	

	

} 

