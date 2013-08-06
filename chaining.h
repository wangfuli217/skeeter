#ifndef _CHAINING_H
#define _CHAINING_H

#include <limits.h>
#include <event2/bufferevent.h>

#if INT_MAX <= SHRT_MAX
#error "need arch where short is shorter than int"
#endif

typedef enum {
    CHAIN_DONE,
    CHAIN_ERROR,
    CHAIN_ABORT,
    CHAIN_AGAIN,
    CHAIN_MASK = 0xff * (SHRT_MAX + 1),
} chain_result;

struct chain;

typedef int (*chain_process)(struct chain *, struct bufferevent *, void *);
typedef int (*chain_except)(struct chain *, struct bufferevent *, int, void *);

int chain_add(struct chain *, chain_process, chain_except, void *);
struct chain *chain_new(chain_except, void *);
int chain_activate(struct chain *, struct bufferevent *, short);
void chain_run(struct bufferevent *, void *);
void chain_abort(struct chain *, struct bufferevent *);
void chain_destroy(struct chain *);

#endif /* _CHAINING_H */
