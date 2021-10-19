#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "processes.h"

struct proc {
    int pid;
    int ppid;
    char user[9];
    int priority;
    float cpu_usage;
    long int rss;
    long int size;
    long int vsize;
    char command[16];
    struct proc * next;
};

struct processes {
    struct proc * first;
    struct proc * last;
};

struct query_result {
    struct query query;
    struct proc * result;
};

struct processes * new_processes() {
    struct processes * this = malloc(sizeof(*this));
    if (this) {
	this->first = 0;
	this->last = 0;
    };
    return this;
}

void delete(struct processes * this) {
    clear(this);
    free(this);
}

void clear(struct processes * this) {
    struct proc * p = this->first;
    while (p) {
	struct proc * tmp = p;
	p = p->next;
	free(tmp);
    }
    this->first = 0;
    this->last = 0;
}

int add_from_file(struct processes * this, const char * filename) {
    FILE * f = fopen(filename, "r");
    if (!f) 
	return 0;

    struct proc p;
    while (fscanf(f, "%d %d %8s %d %f %ld %ld %ld %15s",
		  &(p.pid), &(p.ppid), p.user, &(p.priority), &(p.cpu_usage),
		  &(p.rss), &(p.size), &(p.vsize), p.command) == 9) {
	struct proc * new_p = malloc(sizeof(struct proc));
	if (!new_p) {
	    fclose(f);
	    return 0;
	}
	memcpy(new_p, &p, sizeof(*new_p));
	new_p->next = 0;
	if (this->last) {
	    this->last->next = new_p;
	    this->last = new_p;
	} else {
	    this->first = new_p;
	    this->last = new_p;
	}
    }
    fclose(f);
    return 1;
}

static int match(const struct proc * p, const struct query * q) {
    if (q->priority > 0) {
	if (q->priority != p->priority)
	    return 0;
    } else if (q->priority < 0) {
	if (-q->priority > p->priority)
	    return 0;
    }
    if (q->rss > 0) {
	if (q->rss != p->rss)
	    return 0;
    } else if (q->rss < 0) {
	if (-q->rss > p->rss)
	    return 0;
    }
    if (q->size > 0) {
	if (q->size != p->size)
	    return 0;
    } else if (q->size < 0) {
	if (-q->size > p->size)
	    return 0;
    }
    if (q->vsize > 0) {
	if (q->vsize != p->vsize)
	    return 0;
    } else if (q->vsize < 0) {
	if (-q->vsize > p->vsize)
	    return 0;
    }
    if (q->cpu_usage > 0) {
	if (q->cpu_usage != p->cpu_usage)
	    return 0;
    } else if (q->cpu_usage < 0) {
	if (-q->cpu_usage > p->cpu_usage)
	    return 0;
    }
    return 1;
}

struct query_result * search(struct processes * this, const struct query * q) {
    for (struct proc * p = this->first; p != 0; p = p->next) {
	if (match(p, q)) {
	    struct query_result * r = malloc(sizeof(struct query_result));
	    if (!r)
		return 0;
	    r->query.priority = q->priority;
	    r->query.rss = q->rss;
	    r->query.size = q->size;
	    r->query.vsize = q->vsize;
	    r->query.cpu_usage = q->cpu_usage;
	    r->result = p;
	    return r;
	}
    }
    return 0;
}

int get_pid(struct query_result * r) { return r->result->pid; }
int get_ppid(struct query_result * r) { return r->result->ppid; }
const char * get_user(struct query_result * r) { return r->result->user; }
int get_priority(struct query_result * r) { return r->result->priority; }
float get_cpu_usage(struct query_result * r) { return r->result->cpu_usage; }
long int get_rss(struct query_result * r) { return r->result->rss; }
long int get_size(struct query_result * r) { return r->result->size; }
long int get_vsize(struct query_result * r) { return r->result->vsize; }
const char * get_command(struct query_result * r) { return r->result->command; }

struct query_result * next(struct query_result * r) {
    for (struct proc * p = r->result->next; p != 0; p = p->next) {
	if (match(p, &(r->query))) {
	    r->result = p;
	    return r;
	}
    }
    free(r);
    return 0;
}

void terminate_query(struct query_result * r) {
    free(r);
}

