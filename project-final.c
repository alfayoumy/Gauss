#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<unistd.h>
#include <math.h>

#define mat_elem(a, y, Sol, n) (a + ((y) * (n) + (Sol)))
float determinant(float f[20][20],int x);

int i,j,k,n,input=0,found;
char ch;
float ar[20][20]={0},arr[20][20]={0},cons[20]={0},c,Sol[10],sum=0.0;

float determinant(float f[20][20],int x)
{
  float pr,c[20],d=0,b[20][20];
  int j,p,q,t;
  if(x==2)
  {
    d=0;
    d=(f[1][1]*f[2][2])-(f[1][2]*f[2][1]);
    return(d);
   }
  else
  {
    for(j=1;j<=x;j++)
    {
      int r=1,s=1;
      for(p=1;p<=x;p++)
        {
          for(q=1;q<=x;q++)
            {
              if(p!=1&&q!=j)
              {
                b[r][s]=f[p][q];
                s++;
                if(s>x-1)
                 {
                   r++;
                   s=1;
                  }
               }
             }
         }
     for(t=1,pr=1;t<=(1+j);t++)
     pr=(-1)*pr;
     c[j]=pr*determinant(b,x-1);
     }
     for(j=1,d=0;j<=x;j++)
     {
       d=d+(f[1][j]*c[j]);
      }
     return(d);
   }
}


void swap_row(float *a, float *b, int r1, int r2, int n)
{
	double tmp, *p1, *p2;
	int i;

	if (r1 == r2) return;
	for (i = 0; i < n; i++) {
		p1 = mat_elem(a, r1, i, n);
		p2 = mat_elem(a, r2, i, n);
		tmp = *p1, *p1 = *p2, *p2 = tmp;
	}
	tmp = b[r1], b[r1] = b[r2], b[r2] = tmp;
}

void gauss_eliminate(float *a, float *b, float *Sol, int n)
{
#define A(y, Sol) (*mat_elem(a, y, Sol, n))
	int i, j, col, row, max_row,dia;
	double max, tmp;

	for (dia = 0; dia < n; dia++) {
		max_row = dia, max = A(dia, dia);

		for (row = dia + 1; row < n; row++)
			if ((tmp = fabs(A(row, dia))) > max)
				max_row = row, max = tmp;

		swap_row(a, b, dia, max_row, n);

		for (row = dia + 1; row < n; row++) {
			tmp = A(row, dia) / A(dia, dia);
			for (col = dia+1; col < n; col++)
				A(row, col) -= tmp * A(dia, col);
			A(row, dia) = 0;
			b[row] -= tmp * b[dia];
		}
	}
	for (row = n - 1; row >= 0; row--) {
		tmp = b[row];
		for (j = n - 1; j > row; j--)
			tmp -= Sol[j] * A(row, j);
		Sol[row] = tmp / A(row, row);
	}
#undef A

}

void Find()
{
    found=0;
    for(i=1; i<=n; i++) {
        for(j=1; j<=n+1; j++) {
            if (arr[i][j]!=0) found=1;
        }
    }
}

void clrscr()
{
    printf("\n\n\n\n\n\t\t...Press any key to continue...");
    getch();
    system("cls");
}

void text()
{
    if( access( "gauss.txt", F_OK ) != -1 ) {
    FILE *fin = fopen("gauss.txt", "r");
    fscanf(fin, "%d", &n);
	for (i=1; i<=n+1; ++i) {
		for (j=1; j<=n+1; ++j) {
            if (j==n+1) fscanf(fin, "%f", &cons[j]);
			else fscanf(fin, "%f", &arr[i][j]);
            } }
	fclose(fin);
    printf("\n\n\t\t\t\t...File Loaded...");
    printf("\n\n\t\tChoose option 3 from previous menu to float-check!");
    }
    else {
    printf("\n\n\t\t\t\t...File Not Found...");
    }

}

