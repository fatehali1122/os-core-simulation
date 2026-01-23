#ifndef PROCESS_SCHEDULER_H
#define PROCESS_SCHEDULER_H

#include "process.h"

#define _MLFQ_L 4
#define _Q_BS 2
#define _BST_T 200
#define _P_MAX 1024

typedef struct {
    unsigned int _t_sl;
    unsigned int _t_tot;
    unsigned int _l_run;
    unsigned int _q_idx;
    unsigned int _f_blk; 
} _sched_shadow_t;

void sched_init(void);
struct Node* sched_next(void);
void sched_update(struct Node* _p, int _t);
void sched_boost(void);

#endif

