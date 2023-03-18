#!/usr/bin/env python3
import os
import sys
import csv
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from argparse import ArgumentParser

matplotlib.use("tkagg")


def smooth(y, box_pts):
    box = np.ones(box_pts) / box_pts
    y_smooth = np.convolve(y, box, mode="same")
    return y_smooth


def main(path: str, smooth_val: int = 0) -> int:
    if not os.path.isfile(path):
        print(f'Cannot find "{path}"', file=sys.stderr)
        return 1
    with open(path, newline="") as csvfile:
        reader = csv.reader(csvfile)
        names: list[str] = next(reader)
        data: np.ndarray[list[int]] = np.array(
            list(map(lambda row: list(map(int, row)), reader))
        )
    size_arr = data[:, 0]
    times_matrix = data[:, 1:].T
    if smooth_val > 0:
        times_matrix = np.apply_along_axis(
            lambda y: smooth(y, smooth_val), 0, times_matrix
        )
    for name, times in zip(names, times_matrix):
        plt.plot(size_arr, times, label=name)
    plt.xlabel("array size")
    plt.ylabel("time (µs)")
    plt.legend()
    plt.show()
    return 0


if __name__ == "__main__":
    parser = ArgumentParser(
        description="Sorting algorithms benchmarking results visualization"
    )
    parser.add_argument("file", nargs="?", default="output.csv")
    parser.add_argument("-s", "--smooth", type=int, default=0)
    args = parser.parse_args()
    exit_code: int = main(args.file, args.smooth)
    sys.exit(exit_code)
