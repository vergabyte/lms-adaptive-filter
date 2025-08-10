#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void usage(const char* prog){
    fprintf(stderr, "Usage: %s --order N --beta B --input X.txt --desired D.txt --out DIR\n", prog);
}

int main(int argc, char** argv){
    size_t N = 21;
    double beta = 0.01;
    const char* xin = NULL;
    const char* din = NULL;
    const char* outdir = "results";

    for (int i=1;i<argc;i++){
        if (!strcmp(argv[i],"--order") && i+1<argc) N = (size_t)strtoul(argv[++i],NULL,10);
        else if(!strcmp(argv[i],"--beta") && i+1<argc) beta = atof(argv[++i]);
        else if(!strcmp(argv[i],"--input") && i+1<argc) xin = argv[++i];
        else if(!strcmp(argv[i],"--desired") && i+1<argc) din = argv[++i];
        else if(!strcmp(argv[i],"--out") && i+1<argc) outdir = argv[++i];
        else { usage(argv[0]); return 1; }
    }
    if(!xin || !din){ usage(argv[0]); return 1; }

    FILE* fx = fopen(xin,"rt");
    FILE* fd = fopen(din,"rt");
    if(!fx || !fd){ perror("open input"); return 1; }

    char path[512];
    FILE* fy = NULL; FILE* fe = NULL; FILE* fw = NULL; FILE* fdup = NULL;
    snprintf(path,sizeof(path),"%s/Y_OUT.txt",outdir);  fy = fopen(path,"w");
    snprintf(path,sizeof(path),"%s/ERROR.txt",outdir);  fe = fopen(path,"w");
    snprintf(path,sizeof(path),"%s/WEIGHTS.txt",outdir); fw = fopen(path,"w");
    snprintf(path,sizeof(path),"%s/DESIRED.txt",outdir); fdup = fopen(path,"w");
    if(!fy||!fe||!fw||!fdup){ perror("open results"); return 1; }

    double* W = calloc(N, sizeof(double));
    double* X = calloc(N, sizeof(double));
    if(!W || !X){ perror("alloc"); return 1; }

    /* main streaming loop */
    double x_new = 0.0, d = 0.0;
    while (fscanf(fx, "%lf", &x_new) == 1 && fscanf(fd, "%lf", &d) == 1){
        for(size_t i=N-1;i>0;i--) X[i]=X[i-1];
        X[0] = x_new;

        double y = 0.0;
        for(size_t i=0;i<N;i++) y += W[i]*X[i];

        double e = d - y;
        for(size_t i=0;i<N;i++) W[i] += 2.0 * beta * e * X[i];

        fprintf(fy, "%lf\n", y);
        fprintf(fe, "%lf\n", e);
        fprintf(fdup, "%lf\n", d);
    }

    for(size_t i=0;i<N;i++) fprintf(fw, "%zu %lf\n", i, W[i]);

    fclose(fx); fclose(fd);
    fclose(fy); fclose(fe); fclose(fw); fclose(fdup);
    free(W); free(X);
    return 0;
}
