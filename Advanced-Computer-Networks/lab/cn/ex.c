<<<<<<< HEAD
#include<stdio.h>
int main()
{  int i=0;
	printf("%d,%d,%d",i++,i,--i);
	return 0;

=======
#include "stdio.h"
#include "time.h"
#include "stdint.h"
#include "sys/time.h"
#include "unistd.h"
#include "math.h"

int64_t findCRT(unsigned int k, int64_t* n,int64_t m,int64_t* prod, int64_t c[k][k],int64_t* Y){
    int64_t i,j,value=0,r[k][k];
    for(j=0;j<k;j++) r[j][0]=Y[j];

    for(i=1;i<k;i++){
        for(j=0;j<i;j++){
            r[i][j+1]=((r[i][j]-r[j][j])*c[i][j])%n[i];
            if(r[i][j+1]<0)
                r[i][j+1]=(r[i][j+1]+n[i])%n[i];
            }
    }
    for(i=0;i<k;i++){
        value+=r[i][i]*(prod[i]);
    }
    return value%m;
}
//Parameters pointing to moduli, array to store RNS rep and input x
void findRNS(int64_t* m,int64_t* X,int64_t x,unsigned int k){
    int i;
    for(i=0;i<k;i++){
        X[i]=x % m[i];
        if(X[i]<0)
                X[i]= (X[i]+m[i])%m[i];
    }
}

// C function for extended Euclidean Algorithm
int64_t findGCD(int64_t a, int64_t b, int64_t *x, int64_t *y){
    // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    int64_t x1, y1; // To store results of recursive call
    int64_t gcd = findGCD(b%a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

main() {
    int loop;
    double RNS=0,BDK=0,BDK_Stime=0,BDK_Ttime=0;
    clock_t start,stop;
    unsigned int k=5; //m[]={1073741789,1073741783,1073741741,1073741723,1073741719};
    int64_t m[]={3,7,13,19,29},m_BDK,M[]={3,7,13,19,29},p_BDK,P[]={5,11,17,23,31},m_P_inv,prod;
    int64_t i,j,a=26386,b=72931,n=14527,r,kk,gcd,c=26386,d=72931,o=14527;
    //Declaring arrays to store RNS representation of inputs
    int64_t A[k],B[k],N[k],R[k],N_bar[k],R_inv[k],T[k],Q[k],T_bar[k],C_M[k],C_P[k],D_M[k],D_P[k],O_M[k],O_P[k],O_M_inv[k],C_M_neg[k],S[k],r_MRC[k][k],r_p_MRC[k][k],c_ij[k][k],S_MRC[k],M_ji[k-1][k],P_ji[k-1][k],S_P[k],M_P_inv[k],T_M[k],T_P[k],T_MRC[k]; //Note to prof: Mistake in Step5 - Should be T = (A.B+Q.N).R^-1. Defined T_bar[] to store A.B
    int64_t steps =6;
    double time_mat[steps][k];
    for(i=0;i<steps;i++){
        for(j=0;j<k;j++){
            time_mat[i][j] = 0;
        }
    }
    int64_t c_crt[k][k],c_p_crt[k][k],prod_p_crt[k],prod_crt[k],ex[]={2,1,1};
    int64_t m_crt=1,m_p_crt,t_crt,t_p_crt;
    for(i=0;i<k;i++){
        m_crt = m_crt * m[i];
        m_p_crt = m_p_crt * P[i];
    }
    for(i=1;i<k;i++){
        for(j=0;j<i;j++){
            gcd=findGCD(m[j],m[i],&c_crt[i][j],&t_crt);
            if(c_crt[i][j]<0) c_crt[i][j]= (c_crt[i][j]+m[i])%m[i];
            gcd=findGCD(P[j],P[i],&c_p_crt[i][j],&t_p_crt);
            if(c_p_crt[i][j]<0) c_p_crt[i][j]= (c_p_crt[i][j]+P[i])%P[i];
            //printf("%lld \n",c_crt[i][j]);
        }
    }
    for(i=0;i<k;i++){
        prod_crt[i]=1;
        prod_p_crt[i]=1;
        for(j=0;j<i;j++){
            prod_crt[i]*=m[j];
            prod_p_crt[i]*=P[j];
        }
        //printf("%lld \n",prod_crt[i]);
    }
    a=19;b=21;n=29;c=26386;d=72931;o=14527;
    for(loop=0;loop<100000;loop++){

        findRNS(m,A,a,k);
        findRNS(m,B,b,k);
        findRNS(m,N,n,k);
        int64_t r_hat,n_hat,n_bar,t,q;
        kk=floor(log(n)/log(2)+1);
        r=pow(2,kk);
        findRNS(m,R,r,k);
        gcd=findGCD(r,n,&r_hat,&n_hat);
        n_bar= -n_hat;
        if(n_bar<0){
            n_bar+=r;
        }
        findRNS(m,N_bar,n_bar,k);
        for(i=0;i<k;i++){
            gcd=findGCD(R[i],m[i],&R_inv[i],&n_hat);
            if(R_inv[i]<0) R_inv[i]=(R_inv[i]+m[i])%m[i];
        }
        //Step1 of RNS
        for(i=0;i<k;i++){
            start=clock();
            T_bar[i]=(A[i]*B[i])%m[i];
            T[i]=(A[i]*B[i]*N_bar[i])%m[i];
            //printf("%lld %lld %lld %lld \n",A[i],B[i],N_bar[i],T[i]);
            stop=clock();
            time_mat[0][i]+=(double)(stop-start)/CLOCKS_PER_SEC;
        }
        start=clock();
        //Step2
        t=findCRT(k,m,m_crt,prod_crt,c_crt,T);
        //printf("t=%lld \n",t);
        //Step3
        q=t%r;
        //Step4
        findRNS(m,Q,q,k);
        stop=clock();
        RNS+=(double)(stop-start)/CLOCKS_PER_SEC;
        //Step5
        for(i=0;i<k;i++){
            start=clock();
            T[i]=((T_bar[i]+Q[i]*N[i])*R_inv[i])%m[i];
            //printf("%lld %lld %lld %lld \n",Q[i],N[i],R_inv[i],T[i]);
            stop=clock();
            time_mat[1][i]+=(double)(stop-start)/CLOCKS_PER_SEC;
        }

        //Implementation of BDK
        //Setup steps
        findRNS(M,C_M,c,k);
        findRNS(P,C_P,c,k);
        findRNS(M,D_M,d,k);
        findRNS(P,D_P,d,k);
        findRNS(M,O_M,o,k);
        findRNS(P,O_P,o,k);
        for(i=0;i<k;i++){
            gcd=findGCD(O_M[i],M[i],&O_M_inv[i],&n_hat);
            if(O_M_inv[i]<0) O_M_inv[i]=(O_M_inv[i]+M[i])%M[i];
            //printf("%lld \n",O_M_inv[i]);
        }
        for(i=0;i<k;i++)  C_M_neg[i]=M[i]-C_M[i];
        //Step1
        for(i=0;i<k;i++) {
            start=clock();
            S[i]=(C_M_neg[i]*D_M[i]*O_M_inv[i])%M[i];
            stop=clock();
            time_mat[2][i]+=(double)(stop-start)/CLOCKS_PER_SEC;
            //printf("%lld \n",S[i]);
        }
        //Step2 - Basis Conversion from M to P
        start=clock();
        for(j=0;j<k;j++) r_MRC[j][0]=S[j];

        for(i=1;i<k;i++){
            for(j=0;j<i;j++){
                r_MRC[i][j+1]=(((r_MRC[i][j]-r_MRC[j][j])*c_crt[i][j])%M[i]);
                if(r_MRC[i][j+1] < 0) r_MRC[i][j+1] = (r_MRC[i][j+1]+M[i])%M[i];
                //printf("c_ij[i][j] - %llu , rij - %llu \n",c_crt[i][j],r_MRC[i][j+1]);
                }
        }

        for(i=0;i<k;i++){
            S_MRC[i]=r_MRC[i][i];
        }
        stop=clock();
        BDK_Stime+=(double)(stop-start)/CLOCKS_PER_SEC;
        //precomputing M_ji
        for(i=1;i<k;i++){
            prod=1;
            for(j=0;j<i;j++){
                prod*=M[j];
            }
            findRNS(P,&M_ji[i-1],prod,k);
            //printf("%lld %lld %lld %lld %lld\n",M_ji[i-1][0],M_ji[i-1][1],M_ji[i-1][2],M_ji[i-1][3],M_ji[i-1][4]);
            //value+=r[i][i]*prod;
        }
        //Comverting S from M to P (Actual Step2)
        for(i=0;i<k;i++){
            start=clock();
            S_P[i]=S_MRC[0];
            for(j=1;j<k;j++){
                S_P[i]+=M_ji[j-1][i]*S_MRC[j];
                //printf("%lld %lld \n",M_ji[j-1][i],S_MRC[j]);
            }
            S_P[i]=S_P[i]%P[i];
            //printf("%lld \n",S_P[i]);
            stop=clock();
            time_mat[3][i]+=(double)(stop-start)/CLOCKS_PER_SEC;
        }
        //Computation of T
        m_BDK=1;p_BDK=1;
        for(i=0;i<k;i++){
            m_BDK*=M[i];
            p_BDK*=P[i];
        }
        //printf("%lld \n",m_BDK);
        gcd=findGCD(m_BDK,p_BDK,&m_P_inv,&n_hat);
        findRNS(P,M_P_inv,m_P_inv,k);
        //Step3
        for(i=0;i<k;i++){
            start=clock();
            T_P[i]=((C_P[i]*D_P[i]+S_P[i]*O_P[i])*M_P_inv[i])%P[i];
            //printf("%lld \n",T_P[i]);
            stop=clock();
            time_mat[4][i]+=(double)(stop-start)/CLOCKS_PER_SEC;
        }
        //Step4
        //Conversion from P to M
        start=clock();
        //for(j=0;j<k;j++) r_p_MRC[j][0]=T_P[j];
        r_p_MRC[0][0]=T_P[0];

        for(i=1;i<k;i++){
            r_p_MRC[i][0]=T_P[i];
            for(j=0;j<i;j++){
                r_p_MRC[i][j+1]=(((r_p_MRC[i][j]-r_p_MRC[j][j])*c_p_crt[i][j])%P[i]);
                if(r_p_MRC[i][j+1]<0)
                    r_p_MRC[i][j+1]=(r_p_MRC[i][j+1]+P[i])%P[i];
                //printf("c_ij[i][j] - %llu , rij - %llu \n",c_p_crt[i][j],r_p_MRC[i][j+1]);
            }
            T_MRC[i]=r_p_MRC[i][i];
        }
        stop=clock();
        BDK_Ttime+=(double)(stop-start)/CLOCKS_PER_SEC;
        //precomputation of P_jis
        for(i=1;i<k;i++){
            prod=1;
            for(j=0;j<i;j++){
                prod*=P[j];
            }
            findRNS(M,&P_ji[i-1],prod,k);
        }
        //Actual Step4
        for(i=0;i<k;i++){
            start=clock();
            T_M[i]=T_MRC[0];
            for(j=1;j<k;j++){
                T_M[i]+=P_ji[j-1][i]*T_MRC[j];
                //printf("%lld %lld \n",M_ji[j-1][i],S_MRC[j]);
            }
            T_M[i]=T_M[i]%M[i];
            //printf("%lld \n",T_M[i]);
            stop=clock();
            time_mat[5][i]+=(double)(stop-start)/CLOCKS_PER_SEC;
        }
    }
    double avg;
    for(i=0;i<2;i++){
        avg=0;
        for(j=0;j<k;j++){
            avg+=(time_mat[i][j])/k;
        }
        RNS+=avg;
    }
    for(i=2;i<steps;i++){
        avg=0;
        for(j=0;j<k;j++){
            avg+=(time_mat[i][j])/k;
        }
        BDK+=avg;
    }
    printf("RNS time: %f, BDK time: %f, BDK_Stime: %f, BDK_Ttime: %f ",RNS,BDK,BDK_Stime/k,BDK_Ttime/k);
>>>>>>> 94764a0a8a4c28d0a16f07b1bf81b6876a90c060
}