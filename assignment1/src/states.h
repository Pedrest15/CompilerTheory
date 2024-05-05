#ifndef __STATES_H__
#define __STATES_H__

typedef enum {
    START,
    KEYWORD,
    IDENTIFIER,
    COMMENT,
    DONE_KEYWORD,
    DONE_IDENTIFIER,
    DONE_COMMENT
} State;

#endif