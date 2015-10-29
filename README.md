# author

Aditya Mundle

# usage
> $`make`

> This compiles source code (located in `src` folder) and produces and executable `evaluate` in the current directory.

>$`evaluate test/field1 test/script1`

> This evaluates the `field` and `script` files in the test folder. It will:
> 1. Print the initial grid

> 2. Show the current command

> 3. Print resultant grid

> 4. Loop Step 2 and 3 until the end of simulation

> 5. Print the final score

# design

### evaluate

This starts a simulation given valid `field` and  `script` files. It runs the `Simulator` step wise, printing the step number and the grid pre and post simulation. After the simulation is complete, it queries the `Simulator` for mines remaining, number of fires, number of moves, if the script was complete, and if a mines was missed. Using this information it evaluates a candidates `script`.

### Simulator
The `Simulator` class is responsible for reading the files, creating the `Ship` and `Grid` objects, and book keeping. It reads the `script` one line at a time and passes on the appropriate - `fire` or `move` - command to the `Ship`. It also simulates a 'drop' of the `Ship` through the `Cuboid` by updating the `Grid` object. The `evaluate` program can query the `Simulator` if it is complete. Simulation is over when a mine is missed or all the mines are destroyed or the script ends. The `evaluate` program can also query the `Simulator` for initial number of mines, mines remaining at the end of the script and if a mine was missed.

### Grid
`Simulator` parses the `field` file and stores it as a 2d array of `deque`. A `deque` was chosen over a `vector` since extracting the front and back items were frequent operations. The `Grid` provides `Simulator` an interface to query the dimensions, change the size, query the total number of mines at a given instant, and query if a mine was missed during a 'drop'.

### Ship
`Simulator` can command a `Ship` to either `fire` or `move` according to the command. Depending on these commands, `Ship` can destroy a mine or move in the grid. `Ship` interacts with the grid using `Cuboid`.

### Cuboid
`Cuboid` is the only way `Ship` can access grid - get the dimensions or destroy a mine at a particular position in the grid.
