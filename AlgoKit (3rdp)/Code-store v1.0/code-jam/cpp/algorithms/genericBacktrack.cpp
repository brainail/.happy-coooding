#define MAXCANDIDATES   100		
#define NMAX            100		

typedef char* data;			

bool finished = FALSE;                  

backtrack(int a[], int k, data input)
{
   int c[MAXCANDIDATES];           /* candidates for next position */
   int ncandidates;                /* next position candidate count */
   
   if(is_a_solution(a,k,input))
      process_solution(a,k,input);
   else {
      k = k+1;
      construct_candidates(a,k,input,c,&ncandidates);
      for(int i=0; i<ncandidates; i++) {
         a[k] = c[i];
         backtrack(a,k,input);
      if(finished) 
         return;	                }
   }
}
