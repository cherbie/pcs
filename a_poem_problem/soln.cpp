#include <iostream>
#include <map>
#include <cstdlib>
#include <cstring>

using namespace std;

#define MAX_MESSAGE_LENGTH 1000

/* encrypts pointer of chars using the define map<char, char> object
 * returns the encrypted char * to the caller
 * on error returns NULL
 */
char * encrypt(char * sp, map<char,char> keymap) {
	int length = strlen(sp);
	map<char,char>::iterator it; //access elements in the map
	for(int i = 0; i < length; i++) {
		it = keymap.find(sp[i]); //iterator of value type pair<char,char>
		if( it != keymap.end() ) {
			sp[i] = it->second; //set value to 'second' member variable
			continue;
		}
		else { //no key value for char
			continue;
		}
	}
	return sp;
}

/* decrypts given message using the defined map<char, char> object
 * returns the decrypted message to the caller.
 * on error returns NULL
 */
char * decrypt(char * sp, map<char,char> valkey) {
	int length = strlen(sp);
	map<char,char>::iterator it; //access elements in the map
	for(int i = 0; i < length; i++) {
		it = valkey.find(sp[i]); //iterator of value type pair<char,char>
		if( it != valkey.end() ) {
			sp[i] = it->second; //set value to 'second' member variable
			continue;
		}
		else { //no key value for char
			continue;
		}
	}
	return sp;

}

int main(int argc, char* argv[]) {
	int n; //number of lines in the cipher
	int m; //number of lines to encrypt or decrypt
	cin >> n; //first line
	cin >> m; //second line
	
	map<char, char> key_val; //key value mapping within poem cipher
	map<char, char> val_key; //value key mapping wihtin poem cipher

	//READ TWO UPPERCASE ENGLISH CHARACTERS THAT DEFINE A RULE
	for(int i = 0; i < n; i++) {
		char c_key;
		char c_val;
		cin >> c_key >> c_val;
		key_val[c_key] = c_val; //create key-value mapping
		val_key[c_val] = c_key; //create value-key mapping
	}
	
	//READ LINES OF CAPITAL CHARACTERS AND DECRYPT (d) or ENCRYPT (e) based
	for(int i = 0; i < m; i++) {
		char action;
		cin >> action;
		switch(action) {
		case 'E' : //ENCRYPT the following characters 
			{
			char * string = (char *) malloc( MAX_MESSAGE_LENGTH * sizeof(char));
			cin >> string;
			string = encrypt(string, key_val);
			cout << string << endl;
			break;
			}
		case 'D' : //DECRYPT the following characters
			{
			char* string = (char *) malloc( MAX_MESSAGE_LENGTH * sizeof(char));
			cin >> string;
			string = decrypt(string, val_key);
			cout << string << endl;
			break;
			}
		default : cerr << "Error in understanding whether to encrypt or decrypt." << endl;
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}
