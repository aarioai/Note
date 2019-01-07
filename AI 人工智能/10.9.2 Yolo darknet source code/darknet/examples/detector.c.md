```c
void train_detector(char *datacfg, char *cfgfile, char *weightfile, int *gpus,
                    int ngpus, int clear) {
    // ...
    if (avg_loss < 0)
        avg_loss = loss;
    avg_loss = avg_loss * .9 + loss * .1;

    i = get_current_batch(net);
    printf("%ld: %f, %f avg, %f rate, %lf seconds, %d images\n",
            get_current_batch(net), loss, avg_loss, get_current_rate(net),
            what_time_is_it_now() - time, i * imgs);
    if (i % 100 == 0) {
#ifdef GPU
        if (ngpus != 1)
            sync_nets(nets, ngpus, 0);
#endif
        char buff[256];
        sprintf(buff, "%s/%s.backup", backup_directory, base);
        save_weights(net, buff);
    }
    if (i % 1000 == 0 || (i < 1000 && i % 100 == 0)) {          // @Aario save weights every 1000 epoch
#ifdef GPU
        if (ngpus != 1)
            sync_nets(nets, ngpus, 0);
#endif
        char buff[256];
        sprintf(buff, "%s/%s_%d.weights", backup_directory, base, i);
        save_weights(net, buff);
    }
    free_data(train);
    // ...
}                   
```