# HavocMAB
HavocMAB is an extension of [AFL-2.57b](https://github.com/google/AFL/tree/v2.57b) by Michal Zalewski \<lcamtuf@google.com\>. The goal of HavocMAB is to facilitate the edge exploration of AFL default Havoc mutation strategy with two-layer Multi-Armed Bandits and UCB1-Tuned algorithm.

## Published Work

[One Fuzzing Strategy to Rule Them All](https://dl.acm.org/doi/pdf/10.1145/3510003.3510174), ICSE 2022.

```
@inproceedings{wu2022one,
  title={One Fuzzing Strategy to Rule Them All},
  author={Wu, Mingyuan and Jiang, Ling and Xiang, Jiahong and Huang, Yanwei and Cui, Heming and Zhang, Lingming and Zhang, Yuqun},
  booktitle={Proceedings of the International Conference on Software Engineering},
  year={2022}
}
```

## Environment

Tested on ESC servers with 128-core 2.6GHz AMD EPYC™ROME 7H12 CPUs and 256 GiB RAM. The machine runs on Linux 4.15.0-147-generic Ubuntu 18.04 with RTX 2080ti.

## Fuzzing with HavocMAB

```shell
# build
$ make -j$(nproc) -C fuzzer

# start fuzzing (-d to enbale havoc mutation)
$ fuzzer/afl-fuzz -d -i $FUZZ_IN -o $FUZZ_OUT -- /path/to/program [params] @@
```

For running a demo program `readelf`, please turn to the [document](./docs/run_target.md).

## Contact
Feel free to send an email at tricker51449@gmail.com.