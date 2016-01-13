#include <iostream>
#include <fstream>
#define Max 400


using namespace std;

class Loading{
    friend int MaxLoading(int w[],int c, int n,int bestx[]);

private:
    void Backtrack(int i);
    int n;//集装箱数
    int *w;//集装箱重量数组
    int c;//第一艘轮船的载重量
    int cw;//当前载重量
    int bestw;//当前最优载重量
    int r;//剩余集装箱的重量
    int *x;//当前解
    int *bestx;//当前最优解
};

int MaxLoading(int w[],int c,int n,int bestx[]){//返回最右载重量
    ofstream Outfile("/Users/CristinaSt/Documents/算法设计/test6/test2.txt");
    Loading X;
    X.x = new int[n+1];
    X.w = new int[n+1];
    X.bestx = new int[n+1];
    X.w = w;
    X.c = c;
    X.n = n;
    X.bestx = bestx;
    X.bestw = 0;
    X.cw = 0;
    X.r = 0;
    for (int i = 1; i <=n ; ++i) {
        X.r+=w[i];
    }

    //计算最右载重量
    X.Backtrack(1);
    for (int j = 1; j <=n ; ++j) {
        cout<<X.bestx[j]<<" ";
        Outfile<<X.bestx[j];
    }
    delete[]X.w;
    delete[]X.bestx;
    delete[] X.x;
    return X.bestw;
}

void Loading::Backtrack(int i) {
//搜索第i层
    if(i>n) {//到达叶结点
        if(cw > bestw){
            for (int j = 1; j <=n ; ++j)
                bestx[j] = x[j];
            bestw = cw;
        }
        return;
    }
    r-=w[i];
    //搜索子树
    if(cw + w[i]<=c){
        x[i] = 1;
        cw += w[i];
        Backtrack(i+1);
        cw -= w[i];
    }
    if(cw + r > bestw) {
        x[i] = 0;
        Backtrack(i+1);
    }
    r+= w[i];
}

int main() {
    fstream Infile("/Users/CristinaSt/Documents/算法设计/test6/test1.txt");
    int A[Max]{};
    int pos = 0;
    int *w;
    int *bestx;
    int n;
    int c;

    while(!Infile.eof()){
        Infile>>A[pos];
        pos++;
    }
    n = A[0];
    c = A[1];
    w = new int[n];
    bestx = new int[n+1];
    bestx[0] = 0;
    for (int i = 2; i <pos ; ++i) {
        w[i-1] = A[i];
        cout << w[i-1]<<" ";
    }
    cout <<endl;
    cout <<MaxLoading(w,c,n,bestx)<<endl;

    return 0;
}