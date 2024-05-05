#ifndef __STATES_H__
#define __STATES_H__

typedef enum {
    START,
    KEYWORD,
    KEYSYMBOL,
    IDENTIFIER,
    NUMBER,
    COMMENT,
    DONE_KEYWORD,
    DONE_KEYSYMBOL,
    DONE_IDENTIFIER,
    DONE_NUMBER,
    DONE_COMMENT
} State;

#endif