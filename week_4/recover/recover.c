#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
       /* check if input is valid */
       if (argc != 2)
       {
              printf("Usage: ./recover IMAGE\n");
              return 1;
       }

       /* open input file */
       FILE *input_file = fopen(argv[1], "r");
       if (input_file == NULL)
       {
              printf("Unable to open file");
              return 2;
       }

       /* Initialise variables */
       unsigned char buffer[512];
       int image_counter = 0;
       FILE *output_file = NULL;
       char *filename = malloc(8 * sizeof(char));

       /* Repeat till end of raw file */
       while (fread(buffer, sizeof(char), 512, input_file))
       {
              if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
              {
                     if (image_counter > 0)
                     {
                            fclose(output_file);
                     }

                     sprintf(filename, "%03i.jpg", image_counter);
                     output_file = fopen(filename, "w");
                     image_counter++;
              }


              if (output_file != NULL)
              {
                     fwrite(buffer, sizeof(char), 512, output_file);
              }
       }

       free(filename);
       fclose(input_file);
       fclose(output_file);

       return 0;


}