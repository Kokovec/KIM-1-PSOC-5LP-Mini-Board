/** \file
 \brief Hexadecimal to binary converter
*/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>

/** Flag set by `--verbose'. */
static int verbose_flag;

char fin[255]; 			///< input filename
char fout[255]; 		///< output filename
char strtmp[255]; 		///< temporary string
char separator[255]; 	///< separator for output strings
int bytes_per_string; 	///< how many bytes convert to string? (byte/word/quad/... data)
unsigned int wrap_line;	///< wrap line after about N chars
/** \brief Print some help */
void help(char *exename)
{
    puts("\nHexadecimal to binary converter");
    printf("\nUsage: %s --i <input_filename> --o <output_filename>\n", exename);
    puts("Note: \"0x\" and \"0X\" groups between bytes and any non-hex characters are ignored."
         "If number of hex characters in source file is uneven last hex character is ignored and error code is returned but output file is created");
    puts(" i.e. hex2bin --i myfile.c --o myfile.dat");
    puts("\nauthor: Tomasz Ostrowski, tomasz dot o dot ostrowski at gmail dot com\n");
}


/** \brief Init default options (if not exist in command line) */
void init_options(void)
{
    strcpy(fin,"");
    strcpy(fout,"out.dat");
}

int hex2val(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    return -1;
}


int
main (argc, argv)
int argc;
char **argv;
{
    int c;
    long lSize;			///< filesize
    unsigned char *buffer;		///< pointer to buffer for input file
    int option_count=0; ///< command-line options counter
    FILE *fileIn, *fileOut; ///< input and output file


    init_options();

    while (1)
    {
        static struct option long_options[] =
            {
                /* Flag-type options */
                {"verbose", no_argument,       &verbose_flag, 1
                },
                {"in",  required_argument, 0, 'i'
                },
                {"out",  required_argument, 0, 'o'
                },
                {0, 0, 0, 0
                }
            };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "abc:d:f:",
                         long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
        {
            if(option_count<1)
                help(argv[0]); // print help if no arguments
            break;
        }
        option_count++;

        switch (c)
        {
            case 0:
            /* If this option set a flag, do nothing else now. */
            if (long_options[option_index].flag != 0)
                break;
            printf ("option %s", long_options[option_index].name);
            if (optarg)
                printf (" with arg %s", optarg);
            printf ("\n");
            break;

            case 'i':
            printf ("option -i with value `%s'\n", optarg);
            strcpy(fin, optarg);
            break;

            case 'o':
            printf ("option -o with value `%s'\n", optarg);
            strcpy(fout, optarg);
            break;

            case '?':
            /* getopt_long already printed an error message. */
            help(argv[0]);
            break;

            default:
            abort ();
        }
    }


    if (verbose_flag)
        puts ("verbose flag is set");

    /* Print any remaining command line arguments (not options). */
    if (optind < argc)
    {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        putchar ('\n');
    }

    // start processing
    fileIn = fopen(fin, "rb"); // open input file (binary)
    if (fileIn==NULL)
    {
        puts("Error opening input file");
        exit (1);
    }

    // open output file
    fileOut = fopen(fout, "wb");
    if (fileOut==NULL)
    {
        puts("Error opening output file for write");
        exit (1);
    }


    // obtain file size.
    fseek (fileIn , 0 , SEEK_END);
    lSize = ftell (fileIn);
    rewind (fileIn);
	printf("Filesize: %d bytes.\n", lSize);

    // allocate memory to contain the whole file.
    buffer = (unsigned char*) malloc (lSize);
    if (buffer == NULL)
    {
    	puts("malloc for input file buffer failed (not enough memory?)");
        exit (2);
    }

    // copy the file into the buffer.
    fread (buffer,1,lSize,fileIn);

    int c1, c2;
    enum State {
        Idle,
        Odd
    } state = Idle;
    for (int i=0; i<lSize;)
    {
        char c = buffer[i];

        switch (state)
        {
        case Idle:
            if (c == '0') {
                if (i < lSize -1) {
                    if (buffer[i+1] == 'x' || buffer[i+1] == 'X') {
                        i += 2;
                        continue;
                    }
                }
            }
            c1 = hex2val(c);
            if (c1 < 0) {
                break;
            } else {
                state = Odd;
                break;
            }
        case Odd:
            c2 = hex2val(c);
            if (c2 < 0) {
                break;
            } else {
                unsigned char value = c1*16 + c2;
                fwrite(&value, 1, 1, fileOut);
                state = Idle;
                break;
            }
        }
        i++;
    }

	if(fileIn) fclose (fileIn);
	if(fileOut) fclose (fileOut);
	if(buffer) free (buffer);
	if (state == Odd)
    {
    	puts("Warning: uneven number of hex characters, last character ignored");
        exit (3);
    }
    exit (0);
}
