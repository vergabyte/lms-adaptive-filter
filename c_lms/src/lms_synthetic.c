#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static double dot(const double* a, const double* b, size_t L){ double s=0.0; for(size_t i=0;i<L;i++) s+=a[i]*b[i]; return s; }

static void usage(const char* prog){
    fprintf(stderr, "Usage: %s --order N --beta B --nsamples M --out DIR\n", prog);
}

int main(int argc, char** argv){
    size_t N = 21;
    double beta = 0.01;
    size_t NS = 2000;
    const char* outdir = "results";

    /* very small CLI (explicit over implicit) */
    for (int i=1;i<argc;i++){
        if (!strcmp(argv[i],"--order") && i+1<argc) N = (size_t)strtoul(argv[++i],NULL,10);
        else if(!strcmp(argv[i],"--beta") && i+1<argc) beta = atof(argv[++i]);
        else if(!strcmp(argv[i],"--nsamples") && i+1<argc) NS = (size_t)strtoul(argv[++i],NULL,10);
        else if(!strcmp(argv[i],"--out") && i+1<argc) outdir = argv[++i];
        else { usage(argv[0]); return 1; }
    }

    FILE* fy = NULL; FILE* fe = NULL; FILE* fw = NULL; FILE* fd = NULL;
    char path[512];
    snprintf(path,sizeof(path),"%s/Y_OUT.txt",outdir);  fy = fopen(path,"w");
    snprintf(path,sizeof(path),"%s/ERROR.txt",outdir);  fe = fopen(path,"w");
    snprintf(path,sizeof(path),"%s/WEIGHTS.txt",outdir); fw = fopen(path,"w");
    snprintf(path,sizeof(path),"%s/DESIRED.txt",outdir); fd = fopen(path,"w");
    if(!fy||!fe||!fw||!fd){ perror("open results"); return 1; }

    /* unknown plant h_true */
    if (N < 3) { fprintf(stderr,"order too small\n"); return 1; }
    double* h_true = calloc(N, sizeof(double));
    h_true[0]=0.5; h_true[1]=-0.3; h_true[2]=0.2;

    /* LMS state */
    double* W = calloc(N, sizeof(double));
    double* X = calloc(N, sizeof(double));
    if(!W||!X||!h_true){ perror("alloc"); return 1; }


    /* main loop */
    unsigned int rng = 12345u;
    for(size_t n=0;n<NS;n++){
        /* reference x[n] white-ish */
        rng = 1664525u*rng + 1013904223u;
        double x_new = ((int)(rng>>1)%2001 - 1000)/1000.0; /* ~[-1,1] */

        /* shift X */
        for(size_t i=N-1;i>0;i--) X[i]=X[i-1];
        X[0]=x_new;

        /* desired d = h_true * X (system ID) */
        double d = dot(h_true, X, N);

        /* output and error */
        double y = dot(W, X, N);
        double e = d - y;

        /* LMS update */
        for(size_t i=0;i<N;i++) W[i] += 2.0 * beta * e * X[i];

        fprintf(fy, "%lf\n", y);
        fprintf(fe, "%lf\n", e);
        fprintf(fd, "%lf\n", d);
    }

    for(size_t i=0;i<N;i++) fprintf(fw,"%zu %lf\n", i, W[i]);

    fclose(fy); fclose(fe); fclose(fw); fclose(fd);
    free(W); free(X); free(h_true);
    return 0;
}
