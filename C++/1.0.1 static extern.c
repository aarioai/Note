/**
 * Static in C
 */

static int urinate = 100;
void abscess() {
  printf("%d", urinate);  // global urinate 100
  urinate = 5000;         // alter global urinate to 5000
  static int urinate = 50;     // not global urinate
  printf("%d", urinate);  // abscess.urinate 50; global urinate is still 5000
}

 