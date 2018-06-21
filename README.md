# `qpu-set-pcs`

`qpu-set-pcs` can set/show performance counters of Raspberry Pi QPU.


## Requirements

You need [libvc4regmap](https://github.com/Terminus-IMRC/libvc4regmap).


## Building

```
$ make
```


## Running

To show current status of performance counters:
```
$ sudo ./qpu-set-pcs
```

To set counters (example):
```
$ sudo ./qpu-set-pcs 16 17 18 19 20 21 22 23 24 25 26 27 28 29
```
