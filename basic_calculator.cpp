
#include <iostream>
#include<queue>
#include<stack>
#include<sstream>
#include<string>
#include <iomanip>
using namespace std;

// This is a basic calculator  that can only use the * + / and - operators

bool balancedparanthesis(const string& infix);//This function checks if the infix expression has balanced parenthesis
bool bracket(const string& infix);// This function checks if the infix expression has brackets
int  precedence(char sign);// This function sets the precedence of the arithmetic operators
string postfix(string infix);// This converts infix expressions that have balanced parenthesis to a postfix expression
string nobracketpostfix(string infix);//This converts infix expressions that do not have balanced parenthesis to a postfix expression
float evaluation(string postfix);// This evaluates the postfix expression

int main()
{
	string input, reply;
	cout << "This is a program that calculates an arithmetic equation\n";
	cout << "*********************************************************\n";
	cout << "This is a program can only calulate the following functions\n";
	cout << "Addition\n";
	cout << "Subtraction\n";
	cout << "Multiplication\n";
	cout << "Division\n";
	cout << "*************************************************************\n";
	cout << "Please put an expresion\n";
	getline(cin, input);

	//this loop checks if there is any invalid character in the infix equation 
	for (int i = 0; i < input.length(); i++)
	{
		if ((!isdigit(input[i])) && (input[i] != '*') && (input[i] != '/') && (input[i] != '+') && (input[i] != '-') && (input[i] != '(') && (input[i] != ')') && (input[i] !='.')) {
			for (int j = 0; j < 5; j++)
			{
				cout << "ERROR, ERROR, ERROR, ERROR, ERROR" << endl;
			}
			cout << "*************************************************************\n";
			cout << "please try again" << endl;
			cout << "*************************************************************\n";
			cout << "Please put an expresion\n";
			getline(cin, input);
		}
	}

	cout << "*************************************************************\n";
	cout << "Is this your equation? " << input << endl;
	cout << "please type yes of no\n";
	cin >> reply;
	cout << "*************************************************************\n";

	// this converts the characters in the reply varaible to lower case letters
	for (int i = 0; i < reply.length(); i++) {
		char hold;
		hold = tolower(reply[i]);
		reply[i] = hold;
	}

	// This statement  is to ensure that the user gives the correct response
	if (reply != "yes" && reply != "no") {
		//		cout << reply << endl;
		cout << "Is this your equation? " << input << endl;
		cout << "please type yes of no\n";
		cin >> reply;
	}

	// if the response  given is  correct this  if statement is execured
	if (reply == "yes") {
		// this is selected if the equation has no brackets
		if (bracket(input) == false) {
			cout << nobracketpostfix(input) << endl;
			cout << evaluation(nobracketpostfix(input)) << endl;
		}
		//this is selected if the equation has balanced parenthesis
		else if (balancedparanthesis(input) == true) {
			cout << postfix(input) << endl;
			cout << evaluation(postfix(input)) << endl;
		}//this is selected if the equation does not have balanced parenthesis
		else if (balancedparanthesis(input) == false) {
			cout << nobracketpostfix(input) << endl;
			cout << evaluation(nobracketpostfix(input)) << endl;
		}
	}
	// if the user selects no, these sets of code runs, this set of instructions asks the user to rewrite his or her equation
	else if (reply == "no") {
		while (reply == "no") {
			cout << "*************************************************************\n";
			cout << "Please put an expresion\n";
			cin.ignore();
			getline(cin, input);
			cout << "*************************************************************\n";
			cout << "Is this your equation? " << input << endl;
			cout << "please type yes of no\n";
			cin >> reply;
			cout << "*************************************************************\n";

			for (int i = 0; i < reply.length(); i++) {
				char hold;
				hold = tolower(reply[i]);
				reply[i] = hold;
			}
			if (reply == "yes") {
				if (bracket(input) == false) {
					cout << nobracketpostfix(input) << endl;
					cout << evaluation(nobracketpostfix(input)) << endl;
				}
				else if (balancedparanthesis(input) == true) {
					cout << postfix(input) << endl;
					cout << evaluation(postfix(input)) << endl;
				}
				else if (balancedparanthesis(input) == false) {
					cout << nobracketpostfix(input) << endl;
					cout << evaluation(nobracketpostfix(input)) << endl;
				}
			}
		}
	}
}


