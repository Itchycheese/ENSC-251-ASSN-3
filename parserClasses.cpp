//Use only the following libraries:
#include "parserClasses.h"
#include <string>
/// debug code
#include <iostream>


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
    if (delimiter_test != offset)
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
        quote_delim_test = firstchar.find_first_of("b0x",0);
        if(quote_delim_test == 0)
        {
            secondchar = thestring.substr(offset+1,1);
            if(secondchar == "\\")
            {
                next_delimiter = thestring.find_first_of("\"", offset+1);
                tokenLength = quote_delim_test-offset;
                return;
            }
            else
            {
                bool flag = true;
                while (flag)
                {
                    next_delimiter = thestring.find_first_of(",.;:<>[]{}()?/`~!@#$%^&*|-=+b0x'\"-   ", offset+1);
                    firstchar = thestring.substr(next_delimiter,1);

                    //checks if it is a bit vector
                    quote_delim_test = firstchar.find_first_of("b0x",0);
                    if(quote_delim_test == 0)
                    {
                        secondchar = thestring.substr(next_delimiter+1,1);
                        if(secondchar == "\\")
                        {
                            next_delimiter = thestring.find_first_of("\"", next_delimiter+2);
                            tokenLength = quote_delim_test-offset;
                            continue;
                        }
                        else
                        {
                            flag = false;
                        }
                    }
                }

            }
        }

        // checks for word entities
        {
            quote_delim_test = firstchar.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIGJLMNOPQRSTUVWXYZ",offset);
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

                return;
            }
        }

    }
    else
    {
        tokenLength = 1;
        return;
    }



    { //Probably Wrong code.
    /*
    size_t next_single_delimit = string::npos;
    size_t next_double_delimit = string::npos;
    size_t next_quote_delimit = string::npos;
    size_t next_whitespace = string::npos;
    size_t next_comment = string::npos;
    size_t pos_next_delimiter = string::npos;
    size_t temp = string::npos;
    size_t temp2 = string::npos;
    size_t temp3 = string::npos;
    size_t temp4 = string::npos;
    string the_string = *str;
    string type_of_delimiter_next;
    string type_of_delimiter_temp1;
    string type_of_delimiter_temp2;
    string type_of_delimiter_temp3;
    string type_of_delimiter_temp4;

    size_t new_offset;

    //finds the next whitespace delimiter
    next_whitespace = the_string.find_first_of(delimiters_whitespace, offset);

    //finds the next single character delimiter
    next_single_delimit = the_string.find_first_of(delimiters_single_char, offset);

    // this part finds the next double-type character delimiter
    {
        next_double_delimit = the_string.find_first_of(delimiters_1, offset);
        temp = the_string.find_first_of(delimiters_2, offset);
        next_double_delimit = givesSmallest(next_double_delimit, temp);
        temp = the_string.find_first_of(delimiters_3, offset);
        next_double_delimit = givesSmallest(next_double_delimit, temp);
        temp = the_string.find_first_of(delimiters_4, offset);
        next_double_delimit = givesSmallest(next_double_delimit, temp);
        temp = the_string.find_first_of(delimiters_5, offset);
        next_double_delimit = givesSmallest(next_double_delimit, temp);
        temp = the_string.find_first_of(delimiters_6, offset);
        next_double_delimit = givesSmallest(next_double_delimit, temp);
    }

    // this part finds the next quote-type delimiter
    {
        next_quote_delimit = the_string.find_first_of(delimiter_quote_1);
        temp = the_string.find_first_of(delimiter_quote_2);
        next_quote_delimit = givesSmallest(next_quote_delimit, temp);
        temp = the_string.find_first_of(delimiter_quote_3);
        next_quote_delimit = givesSmallest(next_quote_delimit, temp);
        temp = the_string.find_first_of(delimiter_singlequote);
        next_quote_delimit = givesSmallest(next_quote_delimit, temp);
        temp = the_string.find_first_of(delimiter_doublequote);
        next_quote_delimit = givesSmallest(next_quote_delimit, temp);
    }

    // this part finds the next comment delimiter (if any)
    next_comment = the_string.find_first_of(delimiter_comments, offset);

    //this part finds which type of delimiter is next
    {
        //checks whitespace and singles.
        {
            if(next_whitespace == string::npos && next_single_delimit == string::npos)
            {
                type_of_delimiter_temp1 = "neither";
            }
            else if(next_whitespace < next_single_delimit)
            {
                type_of_delimiter_temp1 = "whitespace";
                temp = next_whitespace;
            }
            else
            {
                type_of_delimiter_temp1 = "single";
                temp = next_single_delimit;
            }
        }

        //checks doubles and quotes
        {
            if(next_double_delimit == string::npos && next_quote_delimit == string::npos)
            {
                type_of_delimiter_temp2 = "neither";
            }
            else if(next_double_delimit < next_quote_delimit)
            {
                type_of_delimiter_temp2 = "double";
                temp2 = next_double_delimit;
            }
            else
        {
            type_of_delimiter_temp2 = "quote";
            temp2 = next_quote_delimit;
        }
        }

        //2nd tier checking
        {
            if (type_of_delimiter_temp1 == "neither" && type_of_delimiter_temp2 != "neither")
            {
                temp3 = temp2;
                type_of_delimiter_temp3 = type_of_delimiter_temp2;
            }
            else if (type_of_delimiter_temp1 != "neither" && type_of_delimiter_temp2 == "neither")
            {
                temp3 = temp2;
                type_of_delimiter_temp3 = type_of_delimiter_temp1;
            }
            else if (type_of_delimiter_temp1 == "neither" && type_of_delimiter_temp2 == "neither")
            {
                type_of_delimiter_temp3 = "neither";
            }
            else if( temp2 < temp)
            {
                temp3 = temp2;
                type_of_delimiter_temp3 = type_of_delimiter_temp2;
            }
            else if(temp < temp2)
            {
                temp3 = temp;
                type_of_delimiter_temp3 = type_of_delimiter_temp1;
            }
            else
            {
                return;
            }
        }

        // 3rd tier check
        {
            if (type_of_delimiter_temp3 == "neither" && next_comment != string::npos)
            {
                temp4 = next_comment;
                type_of_delimiter_temp4 = "comment";
            }
            else if (type_of_delimiter_temp3 != "neither" && next_comment == string::npos)
            {
                temp4 = temp3;
                type_of_delimiter_temp4 = type_of_delimiter_temp3;
            }
            else if (type_of_delimiter_temp3 == "neither" && next_comment == string::npos)
            {
                type_of_delimiter_temp4 = "neither";
            }
            else if( temp3 < next_comment)
            {
                temp4 = temp3;
                type_of_delimiter_temp4 = type_of_delimiter_temp3;
            }
            else if(next_comment < temp3)
            {
                temp4 = next_comment;
                type_of_delimiter_temp4 = "comment";
            }
            else
            {
                return;
            }
        }
    }


    // This part gets the token
    {
        if(type_of_delimiter_temp4 == "neither")
        {
            complete = true;
            tokenLength =0;
            return;
        }

        new_offset = temp4;

        tokenLength = (new_offset - offset)-1;
        return;

        /* this code is wrong. Ignore it*/
        {
        /*both these types of tokens dont care about what ends them.
        if(type_of_delimiter_temp4 == "whitespace" || type_of_delimiter_temp4 == "single")
        {
            pos_next_delimiter = the_string.find_first_of("   ,.;:<>'[]{}()_?/'`~!@#$%^&*|-_\"=+", new_offset);
            if (pos_next_delimiter == new_offset+1)
            {
                    offset = offset+2;
                    tokenLength = 0;
                    return;
            }
            else
            {
                tokenLength = (pos_next_delimiter - new_offset)-2;
                return;
            }
        }
        */
        }
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

    if(tokenLength == 9999) //9999 is the code for comment indications. Realisticall no token should be this long
    {
        the_token = the_string.substr(offset,2);
        offset = offset+2;
        tokenLength = 14370;
        ///debug
        cout << the_token << " ";

        return the_token;
    }
    else if(tokenLength == 14370) //14370 is the code for comment token
    {
        the_token = the_string.substr(offset,string::npos);
        complete = true;
        ///debug
        cout << the_token << " ";

        return the_token;
    }
    else
    {
        the_token = the_string.substr(offset,tokenLength);
        offset = offset+tokenLength;
        prepareNextToken();
        ///debug
        cout << "the token is: \"" <<the_token << "\"\n";

        return the_token;
    }

}



//****Challenge Task Functions******

//Removes the token from the linked list if it is not null
//Deletes the token
//On return from function, head, tail and the prev and next Tokens (in relation to the provided token) may be modified.
void TokenList::deleteToken(Token *token) {/*Fill in implementation */}

//Removes all comments from the tokenList including the -- marker
//Returns the number of comments removed
int removeComments(TokenList &tokenList) {/*Fill in implementation */ }


