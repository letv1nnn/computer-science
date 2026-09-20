# Chapter 2. Programming Model

Main concepts behind the CUDA programming model.

```
                         GPU
                          │
             ┌────────────┼────────────┐
             │            │            │
            SM           SM           SM
             │            │            │
        ┌────┴────┐   ┌───┴────┐   ┌───┴────┐
        │         │   │        │   │        │
      Block     Block Block   Block Block  Block
        │         │
      ┌─┴─┐     ┌─┴─┐
    Warp Warp  Warp Warp
      │    │    │    │
     32T  32T  32T  32T
```


# 2.1. Kernels

CUDA C extends C by allowing the programmer to define C functions, called kernels, that, when called, are executed N times in parallel by N different CUDA threads, as opposed to only once like regular C functions.

A kernel is defined using the `__global__` declaration specifier and the number of CUDA threads that execute that kernel for a given kernel call is specified using a new `<<<...>>>` execution configuration syntax. Each thread that executes the kernel is given a unique thread ID that is accessible within the kernel through the built-in `threadIdx` variable.

# 2.2. Thread Hierarchy

For convenience, threadIdx is a 3-component vector, so that threads can be identified using a one-dimensional, two-dimensional, or three-dimensional thread index, forming a one-dimensional, two-dimensional, or three-dimensional block of threads, called a thread block.