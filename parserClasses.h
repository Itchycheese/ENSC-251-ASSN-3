/*
Name : Isaac Cheng Hui Tan (301247997), Tran Xuan Nhan Le [Ray] (301243743)
ENSC 251 Assignment 3
*/
#ifndef PARSERCLASSES_H_
#define PARSERCLASSES_H_

//Use only the string library DO NOT add any other libraries
#include <string>

using namespace std;

//Declare your variables for storing delimiters here:

//these ones we can search for any of them. they make no difference.
string const delimiters_single_char  = ",.;:<>[]{}()_?/`~!@#$%^&*|-_=+"; //single char delimiters, we can use find_first_of() to find the first one of these
string const delimiters_whitespace = "  "; // in this is a space and a tab
//the following ones we need to search for both of the chars in sequence.
string const delimiters_1 = "<="; // the following are all 2 char delimiters
string const delimiters_2 = "=>"; // can use the find() function to get these.
string const delimiters_3 = ":=";
string const delimiters_4 = "/=";
string const delimiters_5 = "**";
string const delimiters_6 = ">=";
// the following are special as they need to have quotes.
string const delimiter_quote_1 = "b\""; // bit vectors, basically everything until the next " char is in one token.
string const delimiter_quote_2 = "0\"";
string const delimiter_quote_3 = "x\"";
string const delimiter_singlequote = "'";
string const delimiter_doublequote = "\"";
string const delimiter_comments = "--"; // comment delimiter, everything after this to end of line is one token;

//Token class for a doubly-linked list of string tokens
class Token {
private:
	Token *next; //Next pointer for doubly linked list
	Token *prev; //Previous pointer for doubly linked list
	string stringRep; //Token value

	//Allow TokenList class to access Token member variables marked private
  //https://en.wikipedia.org/wiki/Friend_class
  //
	friend class TokenList;

public:
	//Default Constructor, pointers initialized to NULL
	Token() : next(nullptr), prev(nullptr) { }

	//Constructor with string initialization, pointers initialized to NULL
	Token(const string &stringRep) : next(nullptr), prev(nullptr), stringRep(stringRep) { }

	//Returns the Token's *next member
	Token* getNext ( ) const {  return next; }

	//Sets the Token's *next member
	void setNext (Token* next ) { this->next = next; }

	//Returns the Token's *prev member
	Token* getPrev ( ) const { return prev; }

	//Sets the Token's *prev member
	void setPrev (Token* prev ){ this->prev = prev; }

	//Returns a reference to the Token's stringRep member variable
	const string& getStringRep ( ) const { return stringRep; }

	//Sets the token's stringRep variable
	void setStringRep (const string& stringRep ) { this->stringRep = stringRep; }
};

//A doubly-linked list class consisting of Token elements
class TokenList {
private:
	Token *head; //Points to the head of the token list (doubly linked)
	Token *tail; //Points to the tail of the function list (doubly linked)

public:
	//Default Constructor, Empty list with pointers initialized to NULL
	TokenList() : head(nullptr), tail(nullptr) { }

	//Returns a pointer to the head of the list
	Token* getFirst() const { return head; }

	//Returns a pointer to the tail of the list
	Token* getLast() const { return tail; }

	//Creates a new token for the string input, str
	//Appends this new token to the TokenList
	//On return from the function, it will be the last token in the list
	void append(const string &str); //example comment

	//Appends the token to the TokenList if not null
	//On return from the function, it will be the last token in the list
	void append(Token *token);

    //Removes the token from the linked list if it is not null
	//Deletes the token
	//On return from function, head, tail and the prev and next Tokens (in relation to the provided token) may be modified.
	void deleteToken(Token *token);
};

//A class for tokenizing a string of VHDL  code into tokens
class Tokenizer {
private:
	/*State tracking variables for processing a single string*/
	bool complete; //True if finished processing the current string

	size_t offset; //Current position in string
	size_t tokenLength; //Current token length
	string *str; //A pointer to the current string being processed

	//Include any helper functions here
	//e.g. trimming whitespace, comment processing
	size_t givesSmallest(size_t a, size_t b);

	//Computes a new tokenLength for the next token
	//Modifies: size_t tokenLength, and bool complete
	//(Optionally): may modify offset
	//Does NOT modify any other member variable of Tokenizer
	void prepareNextToken();

public:
	//Default Constructor- YOU need to add the member variable initializers.
	Tokenizer()
	    {
            complete = false;
            offset = 0;
            tokenLength = 0;
            str = nullptr;
        }

	//Sets the current string to be tokenized
	//Resets all Tokenizer state variables
	//Calls Tokenizer::prepareNextToken() as the last statement before returning.
	void setString(string *str);

	//Returns true if all possible tokens have been extracted from the current string (string *str)
	bool isComplete() const
    {
        return complete;
	}

	//Returns the next token. Hint: consider the substr function
	//Updates the tokenizer state
	//Updates offset, resets tokenLength, updates processingABC member variables
	//Calls Tokenizer::prepareNextToken() as the last statement before returning.
	string getNextToken();
};


//Removes all comments from the tokenList including the -- marker
//Returns the number of comments removed
int removeComments(TokenList &tokenList);

#endif /* PARSERCLASSES_H_ */
