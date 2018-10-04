#include "tokenizer.h"

Token** Tokenize(char* text, size_t len) {

    uint32_t maxTokens = DEFAULT_COUNT;
    uint32_t tokenCount = 0;
    uint32_t startIndex = 0;
    uint32_t createNewToken = 0;

    Token** tokens = malloc(maxTokens * sizeof(Token*));
    
    for (size_t i = 0; i < len; i++) {
        switch (text[i]) {
            case ' ':
                createNewToken = 1;
                break;
            default:
                break;           
        }

        if (createNewToken) {
            tokens[tokenCount] = malloc(sizeof(Token));
            tokens[tokenCount]->value = malloc(i - startIndex);
            tokenCount += 1;

            if (tokenCount > maxTokens) {
                maxTokens += DEFAULT_COUNT;

                Token** tmp = realloc(tokens, maxTokens * sizeof(Token*));
                if (tmp == NULL) {
                    // Halt and Catch Fire
                    return NULL;
                }
                tokens = tmp;
            }
        }
    }

    return tokens;
}