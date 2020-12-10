#include <stdio.h>
#include <stdlib.h>
/*typedef struct att_ { int start; int stop;} att;
void attSel(int N, att* v);
void  attSelR(int pos,att *activity, int *sol,int k , int count);
int overlapA(int n, att *v, int *sol, int pos);
void  attSelRe(int pos,att *activity, int *sol,int * bestsol, int k ,int duratacorrente, int* bestdurata);
int durata(att activity);
att itemScan();

int main() {
    setbuf(stdout,0);
    int maxact;
    int i;
    FILE* fp;
    att* activity;
    fp=fopen("att.txt","r");
    if(fp==NULL)
        exit(1);
    fscanf(fp,"%d",&maxact);
    activity= (att*) malloc(maxact* sizeof(att));
    for (i=0;i<maxact;i++) {
        fscanf(fp, "%d %d\n", &activity[i].start, &activity[i].stop);
    }

    for (i=0;i<maxact;i++)
        printf("%d %d\n",activity[i].start, activity[i].stop);

    attSel(maxact,activity);

    return 0;
}
void attSel(int N, att* activity ) {

    int count=0;
    int* sol = malloc(N*sizeof(int));
    int *bestsol = calloc(N, sizeof(int));
    int duratacorrente=0;
    int bestdurata=0;
    int i;

    attSelRe(0,activity,sol,bestsol,duratacorrente,N,&bestdurata);
    printf("Soluzione a durata complessiva massima %d\n", bestdurata);
    for (i=0; i<N; i++)
        if (bestsol[i])
            printf(" (%d,%d)", activity[i].start, activity[i].stop);
    printf("\n");

}
void  attSelRe(int pos,att *activity, int *sol,int * bestsol, int k ,int duratacorrente, int* bestdurata)
{
    int i;
    if (pos >= k){
            if(*bestdurata<duratacorrente)
            {
                *bestdurata=duratacorrente;
                for (i=0; i<k; i++)
                bestsol[i]=sol[i];
            }
        return ;
    }
    sol[pos]=0;
    attSelRe(pos+1,activity,sol,bestsol,k,duratacorrente,bestdurata);
    if(!overlapA(k,activity,sol,pos)) {
        sol[pos] = 1;
        attSelRe(pos + 1, activity, sol,bestsol, k, duratacorrente+durata(activity[pos]),bestdurata);
        return ;
    }
}
int durata(att activity)
{
    return activity.stop-activity.start;
}

int overlapA(int n, att *v, int *sol, int pos) {
    int i;

    for (i=0; i<pos; i++) {
        if (sol[i] != 0) {
            if (v[i].start< v[pos].stop && v[pos].start < v[i].stop)
                return 1; // se si intersecano non vanno bene
        }
    }
    return 0;
}
*/
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

typedef struct att_ {
    int s, f;
} att;

int dA(att a) {
    return a.f - a.s;
}

att *attLeggi(FILE *in, int *n) {
    int i;
    att *v;
    fscanf(in, "%d\n", n);
    v = calloc(*n, sizeof(att));
    for (i=0; i<*n; i++)
        fscanf(in, "%d %d\n", &v[i].s, &v[i].f);
    return v;
}

int overlapA(int n, att *v, int *sol, int pos) {
    int i;

    for (i=0; i<pos; i++) {
        if (sol[i] != 0) {
            if (v[i].s < v[pos].f && v[pos].s < v[i].f)
                return 1;
        }
    }
    return 0;
}

void attSelR(int pos, int n, att *v, int *sol, int *bestsol,  int currDurata, int *bestDurata) {
    int i;
    if (pos >= n) {
        if (*bestDurata < currDurata) {
            *bestDurata = currDurata;
            for (i=0; i<n; i++)
                bestsol[i] = sol[i];
        }
        return;
    }

    sol[pos] = 0;
    attSelR(pos+1, n, v, sol, bestsol, currDurata, bestDurata);
    if (!overlapA(n, v, sol, pos)) {
        sol[pos] = 1;
        attSelR(pos+1, n, v, sol, bestsol,  currDurata+dA(v[pos]), bestDurata);
    }

    return;
}

void attSel(int n, att *v) {
    int *sol = calloc(n, sizeof(int));
    int *bestsol = calloc(n, sizeof(int));
    int duration = 0, i;

    attSelR(0, n, v, sol, bestsol, 0, &duration);

    printf("Soluzione a durata complessiva massima %d\n", duration);
    for (i=0; i<n; i++)
        if (bestsol[i])
            printf(" (%d,%d)", v[i].s, v[i].f);
    printf("\n");

    free(sol);
    free(bestsol);

    return;
}

int main(int argc, char **argv) {
    int n;
    FILE *in;
    att *v;

    in = fopen("att.txt", "r");
    if (in == NULL)
        exit(-1);

    v = attLeggi(in, &n);
    attSel(n, v);

    fclose(in);
    return 0;
}
