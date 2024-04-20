#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    struct Trie *children[26];
    int flag;
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int strLen = strlen(word);
    struct Trie *temp = pTrie;
    for (int i = 0; i < strLen; i++)
    {
        if (temp->children[word[i] - 'a'] == NULL)
        {
            temp->children[word[i] - 'a'] = malloc(sizeof(char) * 256);
            temp->children[word[i] - 'a']->flag = 0;
            for (int j = 0; j < 26; j++)
            {
                temp->children[word[i] - 'a']->children[j] = NULL;
            }
        }
        temp = temp->children[word[i] - 'a'];
    }
    temp->flag += 1;
    
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int strLen = strlen(word);
    struct Trie *temp = pTrie;
    for (int i = 0; i < strLen; i++)
    {
        temp = temp->children[word[i] - 'a'];
        if (temp == NULL)
        {
            return 0;
        }
    }
    return temp->flag;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < 26; i++)
    {
        deallocateTrie(pTrie->children[i]);
    }

    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *root = malloc(sizeof(struct Trie));
    root->flag = 0;
    for (int i = 0; i < 26; i++)
    {
        root->children[i] = NULL;
    }
    return root;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *inFile = fopen(filename, "r");
    if (inFile == NULL)
    {
        printf("File Not Found Error, Exiting Program...");
        exit(1);
    }
    int size;
    fscanf(inFile, "%d ", &size);
    char buffer[256];


    for (int i = 0; i < size; i++) 
    {
        pInWords[i] = (char *)malloc(256 * sizeof(char));
    }

    for (int i = 0; i < size; i++)
    {
        fscanf(inFile, "%s ", buffer);
        strcpy((pInWords[i]), buffer);
    }
    return size;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("C:\\Users\\aisid\\Downloads\\Lab10\\dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}
