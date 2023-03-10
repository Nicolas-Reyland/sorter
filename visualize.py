#!/usr/bin/env python3
import os
import sys
import csv
import numpy as np
import matplotlib
import matplotlib.pyplot as plt

matplotlib.use("tkagg")


def main(path: str) -> int:
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
    for name, times in zip(names, times_matrix):
        plt.plot(size_arr, times, label=name)
    plt.xlabel("array size")
    plt.ylabel("time (µs)")
    plt.legend()
    plt.show()
    return 0


if __name__ == "__main__":
    exit_code: int = main(sys.argv[1] if len(sys.argv) > 1 else "output.csv")
    sys.exit(exit_code)
