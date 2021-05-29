# VxWorks Basics
This repo represents my first fun approach to Embedded programming. Experience made during the SWE4ES course at the University of Florence using <a href="https://en.wikipedia.org/wiki/VxWorks"> VxWorks </a> RTOS.

```
 \77777777\          /77777777/
  \77777777\        /77777777/
   \77777777\      /77777777/
    \77777777\    /77777777/
     \77777777\   \7777777/
      \77777777\   \77777/              VxWorks 7 SMP 64-bit
       \77777777\   \777/
        \77777777\   \7/     Core Kernel version: 3.1.2.1
         \77777777\   -      Build date: Mar 24 2020 16:31:08
          \77777777\
           \7777777/         Copyright Wind River Systems, Inc.
            \77777/   -                 1984-2020
             \777/   /7\
              \7/   /777\
               -   -------

                   Board: SIMLINUX board
               CPU Count: 2
          OS Memory Size: 508MB
        ED&R Policy Mode: Deployed
     Debug Agent: Started (always)
         Stop Mode Agent: Started (always)
```

## Know-How
In this "projects" are presents two dkm implemented on Wind River Workbench to test semaphores and periodic activations.

Two modules has been implemented, we can show workspase tree:

```
├── test_periodic
│   ├── dkm.c
│   ├── dummyTask.c
│   ├── dummyTask.h
│   └── ...         # building
│
└── test_semaphores
    ├── dkm.c
    ├── mutual.h
    └── ...         # building
```

You can test the two dkm in a single virtual target as <a href="https://www.windriver.com/"> Windriver's </a> VxSim, by typing the following instructions in the Kernel Shell.
```
sp start        # launch task for test_semaphores
sp init         # launch task for test_periodic
```

## VxWorks
My workstation is used as host with VxSim as target and the system viewer capture the events and allows data exchange between.

Windriver allows to create _download kernem modules_ (**DKM**). These are loaded into the target with "target actions for the selected connections" and "load modules".

### Tasks

### Semaphores

### Periodic Activations
