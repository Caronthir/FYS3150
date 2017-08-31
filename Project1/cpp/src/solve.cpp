#include <armadillo>
#include "solve.h"

arma::vec thomas(const arma::vec& a, const arma::vec& b, const arma::vec& c, const arma::vec& f){
    /* Implementation of Thomas Algorithm as described p. 186*/
    if(arma::numel(a) != arma::numel(b) ||
       arma::numel(b) != arma::numel(c) ||
       arma::numel(c) != arma::numel(f))
        throw std::runtime_error("Input vectors must be of equal length");

    const size_t n   = arma::numel(a);
    arma::vec tmp    = arma::zeros(n);
    arma::vec u      = arma::zeros(n);

    // Forward sweep
    double btmp = b[1];
    u[1]        = f[1]/btmp;
    for(unsigned int i = 2; i <= n-2; i++){
        tmp[i] = c[i-1]/btmp;
        btmp   = b[i]-a[i]*tmp[i];
        u[i]   = (f[i]-a[i]*u[i-1])/btmp;
    }

    // Backward substitution
    for(unsigned int i = n-3; i > 0; i--)
        u[i] -= tmp[i+1]*u[i+1];

    return u;
}


arma::mat tridiagonalMat(unsigned int size, double upper, double middle, double lower){
    auto mat = arma::mat(size, size, arma::fill::zeros);
    for (unsigned int row = 1; row < size-1; row++){
        if (row > 0)
            mat(row, row-1) = lower;
        mat(row, row) = middle;
        if (row < size-1)
            mat(row, row+1) = upper;
    }

    // Ensure the boundary conditions
    mat(0,0) = 1;
    mat(size-1, size-1) = 1;
    return mat;
}


arma::vec thomasSpecial(const arma::vec& v){

    const size_t n   = arma::numel(v);
    arma::vec u      = arma::zeros(n);
    double bprime;
    arma::vec c      = arma::zeros(n);

    u[1] = v[1];
    bprime = 2;
    for(unsigned int i = 2; i <= n-2; i++){
        c[i]      = -1.0/bprime;
        bprime    = (i+1.0)/i;
        u[i]      = (v[i]+u[i-1])/bprime;
    }
    for(unsigned int i = n-3; i > 0; i--){
      u[i] = u[i] - c[i]*u[i+1];
    }
    return u;
}