#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
struct TrieNode
{
    struct TrieNode *children[26];
    int isEndOfWord;
};

// Function to create a new Trie node
struct TrieNode *createTrieNode()
{
    struct TrieNode *newNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (newNode)
    {
        newNode->isEndOfWord = 0;
        for (int i = 0; i < 26; i++)
        {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

// Inserts the word into the trie structure
void insert(struct TrieNode *root, char *word)
{
    struct TrieNode *crawler = root;
    for (int i = 0; i < strlen(word) - 1; i++)
    {
        int index = word[i] - 'a';
        if (crawler->children[index] == NULL)
        {
            crawler->children[index] = createTrieNode();
        }
        crawler = crawler->children[index];
    }
    crawler->isEndOfWord += 1;
}

// Helper function for counting occurrences
int countOccurrences(struct TrieNode *root, char *word)
{
    struct TrieNode *crawler = root;
    for (int i = 0; i < strlen(word); i++)
    {
        int index = word[i] - 'a';
        if (!crawler->children[index])
        {
            return 0;
        }
        crawler = crawler->children[index];
    }
    return (crawler != NULL && crawler->isEndOfWord);
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct TrieNode *root, char *word)
{
    return countOccurrences(root, word);
}

// Deallocates the trie structure
void deallocateTrie(struct TrieNode *root)
{
    if (root == NULL)
    {
        return;
    }
    for (int i = 0; i < 26; i++)
    {
        if (root->children[i] != NULL)
        {
            deallocateTrie(root->children[i]);
        }
    }
    free(root);
}

// Initializes a trie structure
struct TrieNode *createTrie()
{
    return createTrieNode();
}

// Reads the dictionary file and stores the words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 0;
    }

    int numWords = 0;
    char word[100]; // Assuming max word length is 99 characters
    while (fscanf(file, "%s", word) != EOF)
    {
        pInWords[numWords] = strdup(word);
        numWords++;
    }
    fclose(file);
    return numWords;
}

int main(void)
{
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("C:\\Users\\aisid\\Downloads\\Lab10\\dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    // Create and populate the Trie
    struct TrieNode *pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }

    // Test with some sample words
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }

    // Deallocate the Trie
    deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");

    return 0;
}