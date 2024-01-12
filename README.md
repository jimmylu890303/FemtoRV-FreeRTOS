# FemtoRV-FreeRTOS
This repository is not yet complete, and there are several issues to be resolved for porting FreeRTOS on [FemtoRV](https://github.com/BrunoLevy/learn-fpga/tree/master/FemtoRV). For more information, please refer to the documentation available [here](https://hackmd.io/fPdk5tjYSGmI4mx5LQZuQg?view).
## How to run 
1. Clone this repository at learn-fpga\FemtoRV\FIRMWARE\EXAMPLES\directory.
2. make RTOSDemo.barematal.elf at `learn-fpga\FemtoRV\FIRMWARE\EXAMPLES\FemtoRV-FreeRTOS\Demo\` directory.
```
make all
cp /examples/RTOSDemo.barematal.elf ../..
```
3. make RTOSDemo.hex at `learn-fpga\FemtoRV\FIRMWARE\EXAMPLES` directory.
```
make RTOSDemo.hex
```
4. run FemtoRV at `learn-fpga\FemtoRV` directory.
```
make BENCH
```
