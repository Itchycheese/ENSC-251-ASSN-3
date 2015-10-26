/*
Name : Isaac Cheng Hui Tan (301247997), Tran Xuan Nhan Le [Ray] (301243743)
ENSC 251 Assignment 3
*/

//Use only the following libraries:
#include "parserClasses.h"
#include <string>
/// debug code
//#include <iostream>


//****TokenList class function definitions******
//           function implementations for append have been provided and do not need to be modified

//Creates a new token for the string input, str
//Appends this new token to the TokenList
//On return from the function, it will be the last token in the list
void TokenList::append(const string &str) {
	Token *token = new Token(str);
	append(token);
}

//Appends the token to the TokenList if not null
//On return from the function, it will be the last token in the list
void TokenList::append(Token *token) {
	if (!head) {
		head = token;
		tail = token;
	}
	else {
		tail->setNext(token);
		token->setPrev(tail);
		tail = token;
	}
}


//Complete the implementation of the following member functions:
//****Tokenizer class function definitions******

size_t Tokenizer::givesSmallest(size_t a, size_t b) //returns the smaller of the two numbers.
{
    if (a < b)
        return a;
    else
        return b;
}

//Computes a new tokenLength for the next token
//Modifies: size_t tokenLength, and bool complete
//(Optionally): may modify offset
//Does NOT modify any other member variable of Tokenizer
void Tokenizer::prepareNextToken()
{/*Fill in implementation */

    ///this is testing

    string thestring;
    string firstchar;
    string secondchar;

    ///debug code
    //cout << "the string is: "<<*str << endl;


    thestring = *str;

    size_t delimiter_test = string::npos;
    size_t quote_delim_test = string::npos;
    size_t next_delimiter;
    size_t temp_offset;

    //check if we are at the end of the line
    if(offset >= thestring.length())
    {
        complete = true;
        return;
    }

    //first step is to get the first token.
    //start of a new string
    /*
    if (offset ==0)
    {
        firstchar = thestring.substr(offset,1);
        delimiter_test = firstchar.find_first_of(" ,.;[]{}()_?`~!@#$%^&|_+",0);
        tokenLength = 1;
        return;
    }
    */
    //normal cases
    firstchar = thestring.substr(offset,1);
    delimiter_test = firstchar.find_first_of(",.;[]{}()?`~!@#$%^&|+",0);
    if (delimiter_test != 0)
    {

        // checks for single quotes
        quote_delim_test = firstchar.find_first_of("'",0);
        if(quote_delim_test == 0)
        {
            next_delimiter = thestring.find_first_of("'", offset+1);
            tokenLength = next_delimiter-offset+1;
            return;
        }

        //checks for double quotes
        quote_delim_test = firstchar.find_first_of("\"",0);
        if(quote_delim_test == 0)
        {
            next_delimiter = thestring.find_first_of("\"", offset+1);
            tokenLength = next_delimiter-offset+1;
            return;
        }

        //checks for <=
        quote_delim_test = firstchar.find_first_of("<",0);
        if(quote_delim_test == 0)
        {
            secondchar = thestring.substr(offset+1,1);
            if(secondchar == "=")
            {
                tokenLength = 2;
                return;
            }
            else
            {
                tokenLength =1;
                return;
            }
        }

        //checks for =>
        quote_delim_test = firstchar.find_first_of("=",0);
        if(quote_delim_test == 0)
        {
            secondchar = thestring.substr(offset+1,1);
            if(secondchar == ">")
            {
                tokenLength = 2;
                return;
            }
            else
            {
                tokenLength =1;
                return;
            }
        }

        //checks for :=
        quote_delim_test = firstchar.find_first_of(":",0);
        if(quote_delim_test == 0)
        {
            secondchar = thestring.substr(offset+1,1);
            if(secondchar == "=")
            {
                tokenLength = 2;
                return;
            }
            else
            {
                tokenLength =1;
                return;
            }
        }

        //checks for /=
        quote_delim_test = firstchar.find_first_of("//",0);
        if(quote_delim_test == 0)
        {
            secondchar = thestring.substr(offset+1,1);
            if(secondchar == "=")
            {
                tokenLength = 2;
                return;
            }
            else
            {
                tokenLength =1;
                return;
            }
        }

        //checks for **
        quote_delim_test = firstchar.find_first_of("*",0);
        if(quote_delim_test == 0)
        {
            secondchar = thestring.substr(offset+1,1);
            if(secondchar == "*")
            {
                tokenLength = 2;
                return;
            }
            else
            {
                tokenLength =1;
                return;
            }
        }

        //checks for >=
        quote_delim_test = firstchar.find_first_of(">",0);
        if(quote_delim_test == 0)
        {
            secondchar = thestring.substr(offset+1,1);
            if(secondchar == "=")
            {
                tokenLength = 2;
                return;
            }
            else
            {
                tokenLength =1;
                return;
            }
        }

        //checks for --
        quote_delim_test = firstchar.find_first_of("-",0);
        if(quote_delim_test == 0)
        {
            secondchar = thestring.substr(offset+1,1);
            if(secondchar == "-")
            {
                tokenLength = 9999;
                return;
            }
            else
            {
                tokenLength =1;
                return;
            }
        }

        //checks if it is a bit vector
        quote_delim_test = firstchar.find_first_of("bBOoxX",0);
        if(quote_delim_test == 0)
        {
            secondchar = thestring.substr(offset+1,1);
            if(secondchar == "\"")
            {
                next_delimiter = thestring.find_first_of("\"", offset+2);
                tokenLength = next_delimiter-offset+1;
                return;
            }
        }

        // checks for word entities
        {
            quote_delim_test = firstchar.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIGJLMNOPQRSTUVWXYZ0123456789",0);
            if(quote_delim_test == 0)
            {
                next_delimiter = thestring.find_first_of(",.;:<>[]{}()?/`~!@#$%^&*|-=+  '\"-", offset+1);
                if (offset == 0)
                {
                    tokenLength = next_delimiter;
                }
                else
                {
                    tokenLength = next_delimiter - offset;
                }
                return;
            }

        }

        // checks for whitespace.
        {
            quote_delim_test = firstchar.find_first_of("    ",0);
            if(quote_delim_test == 0)
            {
                offset = offset +1;
                prepareNextToken();
                return;
            }
        }

        // checks for newlines
        {
            quote_delim_test = firstchar.find_first_of("\n",0);
            if(quote_delim_test == 0)
            {
                complete = true;
                return;
            }
        }
    }
    else
    {
        tokenLength = 1;
        return;
    }
}

