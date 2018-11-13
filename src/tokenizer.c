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
            token_t *token = calloc(1, sizeof(token_t));

            /* Copy the string into the created token. */
            token->value = calloc(endIndex - startIndex + 1, sizeof(char));
            memcpy(token->value, str + startIndex, endIndex - startIndex);
            
            token->hash = GetHashCode(token->value);

            int32_t argc = GetArgumentCount(token->hash);
            if (argc == -1) {
                token->argc = 0;
            } else if (argc > 0) {
                token->arg = calloc(argc, sizeof(data_t*));

                //TODO: Support for text in data.
                for (int32_t i = 0; i < argc; ++i) {
                    token->arg[i] = GetNextData(str, &endIndex, len, DATA_NUM);

                    if (token->arg[i] == NULL) {
                        printf("%s misses %d argument(s)\n", token->value, argc - i);
                        return (tokenlist_t) {NULL, 0};
                    }
                }

                token->argc = argc;
            }

            #ifdef DEBUG
            printf("Made token_t %I64u: { [%s], %I64u }\n", tokenList.count,
                token->value,
                token->hash);
            #endif

            tokenList.tokens[tokenList.count] = token;
            tokenList.count += 1;

            /* Make room for new tokens if the list is full */
            if (tokenList.count >= maxTokens) {
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

        /* Increment by two, so it points to the character after the whitespace */
        startIndex = endIndex + 1;
    }

    return tokenList;
}

/* Return the index one after the end of the next substring */
size_t GetNextEndIndex(char* str, size_t start, size_t len) {

    for (size_t i = start; i < len + 1; ++i) {

        if (isspace(str[i])) {
            return i;
        } else if (i == len) {
            return i;
        }

    }

    return 0;
}

/* iptr is used to update the endpointer in the main function */
data_t* GetNextData(char* str, size_t* iptr, size_t len, uint32_t type) {

    /* return NULL if there's no characters left */
    if (*iptr == len) {
        return NULL;
    }

    data_t *data = malloc(sizeof(data_t));
    data->type = type;

    size_t endIndex;

    /* Keep incrementing *iptr until an endIndex unequal to *iptr is found */
    do {
        *iptr += 1;
        endIndex = GetNextEndIndex(str, *iptr, len);
    } while (*iptr == endIndex);

    /* Copy the text into a temporary variable */
    char* tmp = calloc(endIndex - *iptr + 1, sizeof(char));
    memcpy(tmp, str + *iptr, endIndex - *iptr);

    if (type == DATA_TEXT) {
        data->text = tmp;
    } else {
        data->number = strtod(tmp, NULL);
        free(tmp);
    }

    /* update the main index */
    *iptr = endIndex;
    return data;
}

uint64_t GetHashCode(char *str) {
    uint64_t hash = 5381;
    uint32_t c;

    while ( (c = *str++) ) {
        hash = hash * 33 + c;
    }

    return hash;
}