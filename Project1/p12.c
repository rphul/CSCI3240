#include <stdio.h>

void main(int argc, char *argv[])
{
	FILE *file1;
	FILE *file2;
	if (argc > 1)
	{
		file1 = fopen(argv[1], "r");
		file2 = fopen(argv[2], "r");
		if ((&file1 == NULL) || (&file2 == NULL))
		{
			printf("Empty file");
		}
		if ((&file1 != NULL) && (&file2 != NULL))
		{
			unsigned char a;
			unsigned char b;
			int count = 0;
			a = getc(file1);
			b = getc(file2);
			while (a == b)
			{
				count++;
				a = getc(file1);
				b = getc(file2);
			}
			//printf("%d\n", feof(file1));
			//printf("%c\n", getc(file1));
			if ((getc(file1) != EOF) && (getc(file2) != EOF))
			{
				printf("%d\n", count);
			}
			if ((getc(file1) == EOF) && (getc(file2) == EOF))
			{
				//printf("%c\n", getc(file1));
				//printf("%d\n", feof(file1));
				printf("SAME");
			}
			//printf("%d\n", feof(file1));
			if ((getc(file1) == EOF) && (getc(file2) != EOF))
			{
				//printf("%c\n", getc(file1));
				//printf("%d\n", feof(file1));
				printf("EOF");
				printf("%X\n", count + 1);
			}
			if ((getc(file2) == EOF) && (getc(file1) != EOF))
			{
				//printf("%c\n", getc(file1));
				//printf("%d\n", feof(file1));
				printf("%X\n", count + 1);
				printf("EOF");
			}
		}
	}
}