int main()
{
    printf("\n\n\t\tThis program is designed by Amr, Tarek and Saud to solve a system of linear equations\n\t\tIt uses the Gaussian Elimination method.\n\n\t\tYour system of equations should be of the form:\n\t\t\taX + bY + cZ + ... = Constant");
    clrscr();

    do {
    printf("\n\tThe program can do the following operations:\n\n\t\t 1- Input Equations from file\n\t\t 2- Input Equations from user\n\t\t 3- Display system of equations\n\t\t 4- Solve system\n\t\t 5- End the program\n");
    printf("\n\tInput your choice (1,2,3,4, or 5): ");
    scanf("%d",&input);
    switch (input) {
    case 1:
        printf("\n\n\t\tInstructions: Type the number of unknowns and the coefficients of X, Y, Z.. etc.\n\t\tin a file and name it \"gauss.txt\"");
        printf("\n\n\t\tNumbers can be separated by white spaces or in separate lines");
        printf("\n\t\tExample: \n\t\tn \n\t\ta1 b1 c1 constant1\n\t\ta2 b2 c2 constant2\n\t\ta3 b3 c3 constant3");
        clrscr();
        text();
        clrscr();
        break;

    case 2:
        printf("\n\t\tEnter the number of unknowns n: ");
        scanf("%d",&n);
        printf("\n\t\tEnter the factors of the n unknowns in the format of\n\t\taX + bY + cZ +... = constant\n\n");
        ch='a';
        for(i=1; i<=n; i++)
        {
            for(j=1; j<=n; j++)
            {
                printf("\t%c%d : ",ch+j-1,i);
                scanf("%f",&arr[i][j]);
            }
            printf("\tconstant%d : ",i);
            scanf("%f",&cons[n+1]);
            printf("\n");
        }
        clrscr();
        break;

    case 3:

        Find();

        if (found) {
        int ch2='Z'-n+1;
        printf("\n\t\tYour system of equations is:\n\n");

        for(i=1; i<=n; i++)
        {
            printf("\tEquation %d:\t",i);

            for(j=1; j<n+1; j++)
            {
                printf(" %+.2f %c",arr[i][j],ch2);
                ch2++;
            }
            printf(" = %f",arr[i][n+1]);
            printf("\n");
            ch2='Z'-n+1;
        }
        clrscr();
        }
        else {
        printf("\n\n\t\t...No inputs found!...");
        clrscr();
        }
        break;

    case 4:

    ; float t=determinant(arr,n);

        Find();

        if (found) {

            if (t!=0)
                {
                    for(i=1; i<=n; i++) {
                        for(j=1; j<=n+1; j++) {
                            ar[i][j]=arr[i][j];
                        }
                    }

                    gauss_eliminate(arr, cons, Sol, n);

                    printf("\n\tThe solution is: \n");
                    int ch2='Z'-n+1;
                    for(i=1; i<=n; i++)
                    {
                        printf("\tSolution %d:\t",i);
                        printf("%c = %f",ch2,Sol[i]);
                        ch2++;
                        printf("\n");
                    }

                } else printf("\n\n\t\t...System is inconsistent!...\n");
            }
            else printf("\n\n\t\t...No inputs found!...");
            clrscr();
            break;

    case 5: printf("\n\n\t\t...Thanks for using our program. Goodbye!...\n\n\n\n\n\n");
        break;

    case 6: //for debugging
        ;

                t=determinant(arr,n);
                printf("%f",t);
                printf("\n\n");
                for(i=1; i<=n; i++) {
                    for(j=1; j<=n+1; j++) {
                        printf("%f\t",ar[i][j]);
                    }
                    printf("\n");
                }

                printf("\n\n");

                for(i=1; i<=n; i++) {
                    printf("%f\t",Sol[i]);
                }

                printf("\n\n");

                for(i=1; i<=n; i++) {
                    for(j=1; j<=n+1; j++) {
                        printf("%f\t",arr[i][j]);
                    }
                    printf("\n");
                }
                clrscr();
                break;



    default:
        printf("\n\n\t\t...Invalid Input!...");
        clrscr();
        break;

    }
    } while(input!=5);


    return(0);
}
