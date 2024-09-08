#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

void help(char* prog);
void fix_isbn(const char *isbn10);
void check_and_remove(const char *isbn, char* isbnout, unsigned char minimum);
unsigned short sum_isbn(const char* isbn, const unsigned char to);
void check_isbn(const char *isbn);
void random_isbn(void);

int main(const int argc, char *argv[])
{
    if (argc < 2) {
        help(argv[0]);
        exit(EXIT_FAILURE);
    }
    int opt;

    // put ':' in the starting of the
    // string so that program can
    //distinguish between '?' and ':'
    while((opt = getopt(argc, argv, "c:f:rh")) != -1)
    {
        switch(opt)
        {
            case 'h':
                help(argv[0]);
                exit(EXIT_SUCCESS);
            case 'f':
                printf("fixing: %s\n", optarg);
                fix_isbn(optarg);
                break;
            case 'c':
                printf("Checking ISBN: %s\n", optarg);
                check_isbn(optarg);
                break;
            case 'r':
                random_isbn();
                break;
            case '?':
                printf("unknown option: %c\n", optopt);
            break;
            default:
                printf("unknown error.");
        }
    }
    return 0;
}

void help(char *prog) {
    printf("Usage: %s [options]\nOptions:\n\t-c <isbn>\tCheck an ISBN 10\n\t-r\t\t\tCreate a random ISBN 10\n\t-f <isbn>\tCorrect an invalid ISBN 10\n\t-h\t\t\tShow this help.\n", prog);
}

void random_isbn(void){
// Use the better random method on platforms that support it.
#ifdef _WIN32
srand(time(NULL));
#define rand_call rand
#else
    FILE* f = fopen("/dev/urandom", "r");
    const int addfactor = fgetc(f);
    fclose(f);
    srandom(time(NULL)+addfactor);
#define rand_call random
#endif
    char isbn_text[10];
    const int isbn = rand_call()%1000000000;
    sprintf(isbn_text, "%09d", isbn);
    fix_isbn(isbn_text);
}

void check_isbn(const char *isbn) {
    char newisbn[13];
    check_and_remove(isbn, newisbn, 10);

    unsigned short final = sum_isbn(newisbn, 10);

    if (final == 11) {
        printf("The ISBN %s is Valid.\n", isbn);
    } else {
        printf("The ISBN %s is not Valid. Run with -f to fix it.\n", isbn);
    }

}

void fix_isbn(const char *isbn10) {
    char newisbn[13];
    check_and_remove(isbn10, newisbn, 9);

    unsigned short final = sum_isbn(newisbn, 9);

    if (final == 11) {
        final = 0;
    }
    for (int i = 0; i < 11; i++) {
        if (i == 1 || i == 4 || i == 10) {
            printf("-");
        }
        if (i < 10) {
            printf("%c", newisbn[i]);
        } else {
            if (final != 10) {
                printf("%i\n", (int)final);
            } else {
                printf("X\n");
            }
        }
    }
}


unsigned short sum_isbn(const char* isbn, const unsigned char to) {
    unsigned short sum = 0;

    char digit[2];
    digit[1] = '\0';
    for (int i = 0,h=10; i < strlen(isbn); i++,h--) {
        digit[0] = isbn[i];
        int currdigit;
        if (digit[0] == 'x' || digit[0] == 'X') {
            currdigit = 10;
        } else {
            currdigit = atoi(digit);
        }
        if (i < to) {
            sum += currdigit*h;
        }
    }
    return (unsigned short)11-sum%11;
}

void remove_non_digits(const char* isbn, char* isbnout);

void check_and_remove(const char *isbn, char* isbnout, const unsigned char minimum) {
    if (strlen(isbn) > 13) {
        fprintf(stderr, "Invalid ISBN-10: %s\n(did you use too many hyphens?)\n", isbn);
        exit(EXIT_FAILURE);
    }
    remove_non_digits(isbn, isbnout);

    if (strlen(isbnout) < minimum) {
        fprintf(stderr, "Invalid ISBN.\n");
        exit(EXIT_FAILURE);
    }
}

void remove_non_digits(const char* isbn, char* isbnout) {
    unsigned char j = 0;
    for (unsigned char i = 0; i < strlen(isbn); i++) {
        if (isdigit(isbn[i]) || isbn[i] == 'x' || isbn[i] == 'X') {
            isbnout[j++] = isbn[i];
        }
    }
    isbnout[j] = '\0';
}