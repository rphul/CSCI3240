#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void main(int argc, char *argv[])
{
	//FILE *file1;
	//FILE *file2;
	if (argc > 1)
	{
		int file1 = open(argv[1], O_RDONLY);
		int file2 = open(argv[2], O_RDONLY);
		//file2 = fopen(argv[2], "r");
		if ((file1 < 0) || (file2 < 0))
		{
			printf("Error in reading file or file not found");
		}
		else if ((file1>0) && (file2 > 0))
		{
			unsigned char a;
			unsigned char b;
			int count = 0;
			int byte_a = 0;
			int byte_b = 0;
			byte_a = read(file1, &a, 1);
			byte_b = read(file2, &b, 1);
			while ((a == b) && (byte_a != 0) && (byte_b != 0))
			{
				count++;
				byte_a = read(file1, &a, 1);
				byte_b = read(file2, &b, 1);
			}
			if ((byte_a != 0) && (byte_b != 0))
			{
				printf("%d\n", count);
				printf(" ");
				printf("%02X\n", a);
				printf(" ");
				printf("%c\n", b);
			}
			else if ((byte_a == 0) && (byte_b == 0))
			{
				printf("SAME");
			}
			else if ((byte_a == 0) && (byte_b != 0))
			{
				printf("EOF");
				printf("%d\n", count);
			}
			else if ((byte_a != 0) && (byte_b == 0))
			{
				printf("%X\n", count);
				printf("EOF");
			}
		}
	}
}
		
		
		
		
		/*if ((&file1 == NULL) || (&file2 == NULL))
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
}*/