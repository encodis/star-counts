/*
   Scale and clip data - output as a ppm file

   Usage: scppm norm|log nx ny num max < input > output

   Compile with: gcc -o scppm scppm.c -lm
*/

#include <stdio.h>
#include <math.h>

void main(int argc, char **argv)
{
  int   nx, ny, num;
  float max;
  char  trans, line[81];
  float d, t, s, T, scale;
  int   dsk, thk, spd;
  
  if (argc != 6) {
    fprintf(stderr,"scppm n|l nx ny num_gry_lev max_val < input > output \n");
    exit(1);
  }
  
  trans = argv[1][0];
  nx    = atoi(argv[2]);
  ny    = atoi(argv[3]);
  num   = atoi(argv[4]);
  max   = atof(argv[5]);
  scale = (float) num / max;
  
  printf("P3 \n%d %d \n%d \n", nx, ny, num);
  
  while (fgets(line,81,stdin))
    {
      sscanf(line,"%f %f %f %f", &d, &t, &s, &T);
      
      if (trans == 'l')
	{
	  d = (d <= 1.0) ? 0.0 : log10(d);
	  t = (t <= 1.0) ? 0.0 : log10(t);
	  s = (s <= 1.0) ? 0.0 : log10(s);
	}
      
      d = d * (num/max);
      t = t * (num/max);
      s = s * (num/max);
      
      dsk = ( (int) d < num ) ? (int) d : num;
      thk = ( (int) t < num ) ? (int) t : num;
      spd = ( (int) s < num ) ? (int) s : num;
      
      printf("%d %d %d\n", dsk, thk, spd);
    }
  
  exit(0);
}
