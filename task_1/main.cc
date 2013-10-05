#include <cstdio>
#include <cstdlib> // for abort and exit functions
#include <getopt.h>
#include "Image.h"

// Praser augmentów to przerobiony kod podkradziony w wgeta. 

/* Flag set by ‘--verbose’. */
static int verbose_flag;
const char *exec_name;

/* Print the usage message.  */
static void
print_usage (void)
{
  printf ("Usage: %s [OPTION]... \n", exec_name);
}

static void
print_help (void)
{
  printf ("Command-line image manipulation program. \
Just to pass the labs."); // Możliwe, że to trzeba będzie usunąć
  fputs ("\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
\n", stdout);
  fputs ("\
Startup:\n\
  -h,  --help              print this help.\n\
  -v,  --verbose           for debugging purposes.\n\
  -e,  --file=filename     set the name of the file.\n\
  -b,  --brightness=value  set brightness.\n\
  -n,  --negative          invert values of pixels.\n\
\n", stdout); print_usage ();
}


int main (int argc, char **argv)
{
    
    // Possible values to set
    double brightness_val = {0.0};
    const char *filename = NULL;
    
    // Operations to perform
    bool isSetBrightness, isFilenameGiven,
         isSetContrast = {false}; // automatically will set all to false

    // Praser
    int c;
    exec_name = argv[0];

    if (argc == 1){
        print_usage ();
        printf ("\n");
        printf ("Try `%s --help' for more options.\n", exec_name);
        exit (0);

    }

    while (1)
    {
        static struct option long_options[] =
        {
            /* These options set a flag. */
            {"verbose", no_argument,       &verbose_flag, 1},
            /* These options don't set a flag.
               We distinguish them by their indices. */
            {"negative",     no_argument,       0, 'n'},
            {"help",     no_argument,       0, 'h'},
            {"brightness",  required_argument, 0, 'b'},
            {"file",    required_argument, 0, 'f'},
            {0, 0, 0, 0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "hnb:f:",
                long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

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

            case 'h': // help
                print_help ();
                exit(0);
                break;

            case 'n': // inverse
                printf ("negative");
                break;

            case 'b': // brightness
                // TODO: check if argument is correct
                brightness_val = atof(optarg);
                isSetBrightness = true;
                break;

            case 'f':
                filename = optarg;
                isFilenameGiven = true;
                break;

            case '?':
                print_usage ();
                printf ("\n");
                printf ("Try `%s --help' for more options.\n", exec_name);
                exit (0);

            default:
                print_usage ();
                printf ("\n");
                printf ("Try `%s --help' for more options.\n", exec_name);
                abort ();
        }
    }

    /* Instead of reporting ‘--verbose’
       we report the final status resulting from them. */
    if (verbose_flag)
        puts ("DEBUGGING MODE");

    /* Print any remaining command line arguments (not options). */
    if (optind < argc)
    {
        printf ("Wrong arguments: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        putchar ('\n');
        print_usage ();
        putchar ('\n');
        printf ("Try `%s --help\' for more options.\n", exec_name);
        exit(1);
    }
    
    if (!isFilenameGiven)
    {
        puts("You must give the name of the file to operate on");
        print_usage ();
        putchar ('\n');
        printf ("Try `%s --help\' for more options.\n", exec_name);
        exit(1);
    }
    
    Image img(filename);

    if (isSetBrightness)
        img.brightness(brightness_val);

    img.save();

    exit (0);
}
