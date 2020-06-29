
#ifndef EXAMPLE_CONECTIVIDADE_H
#define EXAMPLE_CONECTIVIDADE_H
#include "Graph.h"
#include <vector>
#include "algorithm"

void LargeSSCFilterGraph(Graph<int> &gr);
template<class T>
void KosarajuGetMaxSizeStrongCC(Graph<T> &graph,vector<int> &res);
vector<int> getMaxSizeKosarajuStrongCC(vector<vector<int>> &SCCs);
void printSSCKosaraju(vector<vector<int> > &aux);
void printAllSccKosaraju(vector<vector<int> > &aux);
void FastSSCKosorajuFilter(vector<int> &aux,Graph<int> &gr);
void printMaxSizeSccKosoraju(vector<int> &res);
#endif //EXAMPLE_CONECTIVIDADE_H
