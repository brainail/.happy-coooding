    

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

	// substring de java en c, aunque es O(n*m) en la practica puede
    // ser mas rapido que strstr (que esta hecho utilizando KMP y usa
	// O(m) memoria adicional. KMP esta abajo). 
	int indexOf(char *source, int sourceOffset, int sourceCount,
                       char *target, int targetOffset, int targetCount,
                       int fromIndex) {
	if (fromIndex >= sourceCount) {
            return (targetCount == 0 ? sourceCount : -1);
	}
    	if (fromIndex < 0) {
    	    fromIndex = 0;
    	}
	if (targetCount == 0) {
	    return fromIndex;
	}

        char first  = target[targetOffset];
        int max = sourceOffset + (sourceCount - targetCount);

        for (int i = sourceOffset + fromIndex; i <= max; i++) {
            /* Look for first character. */
            if (source[i] != first) {
                while (++i <= max && source[i] != first);
            }

            /* Found first character, now look at the rest of v2 */
            if (i <= max) {
                int j = i + 1;
                int end = j + targetCount - 1;
                for (int k = targetOffset + 1; j < end && source[j] ==
                         target[k]; j++, k++);

                if (j == end) {
                    /* Found whole string. */
                    return i - sourceOffset;
                }
            }
        }
        return -1;
    }
/* KMP.c: Implements strstr library function using the Knuth-Morris-Pratt
   substring search algorithm.

	By Terry R. McConnell

  The entry point my_strstr is an implementation of the standard C library
  function strstr using the KMP algorithm. Extensive documentation is
  provided in the form of comments. There is also a main program invoked
  as "kmp <target string>" (or with -h option for usage information) which
  searches for the first occurence of the target in the stdin stream and
  prints information about where it was found.

  Reference: Knuth, D.E., J.H. Morris, and V.R. Pratt, "Fast pattern matching
  in strings", SIAM J. Computing, 6:2, 323-350.

  Compile: cc -o kmp kmp.c
  Include -DMAX_SOURCE=... to change size of largest string that can be
  searched.

*/

#ifndef MAX_SOURCE
#define MAX_SOURCE 200010
#endif

#define VERSION "1.1"
#define PROGNAME "kmp"
#define USAGE "kmp [-flnvhr] target"
#define HELP "-h: print this helpful message\n\
-v: print version number and exit\n\
-l: use library version of strstr instead. (Useful for benchmarking.)\n\
-f: list definition of the Knuth-Morris-Pratt failure function for target\n\
-r: print the shortest repeating prefix of target \n\
-n: count occurrences of target in source and exit\n\
Read stdin and find first occurence of target string in it. \n\
Print information about where it was found.\n\n"

int *f = new int[200100];  /* Pointer to array containing values of failure function */

/* Create the failure function for target string. The failure function
   is defined as follows, for i = 1 to m, where m is the length of
   the target string: Let the target string be b_1...b_m. Then f(i) is
   the length of the longest proper suffix of b_1...b_i which is a prefix
   of the target string.

   If you are trying to find the first occurence of a target string in
   a stream of input characters and the i+1st character is wrong, you
   need not start over looking for the beginning of the target from the
   next received character on, because the last few characters received
   might still be a valid head start on forming the target. The failure
   function tells exactly how many characters head start you have.

   In more colorful language, the idea behind this algorithm is: Don't
   throw the baby out with the bathwater.

   The code below was translated into C from psuedo code given on page
   151 of Aho, Sethi, and Ullman. Unfortunately, the C-convention of
   starting array indices from 0 makes the code harder to follow than it
   should be. To make it easier, we never use f[0]. */

int make_f(const char *target, int lentar){

	int t = 0; /* think of t+1 as the length of the current valid
                      prefix. */
	int s,m;

	m = lentar;


	f[1] = 0; /* When first character is received there is no proper
                     suffix. */

	for(s=1;s<m;s++){ /* Create f[s] */

		while((t > 0) && (target[s] != target[t]))
			t = f[t];  /* This is the subtle part of the
                                 algorithm. The target does not begin
                                 t_0...t_t t_s. We could examine t_1...t_s,
                                 t_2...t_s,... successively to see which (if any)
                                 gives a valid prefix. But this is not
                                 necessary. Say the longest valid prefix is
                                 t_k...t_t t_s. Then t_k...t_t is also a valid
                                 prefix. But f(t) gave the length of the
                                 longest valid prefix of the form t_k...t_t.
				 Thus no k such that t_k..t_t is longer than
                                 f(t) need be considered. Now iterate this
                                 reasoning to conclude that only candidates
                                 t_k...t_t of lengths f(t), f(f(t)),...
                                 need be considered. */

		if(target[t] == target[s]){ /* The next character can be
                                               added to current prefix to get
                                               a longer valid prefix. Good! */
			t++;
			f[s+1] = t;
		}
		else f[s+1] = 0; /* Clearly the while loop above must have
                                    exited due to t=0. */
	}
}

/* Theoretical note: the assignment t = f[t] can be done at most m-1
   times, where m is the length of the target string (although the
   while loop can iterate more than once on given pass. For example,
   if the target is abababb, then f(6)=4, f(f(6))=2, and f(f(f(6)))= 0.
   The assignment is done 3 times when s = 6.) It is then easy to see that
   the running time of the routine make_f is O(m).

   Lemma. Let f be a non-negative integer valued function such that
   f(1) = 0, and so that f is "continuous upwards", i.e., f(t+1) <= f(t) + 1.
   Then

		__
     A = 	\   [ f(s) - f(s+1) ]+   <=  (l-1),
		/__

     where a+ denotes the maximum of a and 0, and a- denotes the minimum
     of a and 0. Here and below, all sums run from 1 to l-1.

	Proof: Since a = (a+) + (a-) for any number a,  we have
				__
	-f(l) = f(1) - f(l) =	\   [ f(s) - f(s+1) ]    =
				/__
		__
        A + 	\   [ f(s) - f(s+1) ]-    >=    A  - (l-1).
		/__

	Using f(l) >= 0 and rearranging, we obtain the desired inequality.

								QED.

   Consider now a given iteration of the 'for' loop with a given value
   of s. Let n be the number of times the assignment t = f(t) is done.
                               (n)              (n)          (n)
   Note that f(s+1) is either f (s) + 1, or 0 = f(s), where f  denotes the
   n-1 fold iterate of f. Since f(t) < t (only proper suffixes are
   considered,) we have

	 (n)
	f (s)  <=  f(s) - n + 1.

   Thus, in either case, f(s) - f(s+1) >= n. Now apply the lemma to obtain
   the desired bound on the sum of n.

*/

/* Return a pointer to the first occurence of target string in source
*  string, or null if the target does not occur in the source.
*/

char *my_strstr(const char *src, const char *target, int lensrc, int lentar){

	int s = 0; /* Trie state */
	int i;     /* Current index of source char */
	int m;

	make_f(target, lentar); /* Create failure function for this target */
	m = lentar;
        int tamF =lensrc;
	for(i=0;i<tamF;i++){
		while( (s>0) && (src[i] != target[s]))
			s = f[s];
		if(src[i] == target[s]) s++;
		if(s==m) return ((char *)src+i-m+1);
	}
	return NULL;
}