//Sets the current string to be tokenized
//Resets all Tokenizer state variables
//Calls Tokenizer::prepareNextToken() as the last statement before returning.
void Tokenizer::setString(string *str)
{/*Fill in implementation */
    complete = false;
    offset = 0;
    tokenLength =0;
    this->str = str;
    prepareNextToken();
    return;
}

//Returns the next token. Hint: consider the substr function
//Updates the tokenizer state
//Updates offset, resets tokenLength, updates processingABC member variables
//Calls Tokenizer::prepareNextToken() as the last statement before returning.
string Tokenizer::getNextToken()
{/*Fill in implementation */

    string the_string;
    string the_token;
    the_string = *str;

    if(tokenLength == 9999) //9999 is the code for comment indications. Realistically no token should be this long
    {
        the_token = the_string.substr(offset,2);
        offset = offset+2;
        tokenLength = 14370;
        ///debug
        //cout << "the token is: \"" <<the_token << "\"\n";

        return the_token;
    }
    else if(tokenLength == 14370) //14370 is the code for comment token
    {
        the_token = the_string.substr(offset,string::npos);
        complete = true;
        ///debug
        //cout << "the token is: \"" <<the_token << "\"\n";

        return the_token;
    }
    else
    {
        the_token = the_string.substr(offset,tokenLength);
        offset = offset+tokenLength;
        prepareNextToken();
        ///debug
        //cout << "the token is: \"" <<the_token << "\"\n";

        return the_token;
    }

}



//****Challenge Task Functions******

//Removes the token from the linked list if it is not null
//Deletes the token
//On return from function, head, tail and the prev and next Tokens (in relation to the provided token) may be modified.
void TokenList::deleteToken(Token *token)
{
    Token *temp= nullptr;
    Token *temp2= nullptr;
    if (token != nullptr)
    {
        if(token->prev == nullptr && token->next == nullptr)
        {
            delete token;
        }
        else if (token->prev == nullptr) /// case token is the first node
        {
            head = token->next;
            head ->prev= nullptr;
            delete token;
        }
        else if (token->next == nullptr) /// case token is the last node
        {
            tail = token->prev;
            tail-> next = nullptr;
            delete token;
        }
        else                            /// case token is the middle node
        {
            temp = token->prev;
            temp->next = token->next;
            temp2 = token->next;
            temp2->prev = temp;
            delete token;
        }
    }
}

//Removes all comments from the tokenList including the --  marker
//Returns the number of comments removed
int removeComments(TokenList &tokenList)
{
    Token *temp = nullptr;
    Token *temp2= nullptr;
    Token *temp3= nullptr;
    Token *temp4= nullptr;
    temp = tokenList.getFirst();
    temp2 = temp ->getNext();
    while (temp ->getStringRep()== "--") ///go into the loops until the first line is not a comment
    {
        tokenList.deleteToken(temp);
        tokenList.deleteToken(temp2);
        temp = tokenList.getFirst(); ///increment of temp and temp2
        temp2 = temp->getNext();
    }
    while ((temp2->getNext()) != nullptr) ///check the if it the comment until the end of the list
    {
        temp3 = temp->getPrev();
        temp4=temp2->getNext();
        if (temp->getStringRep() == "--")
        {
            tokenList.deleteToken(temp);
            tokenList.deleteToken(temp2);
            temp = temp4;
            temp2 = temp4->getNext();
        }
        //case we not delete anything -> increment
        temp = temp->getNext();
        temp2 = temp2->getNext();
    }
    ///we check the last 2 node if they are comments

    if (temp2->getStringRep()== "--") ///only the last node is a comment
    {

        temp->setNext(nullptr);
        tokenList.deleteToken(temp2);
    }
    else if ( temp->getStringRep()=="--") ///both 2 last node are comments
    {
        tokenList.deleteToken (temp);
        tokenList.deleteToken (temp2);
    }
}


