# ProceduralGen
A university project made to try / test things out with procedural Generation in cpp

TODO Description ...

## Compilation & Launch
To compile this project you will have to follow these steps:
- Install a cpp compiler like **g++**
- Install **cmake**
- Go Into the `build` folder
> $ cd build
- Generate the make file
> $ cmake ..
- Build the Project
> $ cmake --build .
- Start the project
> $ proceduralGen

## Documentation Generation
To generate documentation of the project you'll have to install `Doxygen`

Then follow theses steps:
> $ doxygen sources/docs/doxygen.conf

The documentation will be stored in the folder `docs` at the **root** if the project

The main file to start is the `./docs/html/index.html`

### Note:
The documentation generated uses [doxygen-awesome-css](https://github.com/jothepro/doxygen-awesome-css) project as a custom CSS theme. 