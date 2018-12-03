draw detections label with probability

```c
void draw_detections(image im,
                     detection* dets,
                     int num,
                     float thresh,
                     char** names,
                     image** alphabet,
                     int classes) {
    int i, j;

    for (i = 0; i < num; ++i) {
        char labelstr[4096] = {0};
        int class = -1;
        float p;
        char ps[7];                                 // @Aario 
        for (j = 0; j < classes; ++j) {
            if (dets[i].prob[j] > thresh) {
                p = dets[i].prob[j] * 100;          // @Aario
                sprintf(ps, ": %.0f%%", p);         // @Aario
                if (class < 0) {
                    strcat(labelstr, names[j]);
                    strcat(labelstr, ps);           // @Aario
                    class = j;
                } else {
                    strcat(labelstr, ", ");
                    strcat(labelstr, names[j]);
                    strcat(labelstr, ps);           // @Aario
                }
                printf("%s: %s\n", names[j], ps);   // @Aario
            }
        }
        ...
    }
    ...
}

```