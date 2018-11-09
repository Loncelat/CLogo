#include "tokenizer.h"

tokenlist_t Tokenize(char* str) {
    
    tokenlist_t tokenList = { NULL, 0 };

    uint32_t maxTokens = DEFAULT_COUNT;
    size_t startIndex = 0;
    size_t endIndex = 0;

    tokenList.tokens = malloc(maxTokens * sizeof(token_t*));

    size_t len = strlen(str);
    
    while (startIndex < len) {
        endIndex = GetNextEndIndex(str, startIndex, len);

        /* Don't create whitespace tokens */
        if (startIndex < endIndex) {
            /* Allocate a new token_t into the tokenList */
            token_t *tok = calloc(1, sizeof(token_t));

            /* Copy the string into the created token. */
            tok->value = calloc(endIndex - startIndex + 1, sizeof(char));
            memcpy(tok->value, str + startIndex, endIndex - startIndex);
            
            tok->hash = GetHashCode(tok->value);

            // TODO: determine arguments

            #ifdef DEBUG
            printf("Made token_t %I64u: { [%s], %I64u }\n", tokenList.count,
                tok->value,
                tok->hash);
            #endif

            tokenList.tokens[tokenList.count] = tok;
            tokenList.count += 1;

            /* Make room for new tokens if the list is full */
            if (tokenList.count > maxTokens) {
                maxTokens += DEFAULT_COUNT;

                token_t** tmp = realloc(tokenList.tokens, maxTokens * sizeof(token_t*));
                if (tmp == NULL) {
                    free(tokenList.tokens);
                    tokenList.tokens = NULL;
                    break;
                }
                tokenList.tokens = tmp;
            }
        }
        startIndex = endIndex + 1;
    }

    return tokenList;
}

/* Return the index one after the end of the next substring */
size_t GetNextEndIndex(char* str, size_t start, size_t len) {

    for (size_t i = start; i < len + 1; ++i) {
        
        switch(str[i]) {
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

uint64_t GetHashCode(char *str) {
    uint64_t hash = 5381;
    uint32_t c;

    while ( (c = *str++) ) {
        hash = hash * 33 + c;
    }

    return hash;
}