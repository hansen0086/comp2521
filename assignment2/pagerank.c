#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int numberOfUrlsInCollection()
{
  FILE *f = fopen("collection.txt","r");
  char buf[1000];
  int count = 0;
  while(fscanf(f, "%s", buf)==1)
  {
    count++;
  }
  fclose(f);
  return count;
}
char** readUrlsInCollection(int num_urls)
{
  char** urls = malloc(num_urls * sizeof(char*));
  FILE *f = fopen("collection.txt","r");
  char buf[1000];
  int i = 0;
  while(fscanf(f, "%s", buf)==1)
  {
    strcpy(urls[i],buf);
    
    i++;
  }
  fclose(f);
  return urls;
}
int indexOfUrl(char** urls, int num_urls, char* url)
{
  int i;
  for(i = 0; i<num_urls; i++)
  {
    if(strcmp(urls[i], url) == 0)
    {
      return i;
    }
  }
  return -1;
}
//TODO
int** createAdjMatrix(int v)
{
  int** m = malloc(v * sizeof(int*));
  int i;
  for(i = 0;i<v;i++)
  {
    m[i] = calloc(v, sizeof(int));
  }
  return m;
}
void fillAdjMatrix(char** urls, int num_urls, int** m)
{
  int i;
  for(i = 0; i < num_urls; i++)
  {
    char fname[1000];
    sprintf(fname, "%s.txt", urls[i]);
    FILE *f = fopen(fname,"r");
    fscanf(f, "#start Section-1");
    char buf[1000];
    while(fscanf(f, "%s", buf)==1 && strcmp(buf,"#end") != 0)
    {
      m[i][indexOfUrl(urls, num_urls, buf)] = 1;
    }
    fclose(f);
  }
}
void printMatrix(int**m, int num_urls)
{
  for(int i = 0; i < num_urls; i++)
  {
    for(int j = 0; j < num_urls; j++)
    {
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }
}

int calculateInlinks(int num_urls, int** m, int v)
{
  int count=0, i;
  for(i = 0; i < num_urls; i++)
  {
    if(i!=v){
    count += m[i][v];
    }
  }
  return count;
}
int calculateOutlinks(int num_urls, int** m, int v)
{
  int count=0, i;
  for(i = 0; i < num_urls; i++)
  {
    if(i!=v)
    {
      count += m[v][i];
    }
  }
  return count;
}
double calculateOutlinksNonZero(int num_urls, int** m, int v)
{
  int outlinks=calculateOutlinks(num_urls,m,v);
  if(outlinks == 0)
  {
    return 0.5;
  }else
  {
    return outlinks;
  }
}
double calculateWin(int num_urls, int** m, int v, int u)
{
  double denom = 0;
  int i;
  for(i = 0; i < num_urls; i++)
  {
    if (m[v][i] == 1 && i!=v)
    {
      denom += calculateInlinks(num_urls, m, i);
    }
  }
  return calculateInlinks(num_urls, m, u) / denom;
}
double calculateWout(int num_urls, int** m, int v, int u)
{
  double denom = 0;
  int i;
  for(i = 0; i < num_urls; i++)
  {
    if (m[v][i] == 1 && i != v)
    {
      denom += calculateOutlinksNonZero(num_urls, m, i);
    }
  }
  return calculateOutlinksNonZero(num_urls, m, u) / denom;
}
double* calculatePagerank(int num_urls, int**m, double d, double diffPR, int maxIterations)
{
  double* newPR = malloc(num_urls * sizeof(double));
  double* oldPR = malloc(num_urls * sizeof(double));
  int i, j, iteration = 0;
  double diff = diffPR;

  for(i = 0; i < num_urls; i++)
  {
    newPR[i] = 1.0 / num_urls;
  }

  while(iteration < maxIterations && diff >= diffPR)
  {
    iteration++;
    for(i= 0;i<num_urls;i++)
    {
      oldPR[i] = newPR[i];
    }

    for(i=0;i<num_urls;i++)
    {
      newPR[i] = 0;
      for(j=0;j<num_urls;j++)
      {
        if(m[j][i]==1 && i !=j)
        {
          newPR[i] += oldPR[j]*calculateWin(num_urls,m,j,i)*calculateWout(num_urls,m,j,i);
        }
      }
      newPR[i] = (1.0 - d)/num_urls + d*newPR[i];
    }

    diff = 0;
    for(i = 0;i<num_urls;i++)
    {
      diff += fabs(newPR[i]-oldPR[i]);
    }
  }

  free(oldPR);
  return newPR;
}

typedef struct Page {
  char* name;
  int outlinks;
  double pagerank;
} Page;

int comparePages(const void* va, const void* vb)
{
  const Page* a = va;
  const Page* b = vb;
  if(a->pagerank < b->pagerank)
  {
    return 1;
  }else if(a->pagerank > b->pagerank)
  {
    return -1;
  }else
  {
    return 0;
  }
}

int main (int argc, char* argv[]) {
  int num_urls = numberOfUrlsInCollection();
  char** urls = readUrlsInCollection(num_urls);
  int** m = createAdjMatrix(num_urls);
  fillAdjMatrix(urls, num_urls, m);

  //printMatrix(m,num_urls);

  double d, diffPR;
  int maxIterations;
  sscanf(argv[1], "%lf", &d);
  sscanf(argv[2], "%lf", &diffPR);
  sscanf(argv[3], "%d", &maxIterations);

  double* pageranks = calculatePagerank(num_urls, m, d, diffPR, maxIterations);

  Page* pages = malloc(num_urls * sizeof(Page));

  int i;
  for(i=0;i<num_urls;i++)
  {
    pages[i].name = urls[i];
    pages[i].outlinks = calculateOutlinks(num_urls, m, i);
    pages[i].pagerank = pageranks[i];
  }

  qsort(pages, num_urls, sizeof(Page), comparePages);

  FILE *f = fopen("pagerankList.txt", "w");
  for(i=0;i<num_urls;i++)
  {
    fprintf(f, "%s, %d, %.8lf\n", pages[i].name, pages[i].outlinks, pages[i].pagerank);
  }

  return 0;
}
