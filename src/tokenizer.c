#include "tokenizer.h"

TokenList Tokenize(char* string) {
    
    TokenList tokenList = { NULL, 0 };

    uint32_t maxTokens = DEFAULT_COUNT;
    size_t startIndex = 0;
    size_t endIndex = 0;

    tokenList.tokens = malloc(maxTokens * sizeof(Token*));

    size_t len = strlen(string);
    
    while (startIndex < len) {
        endIndex = GetNextEndIndex(string, startIndex, len);

        /* Allocate a new Token into the tokenList */
        tokenList.tokens[tokenList.count] = calloc(1, sizeof(Token));

        /* Copy the string into the created token. */
        tokenList.tokens[tokenList.count]->value = calloc(endIndex - startIndex + 1, sizeof(char));
        memcpy(tokenList.tokens[tokenList.count]->value, string + startIndex, endIndex - startIndex);
        
        // TODO: determine TokenType and arguments

        #ifdef DEBUG
        printf("Made Token %u: { [%s], %u }\n", (uint32_t) tokenList.count,
            tokenList.tokens[tokenList.count]->value,
            tokenList.tokens[tokenList.count]->type);
        #endif

        tokenList.count += 1;
        startIndex = endIndex + 1;

        /* Make room for new tokens if there will be too many */
        if (tokenList.count > maxTokens) {
            maxTokens += DEFAULT_COUNT;

            Token** tmp = realloc(tokenList.tokens, maxTokens * sizeof(Token*));
            if (tmp == NULL) {
                free(tokenList.tokens);
                tokenList.tokens = NULL;
                break;
            }
            tokenList.tokens = tmp;
        }
    }

    return tokenList;
}

/* Return the index one after the end of the next substring. */
size_t GetNextEndIndex(char* string, size_t start, size_t len) {

    for (size_t i = start; i < len + 1; ++i) {
        
        switch(string[i]) {
            case ' ':
                return i;
            default:
                if (i == len) {
                    return i;
                }
        }

    }

    return 0;

}