//This function checks if the infix expression has balanced parenthesis
bool balancedparanthesis(const string& infix) {
	stack<char> store;
	string::size_type i;
	char next;
	bool failed = false;

	// this loop checks if a character in the infix statement is a parenthesis
	for (i = 0; !failed && (i < infix.length()); ++i)
	{
		next = infix[i];
		//if an opening bracket is seen then it is pushed to a stack
		if (next == '(')
			store.push(next);
		//if an closing bracket is seen and the stack is not empty then the closing bracket is removed fromt the stack
		else if ((next == ')') && (!store.empty()))
			store.pop();
		//if an closing bracket is seen and the stack is  empty then the equation does not have  balanced parenthesis and the function returns false 
		else if ((next == ')') && (store.empty()))
			failed = true;
	}
	//this return true if the stack is empty
	return (store.empty() && !failed);
}

// This function checks if the infix expression has brackets
bool bracket(const string& infix) {
	string::size_type i;
	char next;
	bool id = false;

	// this loop checks if the equation contains any brackets
	for (i = 0; i < infix.length(); ++i)
	{
		next = infix[i];
		if (next == '(' || next == ')') {
			id = true;
		}

	}
	return id;
}

// This function sets the precedence of the arithmetic operators
int precedence(char sign) {
	int temp = 0;

	// if the character is + or - the precednce of the character is set as 1
	if (sign == '+' || sign == '-') {
		temp = 1;
	}
	// if the character is *  or / the precednce of the character is set as 2
	else
		temp = 2;

	return temp;
}


// This converts infix expressions that have balanced parenthesis to a postfix expression
string postfix(string infix) {
	stack<char> store;
	string postfix;
	char space = ' ';
	string::size_type i;
	char next;
	char dot = '.';

	// this loop iterates through the infix expression
	for (i = 0; i < infix.length(); ++i)
	{
		next = infix[i];
		// if the character is an opening bracket we push it into the stack
		if (next == '(') {
			store.push(next);
		}
		// if the character is an dot we add it to the postfix string
		else if (next == dot) {
			postfix += dot;
		}// if the character is an number we add it to the postfix string
		else if (isdigit(next)) {
			postfix += next;
		}
		// if  the character is an arithmetic operator
		else if (next == '*' || next == '/' || next == '+' || next == '-') {
			// we first add space to the postix string
			postfix += space;
			//then we push the operator into a stack
			store.push(next);
		}
		// when the character is a closing bracket
		else if (next == ')') {
			//when the top of the stack is not a opening bracket
			if (store.top() != '(') {
				//while  the top of the stack is not a opening bracket
				while (store.top() != '(') {
					// we add the top of the stack into the postfix expression
					postfix += store.top();
					// we delete the value at the top of the string
					store.pop();
				}
			}
			//when the top of the stack is  a opening bracket
			if (store.top() == '(') {
				// we delete the value at the top of the string
				store.pop();
			}
		}
		// if the character is a closing bracket and the stack is not empty
		else if (next == ')' && !store.empty()) {
			//while  the top of the stack is not a opening bracket
			while (store.top() != '(')
			{
				// we add the top of the stack into the postfix expression
				postfix += store.top();
				// we delete the value at the top of the string
				store.pop();
			}
			//when the top of the stack is  a opening bracket
			if (store.top() == ')') {
				// we delete the value at the top of the string
				store.pop();
			}
		}
	}
	// while the stack is not empty
	while (!store.empty()) {
		// we add a space to the psotfix expression
		postfix += space;
		// we add the value at the top of the stack to the postfix expression 
		postfix += store.top();
		// we delete the value at the top of the stack
		store.pop();
	}
	return postfix;
}



