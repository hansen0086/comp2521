// crawl.c ... build a graph of part of the web
// Written by John Shepherd, September 2015
// Uses the cURL library and functions by Vincent Sanders <vince@kyllikki.org>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <curl/curl.h>
#include "queue.h"
#include "set.h"
#include "graph.h"
#include "html.h"
#include "url_file.h"

#define BUFSIZE 1024

void setFirstURL(char *, char *);
void normalise(char *, char *, char *, char *, int);

int main(int argc, char **argv)
{
	URL_FILE *handle;
	char buffer[BUFSIZE];
	char baseURL[BUFSIZE];
	char firstURL[BUFSIZE];
	char next[BUFSIZE];
	int  maxURLs;
   
   
   char *curr_url;
   
	if (argc > 2) {
		strcpy(baseURL,argv[1]);
		setFirstURL(baseURL,firstURL);
		maxURLs = atoi(argv[2]);
		if (maxURLs < 40) maxURLs = 40;
	}
	else {
		fprintf(stderr, "Usage: %s BaseURL MaxURLs\n",argv[0]);
		exit(1);
	}
		
	// You need to modify the code below to implement:
	//
	// add firstURL to the ToDo list
	// initialise Graph to hold up to maxURLs
	// initialise set of Seen URLs
	// while (ToDo list not empty and Graph not filled) {
	//    grab Next URL from ToDo list
	//    if (not allowed) continue
	//    foreach line in the opened URL {
	//       foreach URL on that line {
	//          if (Graph not filled or both URLs in Graph)
	//             add an edge from Next to this URL
	//          if (this URL not Seen already) {
	//             add it to the Seen set
	//             add it to the ToDo list
	//          }
	//       }
    //    }
	//    close the opened URL
	//    sleep(1)
	// }
	
	
	//TODO
	// add firstURL to the to_do_queue
	Queue to_do_queue = newQueue(); 
	enterQueue(to_do_queue, firstURL);
	// initialise Graph to hold up to maxURLs
	Graph map = newGraph(maxURLs);
	// initialise set of Seen URLs
	//SeenURLs = newSet();
	//while (ToDo list not empty and Graph not filled)
	Set seen = newSet();
	insertInto(seen, firstURL);
	while((!emptyQueue(to_do_queue))&&(map->nV<=maxURLs))
	{
	   curr_url = leaveQueue(to_do_queue);
	      //open the html , handle is the html pointer
	      if (!(handle = url_fopen(curr_url, "r"))) 
	      {
		      fprintf(stderr,"Couldn't open %s\n", next);
		      exit(1);
	      }
	         //    foreach line in the opened URL {
	      while(!url_feof(handle))
	      {  
	         int url_counter=0;
	         //printf("2\n");
	         //buffer is a line in html
	         char next_url[BUFSIZE];
	         memset(next_url,0,BUFSIZE);
	         url_fgets(buffer,sizeof(buffer),handle);
	         //foreach URL on that line
	         while((url_counter = GetNextURL(buffer, curr_url, next_url, url_counter))>0)
	         {
	            //printf("3\n");
	            //(url is not in the seen set),not visited
	            if(!isElem(seen, next_url))
	            {
	               enterQueue(to_do_queue, next_url);
	               //printf("This is a new node, added to the todo list\n");
	               insertInto(seen,next_url);
	               printf("Found: '%s'\n",next_url);
	            }
	              addEdge(map, curr_url, next_url);
	              printf("Found: '%s'\n",next_url);
	              //printf("I havent been here before, Successfully add edge!\n");
	           memset(next_url,0,BUFSIZE);
	         }
	   }
	   url_fclose(handle);
	   //sleep(1);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	/*if (!(handle = url_fopen(firstURL, "r"))) {
		fprintf(stderr,"Couldn't open %s\n", next);
		exit(1);
	}
	while(!url_feof(handle)) {
		url_fgets(buffer,sizeof(buffer),handle);
		//fputs(buffer,stdout);
		int pos = 0;
		char result[BUFSIZE];
		memset(result,0,BUFSIZE);
		while ((pos = GetNextURL(buffer, firstURL, result, pos)) > 0) {
			printf("Found: '%s'\n",result);
			memset(result,0,BUFSIZE);
		}
	}
	url_fclose(handle);
	sleep(1);
	*/
	//printf("IM done\n\n\n");
	showGraph(map,1);
	return 0;
}

// setFirstURL(Base,First)
// - sets a "normalised" version of Base as First
// - modifies Base to a "normalised" version of itself
void setFirstURL(char *base, char *first)
{
	char *c;
	if ((c = strstr(base, "/index.html")) != NULL) {
		strcpy(first,base);
		*c = '\0';
	}
	else if (base[strlen(base)-1] == '/') {
		strcpy(first,base);
		strcat(first,"index.html");
		base[strlen(base)-1] = '\0';
	}
	else {
		strcpy(first,base);
		strcat(first,"/index.html");
	}
}
