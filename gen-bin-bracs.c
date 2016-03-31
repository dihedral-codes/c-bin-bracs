#include <stdio.h>		
#include <stdlib.h>

int N = 16;
int total = 0;

unsigned long long b = 0;

int get(int i) {
  return (((b >> i) & ((unsigned long long) 1)) ? 1 : 0);
}

void set(int i, int value) {
  if (value)
    b |= (((unsigned long long) 1) << i);
  else
    b &= ~(((unsigned long long) 1) << i);
}

void print() {
  int j;

  for (j = 1; j <= N; j++)
    printf("%d", get(j));

  printf("\n");

  //total = __builtin_parityll(b);

  total++;
}

int checkrev(int t, int i) {

  int j;
	
  //printf("%d,%d,%d,%d\n", j, t-j+1, get(j), get(t - j + 1));

	for (j = i + 1; j <= (t + 1) / 2; j++) {
		if (get(j) < get(t - j + 1))
      return(0);
		if (get(j) > get(t - j + 1))
      return(-1);
	}

	return(1);
}

void generate(int t, int p, int r, int u, int v, int RS) {

  //printf("%d,%d,%d,%d,%d,%d\n",t,p,r,u,v,RS);
  
  int j, rev;
	
	if (t - 1 > (((N - r) / 2) + r)) {
		if (get(t - 1) > get(N - t + 2 + r))
      RS = 0;
		else if (get(t - 1) < get(N - t + 2 + r))
      RS = 1;
	}
  	
  if (t > N) {
		if ((RS == 0) && ((N % p == 0)))
      print();  
	} else {

		set(t, get(t - p));
		
    if (get(t) == get(1))
      v++;
		else
      v = 0; 
		
    if ((u == -1) && (get(t - 1) != get(1)))
      u = r = t - 2;
		
		if ((u != -1) && (t == N) && (get(N) == get(1)))
      {} 
		else if (u == v) { 
			rev = checkrev(t, u);	
			if (rev == 0)
        generate(t + 1, p, r, u, v, RS);
			if (rev == 1)
        generate(t + 1, p, t, u, v, 0); 
		} 
		else
      generate(t + 1, p, r, u, v, RS);
		
    for (j = get(t - p) + 1; j <= 1; j++) {
      set(t, j);  
			generate(t + 1, t, r, u, 0, RS);
		}
  }
}

int main(int argc, char *argv[]) {
  
  N = atoi(argv[1]);

  b = 0;
  
  generate(1,1,1,-1,0,0);

	printf("\nTotal = %d\n\n", total);


  return 0;
}
