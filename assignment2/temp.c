#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//get 2 arrays, make a result_array and return the size of that array



typedef struct node 
{
   char * url_name;
   int search_terms;
   double page_rank;
   struct url_node *next;
   
}node;

/*typedef struct all_urls
{
   int urls_num;
   node first
}
*/

void print_struct_url(struct node *url,int size);
int compare_by_search_terms(const void *url1,const void *url2);
int compare_by_page_rank(const void *url1,const void *url2);



int main(void)
{
   int i,j=0;
   int num_urls= 4;
   struct node *url = malloc(num_urls * sizeof(node));
   //initialize the structure
   url[0].url_name ="url22";
   url[0].search_terms = 23;
   url[0].page_rank = 0.3;
   
   url[1].url_name ="url23";
   url[1].search_terms = 25;
   url[1].page_rank = 0.1;
   
   url[2].url_name ="url24";
   url[2].search_terms = 23;
   url[2].page_rank = 0.2;
   
   url[3].url_name ="url25";
   url[3].search_terms = 100;
   url[3].page_rank = 0.4;
   
   print_struct_url(&url[0],4);
   
   printf("\n\n\n");
   
   qsort(&url[0],4,sizeof(node),compare_by_search_terms);
   printf("after first qsort, descending order of search terms\n");
   print_struct_url(&url[0],4);
   //within each group, sort it by page_rank
   for(i=0;i<num_urls-1;i++)
   {
      j=i+1;
      //continue if that group only contains 1 element
      if(url[i].search_terms!=url[j].search_terms)
      {
         continue;
      }
      //use j loop to the end of the group
      
      
      while(url[i].search_terms==url[j].search_terms)
      {
         
         if(j==num_urls-1)
         {
            //the end of the array
            break;
         }
          j++;
        
         printf("j is now %d\n",j);
      }
      //i already found the end index j
      qsort(&url[i],j-i,sizeof(node),compare_by_page_rank);
      
      
   }
   printf("Final version:\n\n");
   print_struct_url(&url[0],4);
    printf("\n\n\n");
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
   return (int)(r-l);
}




