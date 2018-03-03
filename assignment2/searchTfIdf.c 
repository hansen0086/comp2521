//written by Hansen Liu
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define WORD_LENGTH 100
#define MAX_CHARACTER_IN_A_LINE 1000
#define MAX_KEYWORDS 100
#define URL_LENTH 10

typedef struct node 
{
   char url_name[50];
   int search_terms;
   double page_rank;
   struct url_node *next;
   
}node;

int numberOfUrlsInCollection();
void readUrlsInCollection(int num_urls,char urls[][URL_LENTH]);
void print_array(char array[][URL_LENTH],int size);
int merge_array(char array1[][URL_LENTH],int size1, char array2[][URL_LENTH],int size2,char result_array[][URL_LENTH]);
int find_search_terms(char* urlname, char*keyword);
double find_page_rank(char *url);
void print_struct_url(struct node *url,int size);//debugg thing
void normalize(char *p);
int compare_by_search_terms(const void *url1,const void *url2);
int compare_by_page_rank(const void *url1,const void *url2);

int main (int argc, char* argv[])
{
   int i,j=0;
   if(argc<2)
   {
      printf("Usage:./searchPagerank keyword1 keyword2...");
      return 0;
   }
  // printf("haha\n");
   for(i=1;i<argc;i++)
   {
      //printf("normalizing %s\n",argv[i]);
      normalize(argv[i]);
      //printf("argv[i] is now %s\n",argv[i]);
   }
   
   
   int num_urls = numberOfUrlsInCollection();
   char left_urls[num_urls][URL_LENTH];
   int left_urls_size = num_urls;
   char result_urls[num_urls][URL_LENTH];
   
   char keyword_urls[num_urls][URL_LENTH];// char keyword_urls[][] is the unsorted url array of each search terms
   
   readUrlsInCollection(num_urls,left_urls);
   
   readUrlsInCollection(num_urls,result_urls);//char result_urls[][] will be the unsorted url array containing at least one of each search term
   int keyword_urls_counter=0;
   int result_urls_size =num_urls;
   char keyline[MAX_CHARACTER_IN_A_LINE];
   char keyword[WORD_LENGTH];
   char tempword[MAX_CHARACTER_IN_A_LINE];
   char temp_url[100];
   int keyword_counter =1;
   FILE *index = fopen("invertedIndex.txt","r");
   
   FILE* temp_file;
   //search for each keyword to generate a result_urls[]
   //printf("argc is %d\n",argc);
   for(keyword_counter=1; keyword_counter<argc; keyword_counter++ )
   {
      //printf("keyword_counter %d is <= argc %d\n",keyword_counter,argc);
      //printf("searching for %s\n", argv[keyword_counter]);
      strcpy(keyword,argv[keyword_counter]);
      //printf("Looking for %s\n",keyword);
      //save each line in the file to keyline
      rewind(index);
      while((fgets(keyline, MAX_CHARACTER_IN_A_LINE,index))!=NULL)
      {
         //printf("current line:%s\n",keyline);
         
         sscanf(keyline,"%s",tempword);
         //printf("tempword is %s\n",tempword);
         if(0==strcmp(tempword, keyword))
         {
               //write this line into a temp_file
               temp_file = fopen("temp_file.txt","w+");
               
               fprintf(temp_file,"%s",keyline);
               fclose(temp_file);
               temp_file = fopen("temp_file.txt","r");
               fscanf(temp_file,"%s",temp_url);
               keyword_urls_counter=0;
               while((fscanf(temp_file,"%s",temp_url))==1)
               {
                  //printf("storing: '%s'\n",temp_url);
                  strcpy(keyword_urls[keyword_urls_counter],temp_url);
                  keyword_urls_counter++;
               }
               //print_array(keyword_urls,keyword_urls_counter);
               
               result_urls_size= merge_array(keyword_urls,keyword_urls_counter, left_urls,left_urls_size,result_urls);
               memcpy(&left_urls,&result_urls,sizeof(left_urls));
               left_urls_size = result_urls_size;
               break;
         }
         
      }
   }
   //printf("im out of the biggest search loop\n");
   //printf("There are %d urls containing these words!\n",left_urls_size);
   
   //print_array(left_urls,left_urls_size);
   
   struct node *url = malloc(num_urls * sizeof(node));
   //initialize the struct 
   //int seach_terms[num_urls];
   
   for(i =0 ;i< left_urls_size;i++ )
   {
      //initialize the name of the url
      strcpy(url[i].url_name,left_urls[i]);
      //initialize the search_terms found
      url[i].search_terms=0;
      for(j=1;j<argc;j++)
      {
         url[i].search_terms += find_search_terms(left_urls[i], argv[j]);
      }
      //initialize the page_rank
      url[i].page_rank = find_page_rank(left_urls[i]);
   }
   //printf("BEFORE ALL THE SORTING:\n\n");
   //print_struct_url(url,left_urls_size);
   //H a n s e n is my name
   //works fine till here
   //need to sort the structure
   qsort(&url[0],left_urls_size,sizeof(node),compare_by_search_terms);
   //printf("after first qsort, descending order of search terms\n");
   //print_struct_url(&url[0],left_urls_size);
   for(i=0;i<left_urls_size-1;i++)
   {
      j=i+1;
      //continue if that group only contains 1 element
      if(url[i].search_terms!=url[j].search_terms)
      {
         continue;
      }
      //use j loop to the end of the group
      
      //set the j index
      while(url[i].search_terms==url[j].search_terms)
      {
         if(j==left_urls_size-1)
         {
            //the end of the array
            j++;
            break;
         }
          j++;
      }
      j--;
      //i already found the end index j
      //printf("i is now %d,j is now %d\n",i,j);
      //printf("group size: %d\n",j-i+1);
      
      qsort(&url[i],j-i+1,sizeof(node),compare_by_page_rank);
      if(j==left_urls_size-1)
      {
         break;
      }
   }
   //printf("After all the sorting---------------------------\n\n");
   //print_struct_url(url,left_urls_size);
   
   //output the result
   for(i=0;i<=30 && i< left_urls_size;i++)
   {
      printf("%s\n",url[i].url_name);
   }
   fclose(index);
   return 0;
}