//This converts infix expressions that do not have balanced parenthesis to a postfix expression
string nobracketpostfix(string infix) {
	stack<char> store;
	string postfix;
	char space = ' ';
	string::size_type i;
	char next;
	char dot = '.';


	// this loop iterrates through the infix expression
	for (i = 0; i < infix.length(); ++i)
	{
		next = infix[i];

		// if the character is a number it is concatenated to the postfix sting
		if (isdigit(next)) {
			postfix += next;
		}
		// if the character is a dot it is concatenated to the postfix sting
		else if (next == dot) {
			postfix += dot;
		}
		//if the character is an  addition sign
		else if (next == '+') {
			// if the character is an adition sign  a space is concatenated to the postfix sting
			postfix += space;
			// if the stack is empty an adition sign is pushed to the stack 
			if (store.empty()) {
				store.push(next);
			}
			// if the stack is not empty
			else if (!store.empty()) {
				// first we check for operator precedence 
				// if the precedence of the oprator in the stack is less than the current character
				if (precedence(store.top()) < precedence(next)) {
					// fist a space is concatenated to the postfix striing
					postfix += space;
					//then the character with the higher precedence is added to the postfix string
					postfix += next;
					//then the character at the top of the stack is added to the postfix string
					postfix += store.top();
					// the value at the top of the stack is deleted
					store.pop();
				}
				// if the precedence of the oprator in the stack is higher than the current character
				else {
					// fist a space is concatenated to the postfix striing
					postfix += space;
					//then the character at the top of the stack is added to the postfix string
					postfix += store.top();
					// the value at the top of the stack is deleted
					store.pop();
					//then the character with the higher precedence is added to the stack
					store.push(next);
				}
			}
		}
		//if the character is a subtraction sign
		else if (next == '-') {
			// if the character is an subtraction sign  a space is concatenated to the postfix sting
			postfix += space;
			if (store.empty()) {
				store.push(next);
			}
			// if the stack is not empty
			else if (!store.empty()) {
				// first we check for operator precedence 
				// if the precedence of the oprator in the stack is less than the current character
				if (precedence(store.top()) < precedence(next)) {
					// fist a space is concatenated to the postfix striing
					postfix += space;
					//then the character with the higher precedence is added to the postfix string
					postfix += next;
					//then the character at the top of the stack is added to the postfix string
					postfix += store.top();
					// the value at the top of the stack is deleted
					store.pop();
				}
				else {
					// fist a space is concatenated to the postfix striing
					postfix += space;
					//then the character at the top of the stack is added to the postfix string
					postfix += store.top();
					// the value at the top of the stack is deleted
					store.pop();
					//then the character with the higher precedence is added to the stack
					store.push(next);
				}
			}
		}
		// if the character is an asterix
		else if (next == '*') {
			// if the character is an asterix  a space is concatenated to the postfix sting
			postfix += space;
			if (store.empty()) {
				// if the stack is empty the character is pushed into it 
				store.push(next);
			}
			else if (!store.empty()) {
				// if the stack is not empty we check for the precedence of the character in the stack and the current character
				if (precedence(store.top()) < precedence(next)) {
					//if the precedence of the character is less than that of the current character we push the currecnt character into the stack
					store.push(next);
				}
				else {
					//if the precedence of the character is not less than that of the current character we first add space to the postfix string
					postfix += space;
					// we then put the character at the top of the stack  into the postfix string
					postfix += store.top();
					// we then delete the  value at the top of the stack
					store.pop();
					// we then put the curret character into the stack
					store.push(next);
				}
			}
		}
		// if the operator is a division sign
		else if (next == '/') {
		// if the character is division sign  a space is concatenated to the postfix sting
			postfix += space;
			if (store.empty()) {
				// if the stack is empty the character is pushed into it
				store.push(next);
			}
			else if (!store.empty()) {
				// if the stack is not empty we check for the precedence of the character in the stack and the current character
				if (precedence(store.top()) < precedence(next)) {
					//if the precedence of the character is less than that of the current character we push the currecnt character into the stack
					store.push(next);
				}
				else {
					//if the precedence of the character is not less than that of the current character we first add space to the postfix string
					postfix += space;
					// we then put the character at the top of the stack  into the postfix string
					postfix += store.top();
					// we then delete the  value at the top of the stack
					store.pop();
					// we then put the curret character into the stack
					store.push(next);
				}
			}
		}
	}
	while (!store.empty()) {
		postfix += space;
		postfix += store.top();
		store.pop();
	}
	return postfix;
}


// This evaluates the postfix expression
float evaluation(string postfix) {
	stack<float> store;
	char space = ' ';
	float eval = 0, hold = 0;
	string::size_type i;
	stringstream value;

	// this loop iterate through the postfix equation to try and solve the equation
	for (i = 0; i < postfix.length(); ++i)
	{    
		// if the character is an empty space the loop continues
		if (postfix[i] == space) { continue; }

		// if the character is a number it enters this loop condition
		else if (isdigit(postfix[i])) {
			//this loop runs till it sees a non-digit character, each time it sees a digit it adds it to a stringstream to store the number
			while (isdigit(postfix[i])||postfix[i]=='.') {
				value << postfix[i];
				i++;
			}
			// this is used to reduce the value of i so that the outer loop continues from where it stoped before the program entered the loop
			i--;
			// the number is moved from a stringstream to an integer varaible.
			value >> hold;
			//the stingstream is cleared
			value.clear();
			// the integer is pushed into a stack.
			store.push(hold);
		}
		else {
			//this stores the value at the top of the stack into an integer varaible
			float val1 = store.top();
			//this deletes the value at the top of the stack
			store.pop();
			//this stores the value at the top of the stack into an integer varaible
			float val2 = store.top();
			//this deletes the value at the top of the stack
			store.pop();

			//this swigh cases do the arithmetic operation and pushes the result into the stack;
			switch (postfix[i]) {
			case '+':store.push(val2 + val1); break;
			case '-':store.push(val2 - val1); break;
			case '*':store.push(val2 * val1); break;
			case '/':store.push(val2 / val1); break;
			}
		}
	}
	//the value at the top of the stack is the answer
	return  store.top();

}






