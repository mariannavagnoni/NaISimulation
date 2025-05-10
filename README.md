# NaISimulation
Simulation of the spectrum of 60Co source detected by a single 102x102x203 mm NaI(Tl) crystal.

## Requirements

The code is tested with the latest version of Geant4 installed with conda:
```
conda install geant4
```


## Usage

Create a build directory and enter into it:
```
mkdir build 
cd build
```

Run the simulation in visualization mode:
```
cmake ..
make
./sim
```

Run 1000000 events without visualization:
```
cmake ..
make
./sim run.mac
```