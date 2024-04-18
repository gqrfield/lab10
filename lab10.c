#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
	int count;
	struct Trie* next[26];
};

// Initializes a trie structure
struct Trie* createTrie()
{
	struct Trie* rTree = (struct Trie*)calloc(1, sizeof(struct Trie));
	return rTree;
}
// Inserts the word to the trie structure
void insert(struct Trie* pTrie, char* word)
{
	if (pTrie == NULL) return;
	struct Trie* pTraverse = pTrie;
	int i = 0;
	while (word[i] != '\0') {
		if (pTraverse->next[word[i] - 'a'] == NULL) {
			pTraverse->next[word[i] - 'a'] = createTrie();
		}
		pTraverse = pTraverse->next[word[i] - 'a'];
		i++;
	}
	pTraverse->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie* pTrie, char* word)
{
	if (pTrie == NULL) return 0;
	struct Trie* pTraverse = pTrie;
	int i = 0;
	while (word[i] != '\0') {
		if (pTraverse->next[word[i] - 'a'] == NULL) {
			return 0;
		}
		pTraverse = pTraverse->next[word[i] - 'a'];
		i++;
	}
	return pTraverse->count;
}

// deallocate the trie structure
struct Trie* deallocateTrie(struct Trie* pTrie)
{
	for (int i = 0; i < 26; i++) {
		if (pTrie->next[i] == NULL) continue;
		deallocateTrie(pTrie->next[i]);
	}
	free(pTrie);
	pTrie = NULL;
	return pTrie;
}


// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char* filename, char** pInWords)
{
	FILE* inFile = fopen(filename, "r");
	if (inFile == NULL) return -1;

	int count = 0;
	
	fscanf(inFile, "%d\n", &count);
	char word[100];
	for (int i = 0; i < count; i++) {
		fscanf(inFile, "%s\n", word);
		pInWords[i] = (char*)calloc(strlen(word)+1, sizeof(char));
		strcpy(pInWords[i], word);
	}
	
	return count;
}

int main(void)
{
	char* inWords[256];

	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i = 0; i < numWords; ++i)
	{
		printf("%s\n", inWords[i]);
	}

	struct Trie* pTrie = createTrie();
	for (int i = 0; i < numWords; i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char* pWords[] = { "notaword", "ucf", "no", "note", "corg" };
	for (int i = 0; i < 5; i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}