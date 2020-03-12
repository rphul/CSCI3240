#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Richa Phulwani
// CSCI 3240 Project 1

void main(int argc, char *argv[])
{
	if (argc > 1)
	{
		int file1 = open(argv[1], O_RDONLY);
		int file2 = open(argv[2], O_RDONLY);
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
				printf("%d:", count);
				printf(" ");
				printf("0X%02X", a);
				printf(" ");
				printf("0X%02X\n", b);
			}
			else if ((byte_a == 0) && (byte_b == 0))
			{
				printf("SAME\n");
			}
			else if ((byte_a == 0) && (byte_b != 0))
			{
				printf("%d:", count);
				printf(" ");
				printf("EOF ");
				printf("0X%02X\n", count);
			}
			else if ((byte_a != 0) && (byte_b == 0))
			{
				printf("%d:", count);
				printf(" ");
				printf("0X%02X", a);
				printf(" ");
				printf("EOF\n");
			}
		}
	}
}