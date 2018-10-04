#include "tokenizer.h"

TokenList Tokenize(char* text, size_t len) {
    
    TokenList tokenList = { NULL, 0 };

    uint32_t maxTokens = DEFAULT_COUNT;
    uint32_t startIndex = 0;
    uint32_t createNewToken = 0;

    tokenList.tokens = malloc(maxTokens * sizeof(Token*));
    
    for (size_t i = 0; i < len; i++) {
        switch (text[i]) {
            case ' ':
                createNewToken = 1;
                break;
            default:
                if ( (i == len - 1) && startIndex != i - 1) {
                    createNewToken = 1;
                }
                break;
        }

        if (createNewToken) {
            tokenList.tokens[tokenList.count] = malloc(sizeof(Token));
            tokenList.tokens[tokenList.count]->value = calloc(i - startIndex, sizeof(char));
            memcpy(tokenList.tokens[tokenList.count]->value, text + startIndex, i - startIndex);

            #ifdef DEBUG
            printf("Made Token %u: {\"%s\", %u}\n", (uint32_t) tokenList.count,
                tokenList.tokens[tokenList.count]->value,
                tokenList.tokens[tokenList.count]->type);
            #endif

            tokenList.count += 1;
            startIndex = i + 1;

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
            createNewToken = 0;
        }
    }

    return tokenList;
}