void print_array(char array[][URL_LENTH],int size)
{
   printf("array:----------------------------------------------------\n");
   int i =0;
   for(i=0;i<size;i++)
   {
      printf("%s\n",array[i]);
   }
   printf("\n");
}



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


void readUrlsInCollection(int num_urls, char urls[][URL_LENTH])
{
  
  FILE *f = fopen("collection.txt","r");
  char buf[1000];
  int i = 0;
  while(fscanf(f, "%s", buf)==1)
  {
    strcpy(urls[i], buf);
    i++;
  }
  fclose(f);

}


int merge_array(char array1[][URL_LENTH],int size1, char array2[][URL_LENTH],int size2,char result_array[][URL_LENTH])
{
   int result_counter =0;
   int array1_counter =0;
   int array2_counter =0;
   for(array1_counter=0;array1_counter<size1;array1_counter++)
   {
      for(array2_counter=0;array2_counter<size2;array2_counter++)
      {
         if(strcmp(array1[array1_counter],array2[array2_counter])==0)
         {
            //printf("1 found!\n");
            strcpy(result_array[result_counter++],array1[array1_counter]);
            break;
         }
      }
   }
   
   
   return result_counter;
}

int find_search_terms(char* urlname, char*keyword)//tempword actually used
{
   int counter =0;
   char tempword[50];
   strcpy(tempword, urlname);
   strcat(tempword,".txt");
   FILE *fp = fopen(tempword,"r");
   while(fscanf(fp,"%s",tempword)==1)
   {
      normalize(tempword);
      //printf("%s\n",tempword);
      if(strcmp(tempword,keyword)==0)
      {
          counter ++;
      }
   }
   fclose(fp);
   return counter;
}


double find_page_rank(char *url)//url_with_comma actually used
{
   char number[50];

   double rank;
   
   FILE *fp = fopen("pagerankList.txt","r");
   while((fscanf(fp,"%s",number)==1))
   {
      
      normalize(number);
      if(0==strcmp(url, number))
      {
         fscanf(fp,"%s",number);
         fscanf(fp,"%s",number);
         rank = strtod(number,NULL);
         return rank;
      }
   }
   printf("url not found!\n");
   fclose(fp);
   return 0;
   
}

void print_struct_url(struct node *url,int size)
{
   int i=0;
   for(i=0;i<size;i++)
   {
      printf("url_name: %s\n",url[i].url_name);
      printf("search_terms: %d\n",url[i].search_terms);
      printf("page_rank: %f\n",url[i].page_rank);
      printf("\n");
   }
   printf("\n");
}


void normalize(char *p)
{
    char *src = p, *dst = p;

    while (*src)
    {
       if (ispunct((unsigned char)*src))
       {
          /* Skip this character */
          src++;
       }
       else if (isupper((unsigned char)*src))
       {
          /* Make it lowercase */
          *dst++ = tolower((unsigned char)*src);
          src++;
       }
       else if (src == dst)
       {
          /* Increment both pointers without copying */
          src++;
          dst++;
       }
       else
       {
          /* Copy character */
          *dst++ = *src++;
       }
    }

    *dst = 0;
}

int compare_by_search_terms(const void *url1,const void *url2)
{
   int l = ((struct node *)url1)->search_terms;
   int r = ((struct node *)url2)->search_terms;
   return (r-l);
}

int compare_by_page_rank(const void *url1,const void *url2)
{
   double l = ((struct node *)url1)->page_rank;
   double r = ((struct node *)url2)->page_rank;
   
   if(l>=r)
   {
      return 0;
   }
   else
   {
      return 1;
   }
   
}
//written by Hansen Liu
