// a process scheduler from my side
// baqi ap ne khud implement krne hain

#include "process_scheduler.h"
#include <stdlib.h>
#include <string.h>

static _sched_shadow_t _mx[_P_MAX];
static unsigned long long _g_clk = 0;
static int _l_pid[_MLFQ_L];

#define _Z(x) ((x) ? (x) : 0)
#define _Q_SZ(x) (_Q_BS << (x))
#define _VALID(p) ((p) && (p)->pcb.status != TERMINATED)
#define _ID(p) ((p)->pcb.pid)
#define _S(p) (_mx[_ID(p)])
#define _ABS(x) ((x) < 0 ? -(x) : (x))

static inline void _rst(int pid) { int x=pid; _mx[x]._t_sl=_Q_SZ(0); _mx[x]._q_idx=0; _mx[x]._t_tot=0; _mx[x]._l_run=0; }

static inline struct Node* _w(struct Node* _h, int _q, int _lp) {
    struct Node* _c = _h, *_can = NULL;
    int _f = 0;
    for (; _c; _c = _c->next) {
        if (!_VALID(_c)) continue;
        if (_c->pcb.priority != _q && _S(_c)._q_idx != (unsigned int)_q) continue; 
        if (_c->pcb.status == NEW && _S(_c)._t_tot == 0) _rst(_ID(_c));
        if (_c->pcb.status == NEW) _c->pcb.status = READY; 
        if (_c->pcb.status != READY && _c->pcb.status != RUNNING) continue;
        
        if (!_can) _can = _c; 
        if (_ID(_c) > _lp) { _can = _c; _f=1; break; }
    }
    return _f ? _can : (_can ? _can : NULL);
}

void sched_init(void) {
    memset(_mx, 0, sizeof(_mx));
    for(int i=0; i<_MLFQ_L; i++) _l_pid[i] = -1;
}

void sched_update(struct Node* _p, int _t) {
    if (!_p) return;
    
    _S(_p)._t_tot += _t;
    _S(_p)._t_sl = (_S(_p)._t_sl > (unsigned int)_t) ? (_S(_p)._t_sl - _t) : 0;
    _p->pcb.burstTime = (_p->pcb.burstTime > _t) ? (_p->pcb.burstTime - _t) : 0;
    _g_clk += _t;

    if (_p->pcb.burstTime <= 0) {
        _p->pcb.status = TERMINATED;
        return;
    }

    if (_S(_p)._t_sl == 0) {
        if (_S(_p)._q_idx < _MLFQ_L - 1) {
             _S(_p)._q_idx++;
             _p->pcb.priority = _S(_p)._q_idx; 
        }
        _S(_p)._t_sl = _Q_SZ(_S(_p)._q_idx);
    }
}

void sched_boost(void) {
    for (struct Node* _it = getProcessHead(); _it; _it = _it->next) {
        if (_VALID(_it) && _ID(_it) < _P_MAX) {
            _S(_it)._q_idx = 0;
            _S(_it)._t_sl = _Q_SZ(0);
            _it->pcb.priority = 0;
        }
    }
}

struct Node* sched_next(void) {
    if ((++_g_clk % _BST_T) == 0 && _g_clk > 0) sched_boost();

    for (int _q = 0; _q < _MLFQ_L; _q++) {
        struct Node* _tgt = _w(getProcessHead(), _q, _l_pid[_q]);
        if (_tgt) {
            _l_pid[_q] = _ID(_tgt);
            _S(_tgt)._l_run = _g_clk;
            return _tgt;
        }
    }


    /* ================= FCFS Scheduling ================= */

/* Scheduler: Select next READY process (FCFS) */
int scheduleNextProcessFCFS(void)
{
    struct Node *temp = head;

    while (temp != NULL) {
        if (temp->pcb.status == READY)
            return temp->pcb.pid;
        temp = temp->next;
    }

    return -1;  // No READY process
}
/* =================  Dispatching FCFS ================= */

void dispatchFCFS(void)
{
    int pid = scheduleNextProcessFCFS();

    if (pid == -1) {
        printf("No READY process available for FCFS\n");
        return;
    }
/* =================  get TABLECOUNT ================= */

    int getprocessTableCount() {
    struct Node* temp = getProcessHead();
    int count = 0;
    while (temp != NULL) {
        if (temp->pcb.status != TERMINATED) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}
    return NULL;
}
