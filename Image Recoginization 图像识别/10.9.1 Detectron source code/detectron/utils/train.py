from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals

from shutil import copyfile
import cv2  # NOQA (Must import before importing caffe2 due to bug in cv2)
import logging
import numpy as np
import os
import re

from caffe2.python import memonger
from caffe2.python import workspace

from detectron.core.config import cfg
from detectron.core.config import get_output_dir
from detectron.datasets.roidb import combined_roidb_for_training
from detectron.modeling import model_builder
from detectron.utils import lr_policy
from detectron.utils.training_stats import TrainingStats
import detectron.utils.env as envu
import detectron.utils.net as nu


def train_model():
    """Model training loop."""
    model, weights_file, start_iter, checkpoints, output_dir = create_model()
    if 'final' in checkpoints:
        # The final model was found in the output directory, so nothing to do
        return checkpoints

    setup_model_for_training(model, weights_file, output_dir)
    training_stats = TrainingStats(model)
    CHECKPOINT_PERIOD = int(cfg.TRAIN.SNAPSHOT_ITERS / cfg.NUM_GPUS)

    for cur_iter in range(start_iter, cfg.SOLVER.MAX_ITER):
        if model.roi_data_loader.has_stopped():
            handle_critical_error(model, 'roi_data_loader failed')
        training_stats.IterTic()
        lr = model.UpdateWorkspaceLr(cur_iter, lr_policy.get_lr_at_iter(cur_iter))
        workspace.RunNet(model.net.Proto().name)
        if cur_iter == start_iter:
            nu.print_net(model)
        training_stats.IterToc()
        training_stats.UpdateIterStats()
        training_stats.LogIterStats(cur_iter, lr)

        if (cur_iter + 1) % CHECKPOINT_PERIOD == 0 and cur_iter > start_iter:
            checkpoints[cur_iter] = os.path.join(
                output_dir, 'model_iter{}.pkl'.format(cur_iter)
            )
            nu.save_model_to_weights_file(checkpoints[cur_iter], model)

        if cur_iter == start_iter + training_stats.LOG_PERIOD:
            # Reset the iteration timer to remove outliers from the first few
            # SGD iterations
            training_stats.ResetIterTimer()

        if np.isnan(training_stats.iter_total_loss):
            handle_critical_error(model, 'Loss is NaN')

    # Save the final model
    checkpoints['final'] = os.path.join(output_dir, 'model_final.pkl')
    nu.save_model_to_weights_file(checkpoints['final'], model)
    # Shutdown data loading threads
    model.roi_data_loader.shutdown()
    return checkpoints
