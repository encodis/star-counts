/* 
   a hack to make map scales 
*/

int main(int argc, char **argv)
{
  int i, v;
  int nx, gr, wd;
  float mv;

  nx = atoi(argv[1]);
  mv = atof(argv[2]);
  gr = atoi(argv[3]);
  
  wd = nx/2;

  /** header **/
  printf("P3 \n%d 7 \n%d\n", nx, gr);

  /** 3 blank lines **/
  for (i=0; i<3*nx; i++) printf("0 0 0\n");

  /** disk scale **/
  for (i=0; i<wd/2; i++) printf("0 0 0\n");

  for (i=0; i<wd; i++) {
    v = (wd - i) * mv/wd * gr/mv;
    v = (v < gr) ? v : gr;
    printf("%d 0 0\n", v );
  }

  for (i=0; i<=wd/2; i++) printf("0 0 0\n");

  /** 1 blank line **/
  for (i=0; i<nx; i++) printf("0 0 0\n");

  /** sphd scale **/
  for (i=0; i<wd/2; i++) printf("0 0 0\n");

  for (i=0; i<wd; i++) {
    v = (wd - i) * mv/wd * gr/mv;
    v = (v < gr) ? v : gr;
    printf("0 0 %d\n", v );
  }

  for (i=0; i<=wd/2; i++) printf("0 0 0\n");

  /** 1 blank line **/
  for (i=0; i<nx; i++) printf("0 0 0\n");


  exit(0);
}

