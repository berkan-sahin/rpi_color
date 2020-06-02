#define MAIN
#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "tcs34725.h"
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

int main(void)
{
  int sensor_fd;
  uint8_t red, grn, blu;
  mqd_t renk_kuyruk;
  struct mq_attr attr;
  char mesaj[8];

  sensor_fd = tcs34725_init();

  if (sensor_fd == -1)
    {
      fprintf(stderr, "Baslangic hatasi!\n");
      return (-1);
    }

  attr.mq_maxmsg = 50;
  attr.mq_msgsize = 2048;

  renk_kuyruk = mq_open("/colorRGB", O_CREAT | O_WRONLY | O_NONBLOCK,
                        S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP,
                        &attr);

  if (renk_kuyruk == -1)
    {
      perror("mq_open");
      return(-1);
    }

  for (;;)
    {
      nanosleep(&integration_time, NULL);
      tcs34725_get_color(sensor_fd, &red, &grn, &blu);
      snprintf(mesaj, 8, "#%02X%02X%02X\n", red, grn, blu);

      if ( mq_send(renk_kuyruk, mesaj, 8, 0) == -1)
        {
          perror("mq_send");
          return(-1);
        }

    }

  return(0);

}
