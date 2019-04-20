#include <string>

#define ALPHABET_LEN 26

char rotate_char(char a, int sum) {
	return ((a-'A' + sum) % ALPHABET_LEN) + 'A';
}

// decrpt the given string; 
// assume input length is even and <= 15000
// chars are uppercase
std::string drm_message_decrption(std::string &input) {
	if (input.size() % 2 || input.size() == 0)
		return "";

	int sum_1 = 0, sum_2 = 0;

	// rotate the first half
	for (int i=0; i<input.size()/2; i++)
		sum_1 += input[i] - 'A';
	for (int i=0; i<input.size()/2; i++)
		input[i] = rotate_char(input[i], sum_1);
	// rotate the second half
	for (int i=input.size()/2; i<input.size(); i++)
		sum_2 += input[i] - 'A';
	for (int i=input.size()/2; i<input.size(); i++)
		input[i] = rotate_char(input[i], sum_2);

	// merge step by rotating each char in the first half by the value
	// of the corresponding char in the second half string
	for (int i=0, j=input.size()/2; i<input.size()/2; i++, j++)
		input[i] = rotate_char(input[i], input[j]-'A');

	return input.substr(0, input.size()/2);
}
